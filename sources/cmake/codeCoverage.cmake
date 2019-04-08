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

option(CODE_COVERAGE "Enable code coverage generation")
add_feature_info(GCOV CODE_COVERAGE "Code coverage generation enabled.")

if (CODE_COVERAGE)

    # Build type must be Debug
    if (NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
        message(FATAL_ERROR "To generate code coverage data Debug build type must be used.")
    endif()

    # Generate code coverage just for the Linux target
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        add_compile_options(--coverage)
        link_libraries(--coverage)
    else()
        message(FATAL_ERROR "Code coverage generation available only for the GNU compiler.")
    endif()

    # Clean code coverage html
    list(APPEND MAKE_CLEAN_FILES CodeCoverage)
    list(APPEND MAKE_CLEAN_FILES raw.info)
    list(APPEND MAKE_CLEAN_FILES coverage.info)

endif()

add_custom_target(coverage
    COMMAND mkdir CodeCoverage
    COMMAND lcov --directory . --capture --rc lcov_branch_coverage=1 --output-file=raw.info
    COMMAND lcov --remove raw.info '/usr/*' '*/3rdParty/*' '*/test/*' --rc lcov_branch_coverage=1 --output-file=coverage.info
    COMMAND genhtml --output-directory CodeCoverage --rc lcov_branch_coverage=1 coverage.info
    DEPENDS check
    COMMENT "Generating code coverage."
)

