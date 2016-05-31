# CMakeLists.txt
#
# vcdMaker CMake file.
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

cmake_minimum_required(VERSION 3.0)

project(vcdMaker)

# Set source files.
set(COMMON_SOURCES_DIR common/src)
set(VMAKER_SOURCES_DIR vcdMaker/src)

set(SOURCES
    ${COMMON_SOURCES_DIR}/FSignal.cpp
    ${COMMON_SOURCES_DIR}/FSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/ISignal.cpp
    ${COMMON_SOURCES_DIR}/ISignalCreator.cpp
    ${COMMON_SOURCES_DIR}/SignalFactory.cpp
    ${COMMON_SOURCES_DIR}/SignalStructureBuilder.cpp
    ${COMMON_SOURCES_DIR}/Signal.cpp
    ${VMAKER_SOURCES_DIR}/vcdMaker.cpp
    ${COMMON_SOURCES_DIR}/VCDTracer.cpp)

# Set header files. This shouldn't be needed, but helps IDE project generators.
set(COMMON_HEADERS_DIR common/inc)
set(VMAKER_HEADERS_DIR vcdMaker/inc)

set(HEADERS
    ${COMMON_HEADERS_DIR}/CliParser.h
    ${VMAKER_HEADERS_DIR}/CliMaker.h
    ${COMMON_HEADERS_DIR}/FSignalCreator.h
    ${COMMON_HEADERS_DIR}/FSignal.h
    ${COMMON_HEADERS_DIR}/ISignalCreator.h
    ${COMMON_HEADERS_DIR}/ISignal.h
    ${COMMON_HEADERS_DIR}/SignalCreator.h
    ${COMMON_HEADERS_DIR}/SignalFactory.h
    ${COMMON_HEADERS_DIR}/SignalStructureBuilder.h
    ${COMMON_HEADERS_DIR}/Signal.h
    ${COMMON_HEADERS_DIR}/VCDTracer.h)

# 3rd party directories
set(TCLAP_HEADERS_DIR 3rdParty/tclap/include)

# Create target.
set(VCDMAKER_TARGET vcdMaker)

add_executable(${VCDMAKER_TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${VCDMAKER_TARGET} PUBLIC ${COMMON_HEADERS_DIR} ${VMAKER_HEADERS_DIR} ${TCLAP_HEADERS_DIR})

# Set C++14 support.
set_target_properties(${VCDMAKER_TARGET} PROPERTIES CXX_STANDARD 14)
set_target_properties(${VCDMAKER_TARGET} PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${VCDMAKER_TARGET} PROPERTIES CXX_STANDARD_REQUIRED ON)

# Set warning flags.
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  target_compile_options(${VCDMAKER_TARGET} PUBLIC -Wall -Wextra -pedantic)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(${VCDMAKER_TARGET} PUBLIC /W4)
endif()
