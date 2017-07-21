# unitTests.cmake
#
# Unit test targets.
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

# List of unit tests.

set(UT_SIGNAL_SOURCES
    ${COMMON_UT_DIR}/Signal.cpp
    ${COMMON_UT_STUB_DIR}/UtilsEmpty.cpp
    ${COMMON_SOURCES_DIR}/Signal.cpp)

add_vcdtools_ut(utSignal "${UT_SIGNAL_SOURCES}")

set(UT_ISIGNAL_SOURCES
    ${COMMON_UT_DIR}/ISignal.cpp
    ${COMMON_SOURCES_DIR}/ISignal.cpp)

add_vcdtools_ut(utISignal "${UT_ISIGNAL_SOURCES}")

set(UT_FSIGNAL_SOURCES
    ${COMMON_UT_DIR}/FSignal.cpp
    ${COMMON_SOURCES_DIR}/FSignal.cpp)

add_vcdtools_ut(utFSignal "${UT_FSIGNAL_SOURCES}")

set(UT_EVENTSIGNAL_SOURCES
    ${COMMON_UT_DIR}/EventSignal.cpp)

add_vcdtools_ut(utEventSignal "${UT_EVENTSIGNAL_SOURCES}")

set(UT_SOURCE_REGISTRY_SOURCES
    ${COMMON_UT_DIR}/SourceRegistry.cpp
    ${COMMON_SOURCES_DIR}/SourceRegistry.cpp)

add_vcdtools_ut(utSourceRegistry "${UT_SOURCE_REGISTRY_SOURCES}")

set(UT_UTILS_SOURCES
    ${COMMON_UT_DIR}/Utils.cpp
    ${COMMON_UT_STUB_DIR}/Signal.cpp
    ${COMMON_SOURCES_DIR}/Utils.cpp)

add_vcdtools_ut(utUtils "${UT_UTILS_SOURCES}")
