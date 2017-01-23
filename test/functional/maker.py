# maker.py
#
# A class representing vcdMaker specific test.
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

from flat import Flat, CommonFlat


class Maker(object):
    """A vcdMaker specific test class."""

    def __init__(self, node, test_directory):
        """The Maker class constructor.

        Arguments:
        node - The XML node to be read.
        test_directory - The test directory.
        """

        self.command = []
        self.unique_params = {'input_file': ['', 'Missing input file'],
                              'time_unit': ['', 'Missing time unit'],
                              'line_counter': ['', '']}

        for element in node:
            if (element.tag == 'common'):
                self.common = CommonFlat(element, test_directory)
            if (element.tag == 'unique'):
                self.unique = Flat(element, self.unique_params)

        self.create_command(test_directory)

    def create_command(self, test_directory):
        """Builds the vcdMaker specific command line."""

        self.command.append('-t')
        self.command.append(self.unique.get_parameter('time_unit'))

        if self.unique.get_parameter('line_counter'):
            self.command.append('-c')
            self.command.append(self.unique.get_parameter('line_counter'))

        self.command.append('-o')
        self.command.append(os.path.join(test_directory,
                                         self.common.get_parameter('output_file')))
        self.command.append(os.path.join(test_directory,
                                         self.unique.get_parameter('input_file')))

    def get_command(self):
        """Returns a list of command line parameters."""

        return self.command

    def get_output_file(self):
        """Returns the absolute path to the test output file."""

        return self.common.get_output_file()

    def get_golden_file(self):
        """Returns the absolute path to the test golden file."""

        return self.common.get_golden_file()
