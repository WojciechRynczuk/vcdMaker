/// @file parsers/inc/ExpressionContext.h
///
/// The class provides the context for calculating the expressions value.
///
/// @par Full Description
/// The class provides the context for calculating the expressions value.
/// These are the regex groups as well as the log line number.
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
#include <regex>

#include "ExpressionNode.h"

namespace PARSER
{
    /// The class provides the context for calculating the expressions value.

    /// The expression calculation context class.
    class ExpressionContext
    {
        public:

            /// The expression context constructor.
            ///
            /// It creates the expression context which is later used during
            /// calculating the expression's value.
            ///
            /// @param pGroups The pointer to the parsed regex groups.
            /// @param lineNo The log line number.
            ExpressionContext(const std::smatch *pGroups, uint64_t lineNo) :
                m_pGroups(pGroups),
                m_LineNo(lineNo)
            {}

            /// Free the expression.
            ~ExpressionContext()
            {
                delete m_pExpression;
            }

            /// Set the expression context.
            ///
            /// The expression is fixed. It is the expression context that
            /// changes over time and must be set with new values.
            ///
            /// @param pGroups The pointer to the parsed regex groups.
            /// @param lineNo The log line number.
            void Set(const std::smatch *pGroups, uint64_t lineNo) const
            {
                m_pGroups = pGroups;
                m_LineNo = lineNo;
            }

            /// Return the string for the given regex group.
            ///
            /// The string related to the regex group specified
            /// by the index is returned.
            ///
            /// @param index The index of the regex group content to be returned.
            /// @return String representing the given regex group.
            std::string GetElement(size_t index) const
            {
                if (static_cast<int>(index) > m_pGroups->size())
                {
                    throw EXCEPTIONS::IndexOutOfRange("Regex group index out of range: " + std::to_string(index));
                }
                return (*m_pGroups)[index].str();
            }

            /// Return the log line number.
            ///
            /// The log line number is returned.
            ///
            /// @return Positive integer representing the log line number.
            uint64_t GetLineNo() const
            {
                return m_LineNo;
            }

            /// Set the expression reference.
            ///
            /// The expression reference is set by parser here.
            ///
            /// @param pExpression The pointer to the parsed expression.
            void SetExpression(PARSER::ExpressionNode *pExpression)
            {
                m_pExpression = pExpression;
            }

            /// Return the pointer to the expression.
            ///
            /// The expression pointer is returned.
            ///
            /// @return The expression pointer.
            ExpressionNode *GetExpression() const
            {
                return m_pExpression;
            }

        private:
            /// A pointer to the regex groups (the context of the expression).
            const mutable std::smatch *m_pGroups;

            /// The log line number.
            mutable uint64_t m_LineNo;

            /// The expression.
            ExpressionNode *m_pExpression;
    };
}
