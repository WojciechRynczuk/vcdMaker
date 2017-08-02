# comparisonTest.cmake
#
# Comparison test targets.
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

# Comparison functional test.

find_package(PythonInterp 3.5)
set_package_properties(PythonInterp PROPERTIES
                       URL "http://python.org"
                       DESCRIPTION "Python programming language interpretter"
                       TYPE OPTIONAL
                       PURPOSE "Enables comparison test.")

if (PYTHONINTERP_FOUND)
    set(COMPARISON_TEST_SCRIPT ${ROOT_DIR}/test/functional/comparison_test.py)
    set(MAKER_COMPARISON_TEST_DIR ${PROJECT_SOURCE_DIR}/vcdMaker/test/functional)
    set(MERGE_COMPARISON_TEST_DIR ${PROJECT_SOURCE_DIR}/vcdMerge/test/functional)

    add_test(NAME vcdMakerComparisonTest
            COMMAND ${PYTHON_EXECUTABLE} ${COMPARISON_TEST_SCRIPT} -e ./vcdMaker -t ${MAKER_COMPARISON_TEST_DIR}
            WORKING_DIRECTORY ${OUTPUT_DIR_ABSOLUE})

    add_dependencies(check vcdMaker)

    add_test(NAME vcdMergeComparisonTest
            COMMAND ${PYTHON_EXECUTABLE} ${COMPARISON_TEST_SCRIPT} -e ./vcdMerge -t ${MERGE_COMPARISON_TEST_DIR}
            WORKING_DIRECTORY ${OUTPUT_DIR_ABSOLUE})

    add_dependencies(check vcdMerge)
endif()
