# parserSources.cmake
#
# List of parser source files and directories.
#
# Copyright (c) 2018 vcdMaker team
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
set(PARSER_SOURCES_DIR parsers/src)
set(PARSER_GEN_SOURCES_DIR parsers/auto)

set(PARSER_SOURCES
    ${PARSER_SOURCES_DIR}/Evaluator.cpp

    ${PARSER_GEN_SOURCES_DIR}/FloatParser.cpp
    ${PARSER_GEN_SOURCES_DIR}/FloatScanner.cpp
    ${PARSER_GEN_SOURCES_DIR}/DecimalScanner.cpp
    ${PARSER_GEN_SOURCES_DIR}/StringScanner.cpp
    ${PARSER_GEN_SOURCES_DIR}/DecimalParser.cpp
    ${PARSER_GEN_SOURCES_DIR}/StringParser.cpp)

# Set common header files.
# This shouldn't be needed, but helps IDE project generators.
set(PARSER_HEADERS_DIR parsers/inc)
set(PARSER_GEN_HEADERS_DIR parsers/auto)

set(PARSER_HEADERS
    ${PARSER_HEADERS_DIR}/EvaluatorExceptions.h
    ${PARSER_HEADERS_DIR}/StringScanner.h
    ${PARSER_HEADERS_DIR}/evaluator.h
    ${PARSER_HEADERS_DIR}/FloatNode.h
    ${PARSER_HEADERS_DIR}/ExpressionContext.h
    ${PARSER_HEADERS_DIR}/FloatScanner.h
    ${PARSER_HEADERS_DIR}/StringNode.h
    ${PARSER_HEADERS_DIR}/ExpressionNode.h
    ${PARSER_HEADERS_DIR}/DecimalScanner.h
    ${PARSER_HEADERS_DIR}/DecimalNode.h
    ${PARSER_GEN_HEADERS_DIR}/DecimalParser.hpp
    ${PARSER_GEN_HEADERS_DIR}/StringParser.hpp
    ${PARSER_GEN_HEADERS_DIR}/stack.hh
    ${PARSER_GEN_HEADERS_DIR}/FlexLexer.h
    ${PARSER_GEN_HEADERS_DIR}/location.hh
    ${PARSER_GEN_HEADERS_DIR}/position.hh
    ${PARSER_GEN_HEADERS_DIR}/FloatParser.hpp)
