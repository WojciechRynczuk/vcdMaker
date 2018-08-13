/// @file parsers/inc/StringNode.h
///
/// A set of classes for evaluating string nodes.
///
/// @par Full Description
/// A set of classes for evaluating string nodes.
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

#include "ExpressionNode.h"
#include "ExpressionContext.h"

namespace PARSER
{
    /// The class represents the string constant node type.
    class SNConstant : public ExpressionNode
    {
            /// The constatnt value.
            std::string &m_rString;

        public:
            /// Constructs a constant type node from a value.
            ///
            /// @param rExpContext The expression context.
            /// @param value The constant value used to create the node.
            SNConstant(ExpressionContext &rExpContext, std::string &value) :
                ExpressionNode(rExpContext),
                m_rString(value)
            {
            }

            /// @copydoc ExpressionNode::EvaluateString()
            virtual std::string EvaluateString() const
            {
                return std::string(m_rString, 1, m_rString.length() - 2);
            }
    };

    /// The class represents the string node.
    class SNTxt : public ExpressionNode
    {
            /// The index to the regex group containing the decimal string.
            size_t m_Index;

        public:
            /// Constructs a string node.
            ///
            /// @param rExpContext The expression context.
            /// @param rString The string containing information about the string index in the parsed regex group.
            SNTxt(ExpressionContext &rExpContext, std::string &rString) :
                ExpressionNode(rExpContext)
            {
                // Format of the string: txt(position)
                m_Index = static_cast<size_t>(std::strtoull(std::string(rString, FIRST_STRING_CHARACTER_POS,
                                              rString.length() - GROUP_WRAPPER_LENGTH).c_str(), nullptr, 10));
            }

            /// @copydoc ExpressionNode::EvaluateString()
            virtual std::string EvaluateString() const
            {
                return m_rContext.GetElement(m_Index);
            }
    };

    /// The class represents the addition node type.
    class SNAdd : public ExpressionNode
    {
            /// Left calculation operand.
            ExpressionNode *m_pLeft;

            /// Right calculation operand.
            ExpressionNode *m_pRight;

        public:
            /// Constructs a sum of nodes.
            ///
            /// @param rExpContext The expression context.
            /// @param pLeft The pointer to the left node.
            /// @param pRight The pointer to the right node.
            SNAdd(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~SNAdd()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateString()
            virtual std::string EvaluateString() const
            {
                return m_pLeft->EvaluateString() + m_pRight->EvaluateString();
            }
    };
}
