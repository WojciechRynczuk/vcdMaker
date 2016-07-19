# CMakeLists.txt
#
# vcdMaker and vcdMerge CMake file.
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

project(vcdMakerTools)

# Set common source files.
set(COMMON_SOURCES_DIR common/src)

set(COMMON_SOURCES
    ${COMMON_SOURCES_DIR}/FSignal.cpp
    ${COMMON_SOURCES_DIR}/FSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/ISignal.cpp
    ${COMMON_SOURCES_DIR}/ISignalCreator.cpp
    ${COMMON_SOURCES_DIR}/SignalFactory.cpp
    ${COMMON_SOURCES_DIR}/SignalStructureBuilder.cpp
    ${COMMON_SOURCES_DIR}/Signal.cpp
    ${COMMON_SOURCES_DIR}/SignalDb.cpp
    ${COMMON_SOURCES_DIR}/TxtParser.cpp
    ${COMMON_SOURCES_DIR}/LogParser.cpp
    ${COMMON_SOURCES_DIR}/VCDTracer.cpp)

# Set common header files.
# This shouldn't be needed, but helps IDE project generators.
set(COMMON_HEADERS_DIR common/inc)

set(COMMON_HEADERS
    ${COMMON_HEADERS_DIR}/CliParser.h
    ${COMMON_HEADERS_DIR}/LogParser.h
    ${COMMON_HEADERS_DIR}/TxtParser.h
    ${COMMON_HEADERS_DIR}/FSignalCreator.h
    ${COMMON_HEADERS_DIR}/FSignal.h
    ${COMMON_HEADERS_DIR}/ISignalCreator.h
    ${COMMON_HEADERS_DIR}/ISignal.h
    ${COMMON_HEADERS_DIR}/SignalCreator.h
    ${COMMON_HEADERS_DIR}/SignalFactory.h
    ${COMMON_HEADERS_DIR}/SignalStructureBuilder.h
    ${COMMON_HEADERS_DIR}/Signal.h
    ${COMMON_HEADERS_DIR}/SignalDb.h
    ${COMMON_HEADERS_DIR}/VCDTracer.h)

# 3rd party directories.
set(TCLAP_HEADERS_DIR 3rdParty/tclap/include)

# Function for target creation.
function(add_vcdtools_target TARGET_NAME TARGET_SOURCES TARGET_HEADERS TARGET_HEADERS_DIR)
    add_executable(${TARGET_NAME} ${COMMON_SOURCES} ${TARGET_SOURCES} ${COMMON_HEADERS} ${TARGET_HEADERS})

    target_include_directories(${TARGET_NAME} PUBLIC ${COMMON_HEADERS_DIR} ${TARGET_HEADERS_DIR} ${TCLAP_HEADERS_DIR})

    # Set C++14 support.
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 14)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)

    # Set warning flags.
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -pedantic)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        target_compile_options(${TARGET_NAME} PUBLIC /W4)
    endif()
endfunction(add_vcdtools_target)

# Set vcdMaker build.

set(VMAKER_SOURCES_DIR vcdMaker/src)
set(VMAKER_SOURCES
    ${VMAKER_SOURCES_DIR}/vcdMaker.cpp)

set(VMAKER_HEADERS_DIR vcdMaker/inc)
set(VMAKER_HEADERS
    ${VMAKER_HEADERS_DIR}/CliMaker.h)

add_vcdtools_target(vcdMaker
                    ${VMAKER_SOURCES}
                    ${VMAKER_HEADERS}
                    ${VMAKER_HEADERS_DIR})

# Set vcdMerge build.

set(VMERGE_SOURCES_DIR vcdMerge/src)
set(VMERGE_SOURCES
    ${VMERGE_SOURCES_DIR}/vcdMerge.cpp)

set(VMERGE_HEADERS_DIR vcdMerge/inc)
set(VMERGE_HEADERS
    ${VMERGE_HEADERS_DIR}/CliMerge.h)

add_vcdtools_target(vcdMerge
                    ${VMERGE_SOURCES}
                    ${VMERGE_HEADERS}
                    ${VMERGE_HEADERS_DIR})

# Set installation (UNIX-like only)

if (UNIX)
    install(TARGETS vcdMaker vcdMerge
            RUNTIME DESTINATION bin
            COMPONENT runtime)

    install(DIRECTORY common/doc/
            DESTINATION share/doc/${CMAKE_PROJECT_NAME}
            COMPONENT documentation
            PATTERN "*.odt" EXCLUDE)
endif()
