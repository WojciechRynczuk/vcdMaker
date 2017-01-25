# flat.py
#
# A storage for parameters read from a flat (not tested) XML structure.
#
# Copyright (c) 2017 vcdMaker team
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import os


class Flat(object):
    """A storage for parameters read from a flat XML structure."""

    def __init__(self, node, parameters):
        """Class constructor.

        Arguments:
        node - The XML node to be read.
        parameters - The structure describing requirements towards the
                         parameters to be read.

        Example:
        parameters =  {'name': ['', ''],
                       'output_file': ['', 'Missing output file'],
                       'golden_file': ['', 'Missing golden file']}

        The 'key' is the name of the parameter to be read.

        The first element of the list is the value of the read parameter.

        The second element of the list if empty means that the parameter
        is optional. If set, it means the parameter is obligatory and it
        represents a message to be displayed when the parameter is missing.
        """
        self.errors = []
        self.parameters = parameters
        self.read_parameters(node)
        self.check_parameters()

    def read_parameters(self, node):
        """Reads parameters."""

        for element in list(node):
            if element.tag in self.parameters:
                self.parameters[element.tag][0] = element.text

    def check_parameters(self):
        """Checks if all necessary parameters are provided.

        Raises:
        RuntimeError is raised if not all requested parameters are provided.
        """

        for element in self.parameters:
            if self.parameters[element][1] != '':
                if ((self.parameters[element][0] is None) or
                        (not self.parameters[element][0].strip())):
                    self.errors.append(self.parameters[element][1])

        if len(self.errors) > 0:
            raise RuntimeError('Invalid parameters in the test: ',
                               *self.errors)

    def get_parameter(self, param):
        """Returns the requested parameter."""
        return self.parameters[param][0]


class CommonFlat(Flat):
    """The class inheriting from Flat. Designed to handle common test
    parameters.
    """

    def __init__(self, node, test_directory):
        """The constructor of the CommonFlat class specifies the common
        test parameters.
        """
        self.common_params = {'output_file': ['', 'Missing output file'],
                              'golden_file': ['', 'Missing golden file']}

        self.test_directory = test_directory
        Flat.__init__(self, node, self.common_params)

    def get_output_file(self):
        """Returns the absolute output file path."""

        return os.path.join(self.test_directory,
                            self.get_parameter('output_file'))

    def get_golden_file(self):
        """Returns the absolute golden file path."""

        return os.path.join(self.test_directory,
                            self.get_parameter('golden_file'))


class InfoFlat(Flat):
    """The class inheriting from Flat. Designed to handle test information
    parameters.
    """

    def __init__(self, node):
        """The constructor of the InfoFlat class specifies the information
        test parameters.
        """
        self.info_params = {'name': ['', ''],
                            'description': ['', '']}

        Flat.__init__(self, node, self.info_params)

    def get_test_name(self):
        """Returns the test name."""

        return self.get_parameter('name')

    def get_test_description(self):
        """Returns the test description."""

        return self.get_parameter('description')
