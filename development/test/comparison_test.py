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
# Files that passed comparison test are removed. Incorrect files are left
# for review.
#
# Todo:
# - Date and version could change and shoudn't be compared.
# - Timebase and counter name could be encoded in file name.
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

import sys
import os
import glob
import collections
import subprocess
import filecmp
import argparse

# Single test case entry.
TestsCase = collections.namedtuple('TestsCase', ['sourceFile', 'vcdFile', 'vcdCounterFile']);

# Source file name pattern.
SOURCE_PATTERN = 'test_*.txt'

# Gold file name components.
VCD_EXTENSION = '.vcd'
COUNTER_POSTFIX = '_counter'

# Test file parameters.
TEST_POSTFIX = '_test'
DEFAULT_TIMEBASE = 'us'
DEFAULT_COUNTER_NAME = 'counter'

def findTests():
  """Builds a list of tests in current directory.

  Test cases that don't have a gold files are not added.

  Return:
  List of TestsCase named tuples.
  """

  testCases = []

  for source_file in glob.glob(SOURCE_PATTERN):
    source_name = os.path.splitext(source_file)[0]

    vcd_name = source_name + VCD_EXTENSION
    if not os.path.isfile(vcd_name):
      vcd_name = ''

    vcd_counter_name = source_name + COUNTER_POSTFIX + VCD_EXTENSION
    if not os.path.isfile(vcd_counter_name):
      vcd_counter_name = ''

    if (not vcd_name) and (not vcd_counter_name):
      print('WARNING: Source file', source_file, 'doesn\'t have any VCD file.')
    else:
      printv('INFO: Adding source file', source_file, 'with golds:', vcd_name, vcd_counter_name)
      testCases.append(TestsCase(source_file, vcd_name, vcd_counter_name))

  return testCases

def runVcdMaker(vcdMaker, inputFile, outputFile, extraArguments=[]):
  """Executes vcdMaker application for given files.

  Arguments:
  vcdMaker       -- vcdMaker executable path
  inputFile      -- name of a input file (*.txt)
  outputFile     -- name of a output file (*.vcd)
  extraArguments -- array of optional extra arguments for vcdMaker

  Return:
  True if conversion was successful, false otherwise.
  """

  common_arguments = [vcdMaker, '-o', outputFile, '-t', DEFAULT_TIMEBASE]
  command = [*common_arguments, *extraArguments, inputFile]

  fds = {}
  if not VERBOSE:
    fds = {'stdout': subprocess.DEVNULL, 'stderr': subprocess.DEVNULL}

  result = subprocess.call(command, **fds)

  if result == 0:
    return True
  else:
    print('ERROR: Source file', inputFile, 'resulted in error: {}'.format(result))
    print('  Command was:', *command)
    return False

def compareGoldAndOutput(goldFile, outputFile):
  """Compares given files.

  Arguments:
  goldFile   -- name of a gold file
  outputFile -- name of a vcdMaker generated file

  Return:
  True if gold and output are equal, false otherwise.
  """

  if filecmp.cmp(goldFile, outputFile):
    print('PASS:', outputFile, 'EQUALS', goldFile)
    return True
  else:
    print('FAIL:', outputFile, 'DOESNT EQUAL', goldFile)
    return False

def executeTest(testCase, vcdMaker):
  """Runs a single test case.

  Arguments:
  testCase -- test case to execute (TestCase named tuple)
  vcdMaker -- vcdMaker executable path

  Return:
  True if test case passed, false otherwise.
  """

  source_name = os.path.splitext(testCase.sourceFile)[0]
  printv('TEST', source_name)

  result = True

  if testCase.vcdFile:
    test_name = source_name + TEST_POSTFIX + VCD_EXTENSION
    if (runVcdMaker(vcdMaker, testCase.sourceFile, test_name) and
        compareGoldAndOutput(testCase.vcdFile, test_name)):
      os.remove(test_name)
    else:
      result = False

  if testCase.vcdCounterFile:
    test_counter_name = source_name + COUNTER_POSTFIX + TEST_POSTFIX + VCD_EXTENSION
    if (runVcdMaker(vcdMaker, testCase.sourceFile, test_counter_name, ['-c', DEFAULT_COUNTER_NAME]) and
        compareGoldAndOutput(testCase.vcdCounterFile, test_counter_name)):
      os.remove(test_name)
    else:
      result = False

  return result

def executeTests(testCases, vcdMaker):
  """Runs all test cases from the list.

  Arguments:
  testCases -- list of test cases to execute
  vcdMaker  -- vcdMaker executable path

  Return:
  True if all test cases passed, false otherwise.
  """

  for testCase in testCases:
    if not executeTest(testCase, vcdMaker):
      return False

  return True

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
    raise RuntimeError('ERROR: ' + args.exec + ' is not an executable')

  if not os.path.exists(args.testdir):
    raise RuntimeError('ERROR: ' + args.testdir + 'doesn\'t exist')

def main():
  """comparison_test script entry point"""

  parser = argparse.ArgumentParser(description='vcdMaker tools comparison testing utility')
  parser.add_argument('--exec', '-e', required=True, help="Path to the vcdMaker executable")
  parser.add_argument('--testdir', '-t', required=True, help="Path to the directory containing tests")
  parser.add_argument('--verbose', '-v', action='store_true', default=False, help="Turns on verbose output")
  args = parser.parse_args()

  checkArguments(args)

  setupVerbose(args.verbose)

  os.chdir(args.testdir)

  if executeTests(findTests(), args.exec):
    print('TEST PASSED')
    result = 0
  else:
    print('TEST FAILED')
    result = 1

  sys.exit(result)

if __name__ == "__main__":
  main()
