# executor.py
#
# The common test executor.
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

import subprocess
import itertools
import re
import os
import sys


class Executor(object):
    """A test executor class."""

    def __init__(self, executable, tests, verbose):
        """The test executor class constructor.

        Arguments:
        executable - The absolute path to the executable to be tested.
        tests - A list of tests to be executed.
        verbose - If True the verbose output mode is enabled
        """
        self.executable = executable
        self.tests = tests
        self.output_filename = ''
        self.golden_filename = ''
        self.stdout_filename = ''
        self.stdout_output = ''
        self.verbose = verbose

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
            self.output_filename = test.get_output_file()
            self.golden_filename = test.get_golden_file()
            self.stdout_filename = test.get_stdout_file()
            self.stdout_output = test.get_stdout_file() + '.txt'
            ret = subprocess.run(cmd, stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE)
            if self.verbose:
                print('TEST: ', test.get_name())
                print('DESCRIPTION: ', test.get_description())
                print('RUNNING: ', *cmd)
                print(ret.stdout.decode(sys.stdout.encoding))

            if ret.returncode == 0:
                with open(self.stdout_output, 'w', newline='') as stdout_file:
                    if ret.stderr:
                        print(ret.stderr.decode(sys.stderr.encoding), file=stdout_file)
                    print(ret.stdout.decode(sys.stdout.encoding), file=stdout_file)
                    stdout_file.close()

            if ret.returncode != 0 and self.golden_filename is not None:
                print('Test FAILED for an unknown reason.')
                failed += 1
                continue

            if ret.returncode != 0 and self.golden_filename is None:
                with open(self.stdout_output, 'w', newline='') as stdout_file:
                    print(ret.stderr.decode(sys.stderr.encoding), file=stdout_file)
                    stdout_file.close()

            if self.is_gold_and_output_equal() and self.is_standard_output_equal():
                try:
                    os.remove(test.get_output_file())
                except OSError:
                    pass
                os.remove(self.stdout_output)
                passed += 1
            else:
                failed += 1
        return failed, failed, failed+passed

    def is_gold_and_output_equal(self):
        """Compares the output and the golden file.

        Returns:
        True if the golden and the output are equal, false otherwise.
        """

        if not self.golden_filename:
            return True

        with open(self.golden_filename) as golden_file, open(self.output_filename) as output_file:

            if not self.is_date_equal(golden_file, output_file):
                return False

            if not self.is_version_equal(golden_file, output_file):
                return False

            if not self.is_body_equal(golden_file, output_file):
                return False

            print('PASS: {} EQUALS {}'.format(self.output_filename, self.golden_filename))
            return True

    def is_standard_output_equal(self):
        """Compares the standard output with the reference file.

        Returns:
        True if the standard output and the reference file are equal, false otherwise.
        """

        line_number = 1
        with open(self.stdout_filename) as stdout_ref, open(self.stdout_output) as stdout_out:
            for stdout_line, stdref_line in itertools.zip_longest(stdout_out, stdout_ref):
                if os.name == 'nt':
                    stdout_line = re.sub(r'(\w+\\[^\s,\.\{]+\\)', '', stdout_line)
                else:
                    stdout_line = re.sub(r'(\/[^\s,\.\{]+\/)', '', stdout_line)
                stdref_line = re.sub(r'(\/[^\s,\.\{]+\/)', '', stdref_line)
                if stdout_line != stdref_line:
                    print('FAIL: STDOUT DOESN\'T EQUAL {} AT LINE {}'.format(self.stdout_filename, line_number))
                    return False
                line_number += 1

            print('PASS: STDOUT EQUALS {}'.format(self.output_filename))
            return True

    def is_date_equal(self, golden_file, output_file):
        """Compares dates.

        Arguments:
        golden_file - the golden file handle
        output_file - the output file handle

        Returns:
        True if dates are matching, false otherwise.
        """

        golden_file.readline()
        output_date_line = output_file.readline()

        if not re.match(r'\$date\s+[a-zA-Z]{3} [a-zA-Z]{3} {1,2}\d{1,2} \d\d:\d\d:\d\d \d{4}',
                        output_date_line):
            print('FAIL: DATE WRONG IN {}'.format(self.output_filename))
            return False

        gold_date_end_line = golden_file.readline()
        output_date_end_line = output_file.readline()

        if output_date_end_line != gold_date_end_line:
            print('FAIL: DATE END WRONG IN {}'.format(self.output_filename))
            return False

        return True

    def is_version_equal(self, golden_file, output_file):
        """Compares versions.

        Arguments:
        golden_file - the golden file handle
        output_file - the output file handle

        Returns:
        True if versions are matching, false otherwise.
        """

        golden_file.readline()
        output_version_line = output_file.readline()

        if not re.match(r'\$version ', output_version_line):
            print('FAIL: VERSION WRONG IN {}'.format(self.output_filename))
            return False

        return True

    def is_body_equal(self, golden_file, output_file):
        """Compares bodies.

        Arguments:
        golden_file - the golden file handle
        output_file - the output file handle

        Returns:
        True if bodies are matching, false otherwise.
        """

        line_nubmer = 4
        for gold_line, output_line in itertools.zip_longest(golden_file, output_file):
            if output_line != gold_line:
                print('FAIL: {} DOESN\'T EQUAL {} AT LINE {}'.format(self.output_filename, self.golden_filename, line_nubmer))
                return False

            line_nubmer += 1

        print('PASS: {} EQUALS {}'.format(self.output_filename, self.golden_filename))
        return True
