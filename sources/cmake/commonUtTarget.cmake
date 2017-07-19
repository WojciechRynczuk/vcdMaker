# commonUtTarget.cmake
#
# Common unit test target functions.
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

# Unit tests

set(COMMON_UT_DIR common/test/unitTest)
set(COMMON_UT_STUB_DIR common/test/unitTest/stub)

set(CATCH_HEADERS_DIR 3rdParty/catch/single_include)

set(OUTPUT_UT_DIR output/ut)

set(COMMON_UT_TARGET utCommon)

# Function for unit test creation.
function(add_vcdtools_ut UT_NAME UT_SOURCES)
    add_executable(${UT_NAME} EXCLUDE_FROM_ALL $<TARGET_OBJECTS:${COMMON_UT_TARGET}> ${UT_SOURCES})

    target_include_directories(${UT_NAME} PUBLIC ${COMMON_HEADERS_DIR} ${VMAKER_HEADERS_DIR} ${VMERGE_HEADERS_DIR} ${CATCH_HEADERS_DIR})

    add_common_vcdtools_target_props(${UT_NAME})

    set_target_properties(${UT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_UT_DIR})

    add_test(NAME ${UT_NAME}
             COMMAND ${UT_NAME} --use-colour yes)
    add_dependencies(check ${UT_NAME})
endfunction(add_vcdtools_ut)

add_library(${COMMON_UT_TARGET} EXCLUDE_FROM_ALL OBJECT ${COMMON_UT_DIR}/UtMain.cpp)

target_include_directories(${COMMON_UT_TARGET} PUBLIC ${CATCH_HEADERS_DIR})

add_common_vcdtools_target_props(${COMMON_UT_TARGET})
