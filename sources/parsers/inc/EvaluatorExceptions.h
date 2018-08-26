/// @file parsers/inc/EvaluatorExceptions.h
///
/// The user expression parser's exceptions.
///
/// @par Full Description
/// The exceptions being raised by the user expression parser.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2018 vcdMaker team
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
/// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#pragma once

#include <stdexcept>

/// The parser's exceptions.
namespace PARSER
{
    namespace EXCEPTIONS
    {
        /// The parsing error. The exception is raised when the user
        /// expressions contains errors.
        class ParsingError : public std::runtime_error
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            ParsingError(const std::string &rMessage) :
                std::runtime_error(rMessage)
            {
            }
        };

        /// The base evaluator exception class.
        class EvaluatorException : public std::runtime_error
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            EvaluatorException(const std::string &rMessage) :
                std::runtime_error(rMessage)
            {
            }
        };

        /// The conversion error. The exception is raised when a string cannot
        /// be successfully converted to a double, decimal or hexadecimal value.
        class ConversionError : public EvaluatorException
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            ConversionError(const std::string &rMessage) :
                EvaluatorException(rMessage)
            {
            }
        };

        /// The overflow error. The arthmetics overflow detection.
        class Overflow : public EvaluatorException
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            Overflow(const std::string &rMessage) :
                EvaluatorException(rMessage)
            {
            }
        };

        /// The regex index is out of range.
        class IndexOutOfRange : public EvaluatorException
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            IndexOutOfRange(const std::string &rMessage) :
                EvaluatorException(rMessage)
            {
            }
        };

        /// The division by zero error.
        class DivByZero : public EvaluatorException
        {
        public:
            /// The exception constructor.
            ///
            /// @param rMessage The exception warning.
            DivByZero(const std::string &rMessage) :
                EvaluatorException("Division by zero." + rMessage)
            {
            }
        };
    }
}

