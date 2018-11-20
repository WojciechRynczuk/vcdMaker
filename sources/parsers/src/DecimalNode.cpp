/// @file parsers/src/DecimalNode.cpp
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

#include "DecimalNode.h"

SafeUInt<uint64_t> PARSER::DNDec::EvaluateUint() const
{
    SafeUInt<uint64_t> value = 0;
    std::string stringValue(m_rContext.GetElement(m_Index));
    try
    {
        value = std::stoll(stringValue.c_str(), nullptr, 10);
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Out of range decimal value: " + stringValue);
    }
    catch (const std::invalid_argument &)
    {
        throw EXCEPTIONS::ConversionError("Cannot convert to decimal: ", stringValue);
    }

    return value;
}

SafeUInt<uint64_t> PARSER::DNHex::EvaluateUint() const
{
    SafeUInt<uint64_t> value = 0;
    std::string stringValue(m_rContext.GetElement(m_Index));
    try
    {
        value = std::stoll(stringValue.c_str(), nullptr, 16);
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Out of range decimal value: " + stringValue);
    }
    catch (const std::invalid_argument &)
    {
        throw EXCEPTIONS::ConversionError("Cannot convert to hex: ", stringValue);
    }

    return value;
}

SafeUInt<uint64_t> PARSER::DNAdd::EvaluateUint() const
{
    try
    {
        return m_pLeft->EvaluateUint() + m_pRight->EvaluateUint();
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Overflow while adding.");
    }
}

SafeUInt<uint64_t> PARSER::DNSubtract::EvaluateUint() const
{
    try
    {
        return m_pLeft->EvaluateUint() - m_pRight->EvaluateUint();
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Underflow while substracting.");
    }
}

SafeUInt<uint64_t> PARSER::DNMultiply::EvaluateUint() const
{
    try
    {
        return m_pLeft->EvaluateUint() * m_pRight->EvaluateUint();
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Overflow while multiplying.");
    }
}

SafeUInt<uint64_t> PARSER::DNDivide::EvaluateUint() const
{
    SafeUInt<uint64_t> rightValue = m_pRight->EvaluateUint();
    if (0 == rightValue.GetValue())
    {
        throw EXCEPTIONS::DivByZero("");
    }
    return m_pLeft->EvaluateUint() / rightValue;
}
