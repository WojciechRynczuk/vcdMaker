/// @file parsers/inc/Evaluator.h
///
/// The class provides means for evaluating user format expressions.
///
/// @par Full Description
/// The class provides means for evaluating user format expressions.
/// It is a facade to Flex/Bison generated expression evaluators.
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

#include "ExpressionNode.h"
#include "ExpressionContext.h"

namespace PARSER
{
    /// The expression evaluator class.

    /// The expression evaluator class.
    class Evaluator
    {
        public:

            /// The evaluator constructor.
            ///
            /// It creates the expression evaluator.
            ///
            /// @param rSourceName An expression source name.
            Evaluator(const std::string &rSourceName);

            /// Parses the input decimal string.
            ///
            /// @param inString The input string.
            /// @throws ParsingError On parsing error.
            void ParseDecimalString(const std::string &inString);

            /// Parses the input float string.
            ///
            /// @param inString The input string.
            /// @throws ParsingError On parsing error.
            void ParseFloatString(const std::string &inString);

            /// Parses the input string string.
            ///
            /// @param inString The input string.
            /// @throws ParsingError On parsing error.
            void ParseStringString(const std::string &inString);

            /// Set the expression context.
            ///
            /// The expression is fixed. It is the expression context that
            /// changes over time and must be set with new values.
            ///
            /// @param pGroups The pointer to the parsed regex groups.
            /// @param lineNo The log line number.
            void SetContext(const std::smatch *pGroups, uint64_t lineNo) const;

            /// Returns the calculation context.
            ///
            /// @return The calculation context.
            ExpressionContext &GetContext() const;

            /// Evaluates the expression expecting the 'double' value.
            std::tuple<double, std::string> EvaluateDouble() const;

            /// Evaluates the expression expecting the 'uint' value.
            uint64_t EvaluateUint() const;

            /// Evaluates the expression expecting the 'string' value.
            std::string EvaluateString() const;

            /// Sets the syntax error index.
            void SetSyntaxErrorIndex(size_t index)
            {
                m_SyntaxErrorIndex = index;
            }

            /// The lexer pointer must be a public interface as it is
            /// the expected lexer interface.

            /// The decimal(vector) lexer.
            class DecimalScanner *m_pDecimalLexer;

            /// The float lexer.
            class FloatScanner *m_pFloatLexer;

            /// The string lexer.
            class StringScanner *m_pStringLexer;

        private:
            /// Parses the input decimal stream.
            ///
            /// @param inStream The input stream.
            /// @return True if successfully parsed.
            bool ParseDecimalStream(std::istream &inStream);

            /// Parses the input float stream.
            ///
            /// @param inStream The input stream.
            /// @return True if successfully parsed.
            bool ParseFloatStream(std::istream &inStream);

            /// Parses the input string stream.
            ///
            /// @param inStream The input stream.
            /// @return True if successfully parsed.
            bool ParseStringStream(std::istream &inStream);

            /// Prints parsing error message.
            std::string ParsingErrorMessage(const std::string &parsedExpression) const;

            /// Prints evaluation error message.
            std::string EvaluationErrorMessage(const std::string &evaluationError) const;

            /// Syntax error index
            size_t m_SyntaxErrorIndex = 0;

            /// The expression source name.
            const std::string &m_rSourceName;

            /// The evaluated expression.
            std::string m_Expression;

            /// Calculation context.
            mutable ExpressionContext m_Context;
    };
}
