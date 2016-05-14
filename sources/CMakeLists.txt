# CMakeLists.txt
#
# vcdMaker CMake file.
#
# Copyright (c) 2016 Wojciech Rynczuk
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
set(SOURCES_DIR src)

set(SOURCES
    ${SOURCES_DIR}/CliParser.cpp
    ${SOURCES_DIR}/CliParserImpl.cpp
    ${SOURCES_DIR}/FSignal.cpp
    ${SOURCES_DIR}/FSignalCreator.cpp
    ${SOURCES_DIR}/ISignal.cpp
    ${SOURCES_DIR}/ISignalCreator.cpp
    ${SOURCES_DIR}/SignalFactory.cpp
	${SOURCES_DIR}/SignalStructureBuilder.cpp
    ${SOURCES_DIR}/Signal.cpp
    ${SOURCES_DIR}/vcdMaker.cpp
    ${SOURCES_DIR}/VCDTracer.cpp)

# Set header files. This shouldn't be needed, but helps IDE project generators.
set(HEADERS_DIR inc)

set(HEADERS
    ${HEADERS_DIR}/CliParser.h
    ${HEADERS_DIR}/CliParserImpl.h
    ${HEADERS_DIR}/FSignalCreator.h
    ${HEADERS_DIR}/FSignal.h
    ${HEADERS_DIR}/ISignalCreator.h
    ${HEADERS_DIR}/ISignal.h
    ${HEADERS_DIR}/SignalCreator.h
    ${HEADERS_DIR}/SignalFactory.h
	${SOURCES_DIR}/SignalStructureBuilder.h
    ${HEADERS_DIR}/Signal.h
    ${HEADERS_DIR}/VCDTracer.h)

# Create target.
set(VCDMAKER_TARGET vcdMaker)

add_executable(${VCDMAKER_TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${VCDMAKER_TARGET} PUBLIC ${HEADERS_DIR})

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
