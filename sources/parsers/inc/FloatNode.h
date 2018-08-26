/// @file parsers/inc/FloatNode.h
///
/// A set of classes for evaluating float nodes.
///
/// @par Full Description
/// A set of classes for evaluating float nodes.
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

#include <cstdlib>
#include <limits>

#include "ExpressionNode.h"
#include "ExpressionContext.h"

namespace PARSER
{
    /// The class represents the constant node type.
    class FNConstant : public ExpressionNode
    {
            /// The constatnt value.
            double m_Value;

        public:
            /// Constructs a constant type node from a value.
            ///
            /// @param rExpContext The expression context.
            /// @param value The constant value used to create the node.
            FNConstant(ExpressionContext &rExpContext, double value) :
                ExpressionNode(rExpContext),
                m_Value(value)
            {
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                return std::make_tuple(m_Value, "");
            }
    };

    /// The class represents the constant node type based on a float string.
    class FNFlt : public ExpressionNode
    {
            /// The index to the regex group containing the decimal string.
            size_t m_Index;

        public:
            /// Constructs a constant type node based on a float string.
            ///
            /// @param rExpContext The expression context.
            /// @param rString The string containing information about the decimal string index in the parsed regex group.
            FNFlt(ExpressionContext &rExpContext, std::string &rString) :
                ExpressionNode(rExpContext)
            {
                std::string stringIndex(rString, FIRST_STRING_CHARACTER_POS, rString.length() - GROUP_WRAPPER_LENGTH);

                // Format of the string: flt(position)
                m_Index = static_cast<size_t>(std::strtoull(stringIndex.c_str(), nullptr, 10));
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double value = 0;
                try
                {
                    value = std::stod(m_rContext.GetElement(m_Index), nullptr);
                }
                catch (const std::invalid_argument&)
                {
                    throw EXCEPTIONS::ConversionError("Cannot convert to double: " + m_rContext.GetElement(m_Index));
                }
                catch (const std::out_of_range&)
                {
                    throw EXCEPTIONS::Overflow("Out of range double value: " + m_rContext.GetElement(m_Index));
                }

                return std::make_tuple(value, m_rContext.GetElement(m_Index));
            }
    };

    /// The class represents the negate node type.
    class FNNegate : public ExpressionNode
    {
            // Calculation subtree.
            ExpressionNode *m_pNode;

        public:
            /// Constructs a negation of the node.
            ///
            /// @param rExpContext The expression context.
            /// @param pNode The pointer to the original node.
            FNNegate(ExpressionContext &rExpContext, ExpressionNode *pNode)
                : ExpressionNode(rExpContext), m_pNode(pNode)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~FNNegate()
            {
                delete m_pNode;
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double value;
                std::string stringValue;
                std::tie(value, stringValue) = m_pNode->EvaluateDouble();
                return std::make_tuple(-value, "");
            }
    };

    /// The class represents the addition node type.
    class FNAdd : public ExpressionNode
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
            FNAdd(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~FNAdd()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double leftValue;
                std::string leftStringValue;
                std::tie(leftValue, leftStringValue) = m_pLeft->EvaluateDouble();

                double rightValue;
                std::string rightStringValue;
                std::tie(rightValue, rightStringValue) = m_pRight->EvaluateDouble();

                if ((std::numeric_limits<double>::max() - leftValue) < rightValue)
                {
                    throw EXCEPTIONS::Overflow("Overflow while adding.");
                }

                return std::make_tuple(leftValue + rightValue, "");
            }
    };

    /// The class represents the subtraction node type.
    class FNSubtract : public ExpressionNode
    {
            /// Left calculation operand.
            ExpressionNode *m_pLeft;

            /// Right calculation operand.
            ExpressionNode *m_pRight;

        public:
            /// Constructs a substraction of nodes.
            ///
            /// @param rExpContext The expression context.
            /// @param pLeft The pointer to the left node.
            /// @param pRight The pointer to the right node.
            FNSubtract(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~FNSubtract()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double leftValue;
                std::string leftStringValue;
                std::tie(leftValue, leftStringValue) = m_pLeft->EvaluateDouble();

                double rightValue;
                std::string rightStringValue;
                std::tie(rightValue, rightStringValue) = m_pRight->EvaluateDouble();

                if ((std::numeric_limits<double>::min() + rightValue) > leftValue)
                {
                    throw EXCEPTIONS::Overflow("Underflow while substracting.");
                }

                return std::make_tuple(leftValue - rightValue, "");
            }
    };

    /// The class represents the multiplication node type.
    class FNMultiply : public ExpressionNode
    {
            /// Left calculation operand.
            ExpressionNode *m_pLeft;

            /// Right calculation operand.
            ExpressionNode *m_pRight;

        public:
            /// Constructs a multiplication of nodes.
            ///
            /// @param rExpContext The expression context.
            /// @param pLeft The pointer to the left node.
            /// @param pRight The pointer to the right node.
            FNMultiply(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~FNMultiply()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double leftValue;
                std::string leftStringValue;
                std::tie(leftValue, leftStringValue) = m_pLeft->EvaluateDouble();

                double rightValue;
                std::string rightStringValue;
                std::tie(rightValue, rightStringValue) = m_pRight->EvaluateDouble();

                if ((std::numeric_limits<double>::max() / leftValue) < rightValue)
                {
                    throw EXCEPTIONS::Overflow("Overflow while multiplying.");
                }

                return std::make_tuple(leftValue * rightValue, "");
            }
    };

    /// The class represents the division node type.
    class FNDivide : public ExpressionNode
    {
            /// Left calculation operand.
            ExpressionNode *m_pLeft;

            /// Right calculation operand.
            ExpressionNode *m_pRight;

        public:
            /// Constructs a division of nodes.
            ///
            /// @param rExpContext The expression context.
            /// @param pLeft The pointer to the left node.
            /// @param pRight The pointer to the right node.
            FNDivide(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~FNDivide()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateDouble()
            virtual std::tuple<double, std::string> EvaluateDouble() const
            {
                double leftValue;
                std::string leftStringValue;
                std::tie(leftValue, leftStringValue) = m_pLeft->EvaluateDouble();

                double rightValue;
                std::string rightStringValue;
                std::tie(rightValue, rightStringValue) = m_pRight->EvaluateDouble();

                if (0 == rightValue)
                {
                    throw EXCEPTIONS::DivByZero("");
                }

                return std::make_tuple(leftValue / rightValue, "");
            }
    };
}
