#!/usr/bin/env python3

# comparison_test.py
#
# vcdMaker tools comparison testing utility
#
# This script executes tests in a given directory, converts them to VCD
# traces using any of the vcdMaker tools and then compares the results
# to the prepared golden files.
#
# The tests to be executed are specified by the test.xml file located in
# the test directory.
#
# Test files are created in current directory. Files that passed comparison
# test are removed. Incorrect files are left for review.
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

import argparse
import os
import sys

from tests import Tests
from executor import Executor


def check_arguments(args):
    """Checks if given args are correct (executable and path)"""

    if not (os.path.isfile(args.exec) and os.access(args.exec, os.X_OK)):
        raise RuntimeError('ERROR: {} is not an executable'.format(args.exec))

    if not os.path.exists(args.testdir):
        raise RuntimeError('ERROR: {} doesn\'t exist'.format(args.testdir))


def setup_verbose(enable):
    """Setups global VERBOSE flag and printv function"""

    local_printv = print if enable else lambda *a, **k: None
    global printv
    printv = local_printv

    global VERBOSE
    VERBOSE = enable


def main():
    """comparison_test script entry point"""

    parser = argparse.ArgumentParser(description='vcdMaker tools comparison testing utility')
    parser.add_argument('--exec', '-e', required=True, help="Path to the vcdMaker executable")
    parser.add_argument('--testdir', '-t', required=True, help="Path to the directory containing tests")
    parser.add_argument('--verbose', '-v', action='store_true', default=False, help="Turns on verbose output")
    args = parser.parse_args()

    check_arguments(args)
    setup_verbose(args.verbose)

    tests = Tests(args.testdir)
    executor = Executor(args.exec, tests.get_tests())

    result, number_failed, number_total = executor.run()

    if not result:
        print('TEST PASSED ({})'.format(number_total))
        exit_result = 0
    else:
        print('TEST FAILED ({}/{})'.format(number_failed, number_total))
        exit_result = 1

    sys.exit(exit_result)

if __name__ == "__main__":
    main()
