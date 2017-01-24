# merge.py
#
# A set of classes needed to create a vcdMerge specific test.
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


class Source(object):
    """A class for storing a source specific parameters."""

    def __init__(self, node, test_directory):
        """The Source class constructor.

        Arguments:
        node - The XML node to be read.
        test_directory - The test directory.
        """
        self.parameters = {'format': ['', 'Missing source format.'],
                           'time_stamp': ['', 'Missing source time stamp.'],
                           'time_unit': ['', 'Missing source time unit.'],
                           'prefix': ['', ''],
                           'line_counter': ['', ''],
                           'input_file': ['', 'Missing source input file.']}

        self.data = Flat(node, self.parameters)
        self.source = []
        self.create_source(test_directory)

    def create_source(self, test_directory):
        """Builds the list of source parameters."""
        self.source = [self.data.get_parameter('format'),
                       self.data.get_parameter('time_stamp'),
                       self.data.get_parameter('time_unit'),
                       self.data.get_parameter('prefix'),
                       self.data.get_parameter('line_counter'),
                       os.path.join(test_directory,
                                    self.data.get_parameter('input_file'))]

    def get(self):
        """Returns the source string to be passed as an argument
        to vcdMerge.
        """

        return ','.join(self.source)


class Sources(object):
    """A container for sources."""

    def __init__(self, node, test_directory):
        """The Sources class constructor.

        Arguments:
        node - The XML node to be read.
        test_directory - The test directory.
        """

        self.sources = []

        for element in node.iter(tag='source'):
            self.sources.append(Source(element, test_directory))

    def get(self):
        """Returns a list of sources."""

        return self.sources


class Merge(object):
    """A vcdMerge specific test class."""

    def __init__(self, node, test_directory):
        """The Merge class constructor.

        Arguments:
        node - The XML node to be read.
        test_directory - The test directory.
        """

        self.command = []
        self.unique_params = {'time_unit': ['', '']}

        for element in node:
            if (element.tag == 'common'):
                self.common = CommonFlat(element, test_directory)
            if (element.tag == 'unique'):
                self.unique = Flat(element, self.unique_params)
                for item in element.iter(tag='sources'):
                    self.sources = Sources(item, test_directory)

        self.create_command(test_directory)

    def create_command(self, test_directory):
        """Builds the vcdMerge specific command line."""

        self.command.append('-o')
        self.command.append(os.path.join(test_directory,
                                         self.common.get_parameter('output_file')))

        if self.unique.get_parameter('time_unit'):
            self.command.append('-t')
            self.command.append(self.unique.get_parameter('time_unit'))

        for source in self.sources.get():
            self.command.append(source.get())

    def get_command(self):
        """Returns a list of command line parameters."""

        return self.command

    def get_output_file(self):
        """Returns the absolute path to the test output file."""

        return self.common.get_output_file()

    def get_golden_file(self):
        """Returns the absolute path to the test golden file."""

        return self.common.get_golden_file()
