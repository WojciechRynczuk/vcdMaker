# CMakeLists.txt
#
# vcdMaker and vcdMerge CMake file.
#
# This file is split into several other files that include majority
# of CMake code. Those files are dependent on each other through
# the use of variables. Because of that they can't really be treated
# like stand-alone modules.
#
# Most interesting cmake files are:
# - commonSources.cmake: list of all common sources and dirs.
# - parserSources.cmake: list of parser related files.
# - vcdMaker.cmake, vcdMerge.cmake: executable targets with source list.
# - unitTests.cmake: list of unit tests.
# - codeCoverage.cmake: enables creating coverage data. Just for Linux target.
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

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(version)

# Setup project.
project(vcdMakerTools VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

include(commonSources)

include(parserSources)

include(commonTarget)

include(codeCoverage)

include(vcdMaker)

include(vcdMerge)

if (UNIX)
    include(manPages)

    include(install)

    include(installCpack)
endif()

include(check)

include(comparisonTest)

include(commonUtTarget)

include(unitTests)

include(doxygen)

include(pugixml)

feature_summary(WHAT ALL)
