/// @file parsers/src/FloatNode.cpp
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

#include "FloatNode.h"

PARSER::FloatResult PARSER::FNFlt::EvaluateDouble() const
{
    std::string stringValue(m_rContext.GetElement(m_Index));

    return FloatResult(stringValue);
}

PARSER::FloatResult PARSER::FNNegate::EvaluateDouble() const
{
    double value = m_pNode->EvaluateDouble().GetFloatValue();
    return FloatResult(-value);
}

PARSER::FloatResult PARSER::FNAdd::EvaluateDouble() const
{
    double leftValue = m_pLeft->EvaluateDouble().GetFloatValue();
    double rightValue = m_pRight->EvaluateDouble().GetFloatValue();

    if ((std::numeric_limits<double>::max() - leftValue) < rightValue)
    {
        throw EXCEPTIONS::Overflow("Overflow while adding.");
    }

    return FloatResult(leftValue + rightValue);
}

PARSER::FloatResult PARSER::FNSubtract::EvaluateDouble() const
{
    double leftValue = m_pLeft->EvaluateDouble().GetFloatValue();
    double rightValue = m_pRight->EvaluateDouble().GetFloatValue();

    if ((std::numeric_limits<double>::min() + rightValue) > leftValue)
    {
        throw EXCEPTIONS::Overflow("Underflow while substracting.");
    }

    return FloatResult(leftValue - rightValue);
}

PARSER::FloatResult PARSER::FNMultiply::EvaluateDouble() const
{
    double leftValue = m_pLeft->EvaluateDouble().GetFloatValue();
    double rightValue = m_pRight->EvaluateDouble().GetFloatValue();

    if ((std::numeric_limits<double>::max() / leftValue) < rightValue)
    {
        throw EXCEPTIONS::Overflow("Overflow while multiplying.");
    }

    return FloatResult(leftValue * rightValue);
}

PARSER::FloatResult PARSER::FNDivide::EvaluateDouble() const
{
    double leftValue = m_pLeft->EvaluateDouble().GetFloatValue();
    double rightValue = m_pRight->EvaluateDouble().GetFloatValue();

    if (0 == rightValue)
    {
        throw EXCEPTIONS::DivByZero("");
    }

    return FloatResult(leftValue / rightValue);
}
