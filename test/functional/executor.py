# executor.py
#
# The common test executor.
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

import subprocess
import itertools
import re
import os


class Executor(object):
    """A test executor class."""

    def __init__(self, executable, tests):
        """The test executor class constructor.

        Arguments:
        executable - The absolute path to the executable to be tested.
        tests - A list of tests to be executed.
        """
        self.executable = executable
        self.tests = tests

    def run(self):
        """Runs the tests.

        Returns:
        status, failed, total
        status - >0 if any of the tests failed
        failed - the number of failed tests
        total  - the total number of the tests executed
        """
        failed = 0
        passed = 0
        for test in self.tests:
            cmd = [self.executable, *test.get_command()]
            subprocess.run(cmd, stdout=subprocess.DEVNULL,
                           stderr=subprocess.DEVNULL)
            if (self.compareGoldAndOutput(test.get_golden_file(),
                                          test.get_output_file()) is True):
                os.remove(test.get_output_file())
                passed += 1
            else:
                failed += 1
        return failed, failed, failed+passed

    def compareGoldAndOutput(self, golden_filename, output_filename):
        """Compares given files.

        First three lines can actually change because they contain date
        and version info. Those lines from ouput file are matched against
        patterns.

        Arguments:
        golden_filename-- name of a gold file
        outputFileName -- name of a vcdMaker generated file

        Returns:
        True if gold and output are equal, false otherwise.
        """

        with open(golden_filename) as gold_file, open(output_filename) as output_file:
            gold_file.readline()
            output_date_line = output_file.readline()

            if not re.match(r'\$date .+\d\d?, \d\d\d\d \d\d:\d\d:\d\d',
                            output_date_line):
                print('FAIL: DATE WRONG IN {}'.format(output_filename))
                return False

            gold_date_end_line = gold_file.readline()
            output_date_end_line = output_file.readline()

            if output_date_end_line != gold_date_end_line:
                print('FAIL: DATE END WRONG IN {}'.format(output_filename))
                return False

            gold_file.readline()
            output_version_line = output_file.readline()

            if not re.match(r'\$version ', output_version_line):
                print('FAIL: VERSION WRONG IN {}'.format(output_filename))
                return False

            line_nubmer = 4
            for gold_line, output_line in itertools.zip_longest(gold_file, output_file):
                if output_line != gold_line:
                    print('FAIL: {} DOESN\'T EQUAL {} AT LINE {}'.format(output_filename, golden_filename, line_nubmer))
                    return False

                line_nubmer += 1

            print('PASS: {} EQUALS {}'.format(output_filename, golden_filename))
            return True
