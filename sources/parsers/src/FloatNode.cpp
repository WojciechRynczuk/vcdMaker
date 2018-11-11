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

std::tuple<double, std::string> PARSER::FNFlt::EvaluateDouble() const
{
    double value = 0;
    std::string stringValue(m_rContext.GetElement(m_Index));
    try
    {
        value = std::stod(stringValue, nullptr);
    }
    catch (const std::invalid_argument &)
    {
        if (IsStringEmpty(stringValue))
        {
            throw EXCEPTIONS::EmptyString();
        }
        throw EXCEPTIONS::ConversionError("Cannot convert to double: " + stringValue);
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Out of range double value: " + stringValue);
    }

    return std::make_tuple(value, stringValue);
}

std::tuple<double, std::string> PARSER::FNNegate::EvaluateDouble() const
{
    double value;
    std::string stringValue;
    std::tie(value, stringValue) = m_pNode->EvaluateDouble();
    return std::make_tuple(-value, "");
}

std::tuple<double, std::string> PARSER::FNAdd::EvaluateDouble() const
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

std::tuple<double, std::string> PARSER::FNSubtract::EvaluateDouble() const
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
std::tuple<double, std::string> PARSER::FNMultiply::EvaluateDouble() const
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

std::tuple<double, std::string> PARSER::FNDivide::EvaluateDouble() const
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
