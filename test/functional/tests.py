# tests.py
#
# The master class creating test objects.
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

import xml.etree.ElementTree as ET
import os

from maker import Maker
from merge import Merge


class Tests(object):
    """The master test class creating test objects."""

    def __init__(self, test_directory):
        """The master class constructor.

        Arguments:
        test_directory - The test directory.
        """
        self.tree = ET.parse(os.path.join(test_directory, "test.xml"))
        self.root = self.tree.getroot()
        self.tests = []
        self.create_objects(test_directory)

    def create_objects(self, test_directory):
        """Traverses the XML structure and creates test objects

        Arguments:
        test_directory - The test directory.
        """
        for element in self.root:
            if element.tag == 'maker':
                self.tests.append(Maker(element, test_directory))
            if element.tag == 'merge':
                self.tests.append(Merge(element, test_directory))

    def get_tests(self):
        """Returns a list of created tests.

        Returns:
        A list of valid tests.
        """
        return self.tests
