# codeCoverage.cmake
#
# Code Coverage generation.
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

option(CODE_COVERAGE_ENABLE "Enable code coverage generation" OFF)
add_feature_info(GCOV CODE_COVERAGE_ENABLE "Code coverage generation enabled.")
if (CODE_COVERAGE_ENABLE)
    # Generate code coverage just for the Linux target
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(CMAKE_BUILD_TYPE Debug ... FORCE )
        set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")
        add_compile_options(--coverage)
    endif()
endif()
