/// @file parsers/inc/DecimalNode.h
///
/// A set of classes for evaluating decimal nodes.
///
/// @par Full Description
/// A set of classes for evaluating decimal nodes.
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

#include <vector>

#include "ExpressionNode.h"
#include "ExpressionContext.h"

namespace PARSER
{
    /// The class represents the constant node type.
    class DNConstant : public ExpressionNode
    {
            /// The constatnt value.
            SafeUInt<uint64_t> m_Value;

        public:
            /// Constructs a constant type node from a value.
            ///
            /// @param rExpContext The expression context.
            /// @param value The constant value used to create the node.
            DNConstant(ExpressionContext &rExpContext, uint64_t value) :
                ExpressionNode(rExpContext),
                m_Value(value)
            {
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                return m_Value;
            }
    };

    /// The class represents the constant node type based on a decimal string.
    class DNDec : public ExpressionNode
    {
            /// The index to the regex group containing the decimal string.
            size_t m_Index;

        public:
            /// Constructs a constant type node based on a decimal string.
            ///
            /// @param rExpContext The expression context.
            /// @param rString The string containing information about the decimal string index in the parsed regex group.
            DNDec(ExpressionContext &rExpContext, std::string &rString) :
                ExpressionNode(rExpContext)
            {
                std::string stringIndex(rString, FIRST_STRING_CHARACTER_POS, rString.length() - GROUP_WRAPPER_LENGTH);

                // Format of the string: dec(position)
                m_Index = static_cast<size_t>(std::strtoull(stringIndex.c_str(), nullptr, 10));
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                SafeUInt<uint64_t> value = 0;
                if (IsDecimal(m_rContext.GetElement(m_Index)))
                {
                    try
                    {
                        value = std::stoll(m_rContext.GetElement(m_Index).c_str(), nullptr, 10);
                    }
                    catch (const std::out_of_range&)
                    {
                        throw EXCEPTIONS::Overflow("Out of range decimal value: " + m_rContext.GetElement(m_Index));
                    }
                }
                else
                {
                    throw EXCEPTIONS::ConversionError("Cannot convert to decimal: " + m_rContext.GetElement(m_Index));
                }

                return value;
            }
    };

    /// The class represents the constant node type based on a hexadecimal string.
    class DNHex : public ExpressionNode
    {
            /// The index to the regex group containing the hexadecimal string.
            size_t m_Index;

        public:
            /// Constructs a constant type node based on a hexadecimal string.
            ///
            /// @param rExpContext The expression context.
            /// @param rString The string containing information about the hexadecimal string index in the parsed regex group.
            DNHex(ExpressionContext &rExpContext, std::string &rString) :
                ExpressionNode(rExpContext)
            {
                std::string stringIndex(rString, FIRST_STRING_CHARACTER_POS, rString.length() - GROUP_WRAPPER_LENGTH);

                // Format of the string: hex(position)
                m_Index = static_cast<size_t>(std::strtoull(stringIndex.c_str(), nullptr, 10));
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                SafeUInt<uint64_t> value = 0;
                if (IsHex(m_rContext.GetElement(m_Index)))
                {
                    try
                    {
                        value = std::stoll(m_rContext.GetElement(m_Index).c_str(), nullptr, 16);
                    }
                    catch (const std::out_of_range&)
                    {
                        throw EXCEPTIONS::Overflow("Out of range decimal value: " + m_rContext.GetElement(m_Index));
                    }
                }
                else
                {
                    throw EXCEPTIONS::ConversionError("Cannot convert to hex: " + m_rContext.GetElement(m_Index));
                }

                return value;
            }
    };

    /// The class represents the constant type of nodes based on a log line number.
    class DNLine : public ExpressionNode
    {
            /// The constant value returned.
            SafeUInt<uint64_t> m_Value;

        public:
            /// Constructa a constant node from a value.
            DNLine(ExpressionContext &expContext)
                : ExpressionNode(expContext), m_Value(0)
            {
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                return m_rContext.GetLineNo();
            }
    };

    /// The class represents the addition node type.
    class DNAdd : public ExpressionNode
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
            DNAdd(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~DNAdd()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                try
                {
                    return m_pLeft->EvaluateUint() + m_pRight->EvaluateUint();
                }
                catch (const std::out_of_range&)
                {
                    throw EXCEPTIONS::Overflow("Overflow while adding.");
                }
            }
    };

    /// The class represents the subtraction node type.
    class DNSubtract : public ExpressionNode
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
            DNSubtract(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~DNSubtract()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                try
                {
                    return m_pLeft->EvaluateUint() - m_pRight->EvaluateUint();
                }
                catch (const std::out_of_range&)
                {
                    throw EXCEPTIONS::Overflow("Underflow while substracting.");
                }
            }
    };

    /// The class represents the multiplication node type.
    class DNMultiply : public ExpressionNode
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
            DNMultiply(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~DNMultiply()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                try
                {
                    return m_pLeft->EvaluateUint() * m_pRight->EvaluateUint();
                }
                catch(const std::out_of_range&)
                {
                    throw EXCEPTIONS::Overflow("Overflow while multiplying.");
                }
            }
    };

    /// The class represents the division node type.
    class DNDivide : public ExpressionNode
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
            DNDivide(ExpressionContext &rExpContext, ExpressionNode *pLeft, ExpressionNode *pRight)
                : ExpressionNode(rExpContext), m_pLeft(pLeft), m_pRight(pRight)
            {
            }

            /// @copydoc ExpressionNode::~ExpressionNode()
            virtual ~DNDivide()
            {
                delete m_pLeft;
                delete m_pRight;
            }

            /// @copydoc ExpressionNode::EvaluateUint()
            virtual SafeUInt<uint64_t> EvaluateUint() const
            {
                SafeUInt<uint64_t> rightValue = m_pRight->EvaluateUint();
                if (0 == rightValue.GetValue())
                {
                    throw EXCEPTIONS::DivByZero("");
                }
                return m_pLeft->EvaluateUint() / rightValue;
            }
    };
}
