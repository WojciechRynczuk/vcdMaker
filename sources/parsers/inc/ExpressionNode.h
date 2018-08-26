/// @file parsers/inc/ExpressionNode.h
///
/// The base expression node class.
///
/// @par Full Description
/// The base expression node class.
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

#include <string>
#include <tuple>
#include <algorithm>

#include "SafeUInt.h"
#include "EvaluatorExceptions.h"

namespace PARSER
{
    /// Forward declaration of the expression context class.
    class ExpressionContext;

    /// The abstract expression node.
    ///
    /// The class defines the expression node interface.
    class ExpressionNode
    {
        public:

            /// Constructs the expression node.
            ///
            /// The expression context constructor.
            /// @param rExpContext The expression context.
            ExpressionNode(ExpressionContext &rExpContext) :
                m_rContext(rExpContext)
            {}

            /// Destroys the expression node.
            virtual ~ExpressionNode()
            {
            }

            /// Evaluates the complete 'uint' tree and returns the expression value.
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                return 0;
            }

            /// Evaluates the complete 'double' tree and returns the expression value.
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                return std::make_tuple(0.0, "");
            }

            /// Evaluates the complete 'double' tree and returns the expression value.
            virtual std::string EvaluateString() const
            {
                return "";
            }

        protected:
            /// Checks if the given string is a valid decimal number.
            ///
            /// @param rDecimalString A string to be validated.
            bool IsDecimal(const std::string &rDecimalString) const
            {
                return (std::all_of(rDecimalString.begin(),
                    rDecimalString.end(),
                    [](char i) { return (i >= '0' && i <= '9'); }));
            }

            /// Checks if the given string is a valid hex number.
            ///
            /// @param rHexString A string to be validated.
            bool IsHex(const std::string &rHexString) const
            {
                return (std::all_of(rHexString.begin(),
                    rHexString.end(),
                    [](char i) { return ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F')); }));
            }

            /// The beginning of the index string.
            const size_t FIRST_STRING_CHARACTER_POS = 4;

            /// The length of the command and parentheses. E.g. 'dec()'.
            const size_t GROUP_WRAPPER_LENGTH = 5;

            /// The expression context.
            ExpressionContext &m_rContext;
    };
}
