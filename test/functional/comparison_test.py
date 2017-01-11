#!/usr/bin/env python3

# comparison_test.py
#
# vcdMaker tools comparison testing utility
#
# This script gathers test log files from a given directory, converts them
# to VCD traces using vcdMaker and then compares to prepared gold files.
#
# It's expected that test case source file will have a name in format
# "test_NAME.txt". Gold file should be named "test_NAME.vcd" for normal
# VCD files and "test_NAME_counter.vcd" for VCD files with line counter
# enabled. Expected timebase is "us" and line counter signal name
# is "counter".
#
# Test files are created in current directory. Files that passed comparison
# test are removed. Incorrect files are left for review.
#
# Todo:
# - Timebase and counter name could be encoded in file name.
# - Improve Python coding.
#
# Copyright (c) 2016 vcdMaker team
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
import collections
import filecmp
import glob
import itertools
import os
import re
import subprocess
import sys

# Single test case entry.
TestsCase = collections.namedtuple('TestsCase', ['sourceDir', 'sourceFile', 'vcdFile', 'vcdCounterFile']);

# Source file name pattern.
SOURCE_PATTERN = 'test_*.txt'

# Gold file name components.
VCD_EXTENSION = '.vcd'
COUNTER_POSTFIX = '_counter'

# Test file parameters.
TEST_POSTFIX = '_test'
DEFAULT_TIMEBASE = 'us'
DEFAULT_COUNTER_NAME = 'counter'

def findTests(sourceDir):
  """Builds a list of tests in current directory.

  Test cases that don't have a gold files are not added.

  Returns:
  List of TestsCase named tuples.
  """

  saved_current_dir = os.getcwd()
  os.chdir(sourceDir)

  test_cases = []

  for source_file in glob.glob(SOURCE_PATTERN):
    source_name = os.path.splitext(source_file)[0]

    vcd_name = source_name + VCD_EXTENSION
    if not os.path.isfile(vcd_name):
      vcd_name = ''

    vcd_counter_name = source_name + COUNTER_POSTFIX + VCD_EXTENSION
    if not os.path.isfile(vcd_counter_name):
      vcd_counter_name = ''

    if (not vcd_name) and (not vcd_counter_name):
      print('WARNING: Source file {} doesn\'t have any VCD file'.format(source_file))
    else:
      printv('INFO: Adding source file {} with golds: {} {}'.format(source_file, vcd_name, vcd_counter_name))
      test_cases.append(TestsCase(sourceDir, source_file, vcd_name, vcd_counter_name))

  os.chdir(saved_current_dir)
  return test_cases

def runVcdMaker(vcdMaker, sourceDir, inputFile, outputFile, extraArguments=[]):
  """Executes vcdMaker application for given files.

  Arguments:
  vcdMaker       -- vcdMaker executable path
  sourceDir      -- input file directory
  inputFile      -- name of a input file (*.txt)
  outputFile     -- name of a output file (*.vcd)
  extraArguments -- array of optional extra arguments for vcdMaker

  Returns:
  True if conversion was successful, false otherwise.
  """

  common_arguments = [vcdMaker, '-o', outputFile, '-t', DEFAULT_TIMEBASE]
  command = [*common_arguments, *extraArguments, os.path.join(sourceDir, inputFile)]

  fds = {}
  if not VERBOSE:
    fds = {'stdout': subprocess.DEVNULL, 'stderr': subprocess.DEVNULL}

  printv('RUNNING:', *command)
  result = subprocess.call(command, **fds)

  if result == 0:
    return True
  else:
    print('ERROR: Source file {} resulted in error: {}'.format(inputFile, result))
    return False

