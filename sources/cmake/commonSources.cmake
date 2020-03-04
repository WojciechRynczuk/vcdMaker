# commonSources.cmake
#
# List of common source files and directories.
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

# Set common source files.
set(COMMON_SOURCES_DIR common/src)

set(COMMON_SOURCES
    ${COMMON_SOURCES_DIR}/EventSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/FSignal.cpp
    ${COMMON_SOURCES_DIR}/FSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/ISignal.cpp
    ${COMMON_SOURCES_DIR}/ISignalCreator.cpp
    ${COMMON_SOURCES_DIR}/SignalFactory.cpp
    ${COMMON_SOURCES_DIR}/XmlEventSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/XmlFSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/XmlISignalCreator.cpp
    ${COMMON_SOURCES_DIR}/XmlSignalCreator.cpp
    ${COMMON_SOURCES_DIR}/XmlSignalFactory.cpp
    ${COMMON_SOURCES_DIR}/DefaultSignalFactory.cpp
    ${COMMON_SOURCES_DIR}/SignalStructureBuilder.cpp
    ${COMMON_SOURCES_DIR}/Signal.cpp
    ${COMMON_SOURCES_DIR}/SignalDb.cpp
    ${COMMON_SOURCES_DIR}/SourceRegistry.cpp
    ${COMMON_SOURCES_DIR}/TxtParser.cpp
    ${COMMON_SOURCES_DIR}/LogParser.cpp
    ${COMMON_SOURCES_DIR}/LineCounter.cpp
    ${COMMON_SOURCES_DIR}/TimeFrame.cpp
    ${COMMON_SOURCES_DIR}/Utils.cpp
    ${COMMON_SOURCES_DIR}/TimeUnit.cpp
    ${COMMON_SOURCES_DIR}/Logger.cpp
    ${COMMON_SOURCES_DIR}/VCDTracer.cpp)

# Set common header files.
# This shouldn't be needed, but helps IDE project generators.
set(COMMON_HEADERS_DIR common/inc)

set(COMMON_HEADERS
    ${COMMON_HEADERS_DIR}/CliParser.h
    ${COMMON_HEADERS_DIR}/LogParser.h
    ${COMMON_HEADERS_DIR}/LineCounter.h
    ${COMMON_HEADERS_DIR}/TxtParser.h
    ${COMMON_HEADERS_DIR}/EventSignalCreator.h
    ${COMMON_HEADERS_DIR}/EventSignal.h
    ${COMMON_HEADERS_DIR}/FSignalCreator.h
    ${COMMON_HEADERS_DIR}/FSignal.h
    ${COMMON_HEADERS_DIR}/ISignalCreator.h
    ${COMMON_HEADERS_DIR}/ISignal.h
    ${COMMON_HEADERS_DIR}/SignalCreator.h
    ${COMMON_HEADERS_DIR}/SignalFactory.h
    ${COMMON_HEADERS_DIR}/XmlEventSignalCreator.h
    ${COMMON_HEADERS_DIR}/XmlFSignalCreator.h
    ${COMMON_HEADERS_DIR}/XmlISignalCreator.h
    ${COMMON_HEADERS_DIR}/XmlSignalCreator.h
    ${COMMON_HEADERS_DIR}/XmlSignalFactory.h
    ${COMMON_HEADERS_DIR}/DefaultSignalFactory.h
    ${COMMON_HEADERS_DIR}/SignalStructureBuilder.h
    ${COMMON_HEADERS_DIR}/Signal.h
    ${COMMON_HEADERS_DIR}/SourceRegistry.h
    ${COMMON_HEADERS_DIR}/SignalDb.h
    ${COMMON_HEADERS_DIR}/VcdException.h
    ${COMMON_HEADERS_DIR}/VcdExceptionList.h
    ${COMMON_HEADERS_DIR}/Logger.h
    ${COMMON_HEADERS_DIR}/TimeFrame.h
    ${COMMON_HEADERS_DIR}/Utils.h
    ${COMMON_HEADERS_DIR}/TimeUnit.h
    ${COMMON_HEADERS_DIR}/Instrument.h
    ${COMMON_HEADERS_DIR}/VCDTracer.h
    ${COMMON_HEADERS_DIR}/SafeUInt.h
    ${COMMON_HEADERS_DIR}/Timestamp.h
    ${COMMON_HEADERS_DIR}/OutOfMemory.h
    ${VERSION_HEADER})

# 3rd party directories.
set(TCLAP_HEADERS_DIR 3rdParty/tclap/include)

# Other directories.
get_filename_component(DEVEL_SUPPORT_DIR ${PROJECT_SOURCE_DIR}/../development ABSOLUTE)
get_filename_component(ROOT_DIR ${PROJECT_SOURCE_DIR}/.. ABSOLUTE)
