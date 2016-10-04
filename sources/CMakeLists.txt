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

# Extract version information
set(VERSION_HEADER common/inc/Version.h)

file(STRINGS ${VERSION_HEADER} VERSION_LINE REGEX "#define D_VERSION_")
string(REGEX MATCHALL "[0-9]+" VERSION_COMPONENTS ${VERSION_LINE})

list(GET VERSION_COMPONENTS 0 VERSION_MAJOR)
list(GET VERSION_COMPONENTS 1 VERSION_MINOR)
list(GET VERSION_COMPONENTS 2 VERSION_PATCH)

# Setup project.
project(vcdMakerTools VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

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
    ${COMMON_SOURCES_DIR}/SourceRegistry.cpp
    ${COMMON_SOURCES_DIR}/TxtParser.cpp
    ${COMMON_SOURCES_DIR}/LogParser.cpp
    ${COMMON_SOURCES_DIR}/LineCounter.cpp
    ${COMMON_SOURCES_DIR}/TimeFrame.cpp
    ${COMMON_SOURCES_DIR}/VCDTracer.cpp)

# Set common header files.
# This shouldn't be needed, but helps IDE project generators.
set(COMMON_HEADERS_DIR common/inc)

set(COMMON_HEADERS
    ${COMMON_HEADERS_DIR}/CliParser.h
    ${COMMON_HEADERS_DIR}/LogParser.h
    ${COMMON_HEADERS_DIR}/LineCounter.h
    ${COMMON_HEADERS_DIR}/TxtParser.h
    ${COMMON_HEADERS_DIR}/FSignalCreator.h
    ${COMMON_HEADERS_DIR}/FSignal.h
    ${COMMON_HEADERS_DIR}/ISignalCreator.h
    ${COMMON_HEADERS_DIR}/ISignal.h
    ${COMMON_HEADERS_DIR}/SignalCreator.h
    ${COMMON_HEADERS_DIR}/SignalFactory.h
    ${COMMON_HEADERS_DIR}/SignalStructureBuilder.h
    ${COMMON_HEADERS_DIR}/Signal.h
    ${COMMON_HEADERS_DIR}/SourceRegistry.h
    ${COMMON_HEADERS_DIR}/SignalDb.h
    ${COMMON_HEADERS_DIR}/VcdExceptions.h
    ${COMMON_HEADERS_DIR}/TimeFrame.h
    ${COMMON_HEADERS_DIR}/VCDTracer.h
    ${VERSION_HEADER})

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
                    "${VMAKER_SOURCES}"
                    "${VMAKER_HEADERS}"
                    ${VMAKER_HEADERS_DIR})

# Set vcdMerge build.

set(VMERGE_SOURCES_DIR vcdMerge/src)
set(VMERGE_SOURCES
    ${VMERGE_SOURCES_DIR}/vcdMerge.cpp
    ${VMERGE_SOURCES_DIR}/Merge.cpp
    ${VMERGE_SOURCES_DIR}/Source.cpp)

set(VMERGE_HEADERS_DIR vcdMerge/inc)
set(VMERGE_HEADERS
    ${VMERGE_HEADERS_DIR}/CliMerge.h
    ${VMERGE_HEADERS_DIR}/Merge.h
    ${VMERGE_HEADERS_DIR}/Source.h)

add_vcdtools_target(vcdMerge
                    "${VMERGE_SOURCES}"
                    "${VMERGE_HEADERS}"
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

    set(AUTHOR "vcdMaker team")
    set(WEBSITE "http://vcdmaker.org")
    set(DESCRIPTION "Commandline tools that can generate VCD files from text logs")

    set(CPACK_PACKAGE_VENDOR ${AUTHOR})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Generates VCD files from text logs")
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_GENERATOR "RPM" "DEB")

    set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_PROCESSOR})
    if (CPACK_SYSTEM_NAME STREQUAL "x86_64")
        set(CPACK_SYSTEM_NAME "amd64")
    endif()

    set(CPACK_RPM_PACKAGE_RELEASE 1)
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    set(CPACK_RPM_PACKAGE_URL ${WEBSITE})
    set(CPACK_RPM_PACKAGE_DESCRIPTION ${DESCRIPTION})

    set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${AUTHOR})
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${DESCRIPTION})
    set(CPACK_DEBIAN_PACKAGE_SECTION "electronics")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${WEBSITE})

    include(CPack)
endif()

# Add test targets

find_package(PythonInterp 3)

if (PYTHONINTERP_FOUND)
    get_filename_component(TEST_SCRIPT_DIR ${PROJECT_SOURCE_DIR}/../development/test ABSOLUTE)

    set(COMPARISON_TEST_SCRIPT ${TEST_SCRIPT_DIR}/comparison_test.py)
    set(COMPARISON_TEST_DIR ${PROJECT_SOURCE_DIR}/vcdMaker/test)

    add_custom_target(comparisonTest
                      COMMAND ${PYTHON_EXECUTABLE} ${COMPARISON_TEST_SCRIPT} -e ./vcdMaker -t ${COMPARISON_TEST_DIR}
                      COMMENT "vcdMaker commparison test"
                      VERBATIM)
endif()