def compareGoldAndOutput(goldDir, goldFileName, outputFileName):
  """Compares given files.

  First three lines can actually change because they contain date and version info.
  Those lines from ouput file are matched against patterns.

  Arguments:
  goldDir        -- gold file directory
  goldFileName   -- name of a gold file
  outputFileName -- name of a vcdMaker generated file

  Returns:
  True if gold and output are equal, false otherwise.
  """

  with open(os.path.join(goldDir, goldFileName)) as gold_file, open(outputFileName) as output_file:
    gold_file.readline()
    output_date_line = output_file.readline()

    if not re.match(r'\$date .+\d\d?, \d\d\d\d \d\d:\d\d:\d\d', output_date_line):
      print('FAIL: DATE WRONG IN {}'.format(outputFileName))
      return False

    gold_date_end_line = gold_file.readline()
    output_date_end_line = output_file.readline()

    if output_date_end_line != gold_date_end_line:
      print('FAIL: DATE END WRONG IN {}'.format(outputFileName))
      return False

    gold_file.readline()
    output_version_line = output_file.readline()

    if not re.match(r'\$version ', output_version_line):
      print('FAIL: VERSION WRONG IN {}'.format(outputFileName))
      return False

    line_nubmer = 4
    for gold_line, output_line in itertools.zip_longest(gold_file, output_file):
      if output_line != gold_line:
         print('FAIL: {} DOESN\'T EQUAL {} AT LINE {}'.format(outputFileName, goldFileName, line_nubmer))
         return False

      line_nubmer += 1

    print('PASS: {} EQUALS {}'.format(outputFileName, goldFileName))
    return True

def executeTest(testCase, vcdMaker):
  """Runs a single test case.

  Arguments:
  testCase -- test case to execute (TestCase named tuple)
  vcdMaker -- vcdMaker executable path

  Returns:
  True if test case passed, false otherwise.
  """

  source_name = os.path.splitext(testCase.sourceFile)[0]
  printv('TEST: {}'.format(source_name))

  result = True

  if testCase.vcdFile:
    test_name = source_name + TEST_POSTFIX + VCD_EXTENSION
    if (runVcdMaker(vcdMaker, testCase.sourceDir, testCase.sourceFile, test_name) and
        compareGoldAndOutput(testCase.sourceDir, testCase.vcdFile, test_name)):
      os.remove(test_name)
    else:
      result = False

  if testCase.vcdCounterFile:
    test_counter_name = source_name + COUNTER_POSTFIX + TEST_POSTFIX + VCD_EXTENSION
    if (runVcdMaker(vcdMaker, testCase.sourceDir, testCase.sourceFile, test_counter_name, ['-c', DEFAULT_COUNTER_NAME]) and
        compareGoldAndOutput(testCase.sourceDir, testCase.vcdCounterFile, test_counter_name)):
      os.remove(test_counter_name)
    else:
      result = False

  return result

def executeTests(testCases, vcdMaker):
  """Runs all test cases from the list.

  Arguments:
  testCases -- list of test cases to execute
  vcdMaker  -- vcdMaker executable path

  Returns tuple of:
  Result of the test: true if all test cases passed, false otherwise.
  Number of failed test cases.
  Number of all test cases.
  """

  number_total = len(testCases)
  number_failed = 0

  for testCase in testCases:
    if not executeTest(testCase, vcdMaker):
      number_failed += 1

  return ((number_failed > 0), number_failed, number_total)

def setupVerbose(enable):
  """Setups global VERBOSE flag and printv function"""

  local_printv = print if enable else lambda *a, **k: None
  global printv
  printv = local_printv

  global VERBOSE
  VERBOSE = enable

def checkArguments(args):
  """Checks if given args are correct (executable and path)"""

  if not (os.path.isfile(args.exec) and os.access(args.exec, os.X_OK)):
    raise RuntimeError('ERROR: {} is not an executable'.format(args.exec))

  if not os.path.exists(args.testdir):
    raise RuntimeError('ERROR: {} doesn\'t exist'.format(args.testdir))

def main():
  """comparison_test script entry point"""

  parser = argparse.ArgumentParser(description='vcdMaker tools comparison testing utility')
  parser.add_argument('--exec', '-e', required=True, help="Path to the vcdMaker executable")
  parser.add_argument('--testdir', '-t', required=True, help="Path to the directory containing tests")
  parser.add_argument('--verbose', '-v', action='store_true', default=False, help="Turns on verbose output")
  args = parser.parse_args()

  checkArguments(args)

  setupVerbose(args.verbose)

  result, number_failed, number_total = executeTests(findTests(args.testdir), args.exec)

  if not result:
    print('TEST PASSED ({})'.format(number_total))
    exit_result = 0
  else:
    print('TEST FAILED ({}/{})'.format(number_failed, number_total))
    exit_result = 1

  sys.exit(exit_result)

if __name__ == "__main__":
  main()
