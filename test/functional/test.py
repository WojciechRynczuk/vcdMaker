# test.py
#
# The base test class.
#
# Copyright (c) 2019 vcdMaker team
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

from flat import CommonFlat, InfoFlat


class Test(object):
    """The base test class."""

    def __init__(self, node, test_directory):
        """The base test class constructor.

        Arguments:
        node - The XML node to be read.
        test_directory - The test directory.
        """

        for element in node:
            if (element.tag == 'info'):
                self.info = InfoFlat(element)
            if (element.tag == 'common'):
                self.common = CommonFlat(element, test_directory)

    def get_command(self):
        """Returns a list of command line parameters."""

        return self.command

    def get_output_file(self):
        """Returns the absolute path to the test output file."""

        return self.common.get_output_file()

    def get_golden_file(self):
        """Returns the absolute path to the test golden file."""

        return self.common.get_golden_file()

    def get_stdout_file(self):
        """Returns the absolute path to the test standard output file."""

        return self.common.get_stdout_file()

    def get_name(self):
        """Returns the test name."""

        return self.info.get_test_name()

    def get_description(self):
        """Returns the test description."""

        return self.info.get_test_description()
