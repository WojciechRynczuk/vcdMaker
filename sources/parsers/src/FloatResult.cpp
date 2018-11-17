/// @file parsers/src/FloatResult.cpp
///
/// A class representing the result of float calculations.
///
/// @par Full Description
/// A class representing the result of float calculations.
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

#include <sstream>

#include "FloatResult.h"
#include "EvaluatorExceptions.h"

PARSER::FloatResult::FloatResult(const std::string &rFloatString) :
    m_String(rFloatString)
{
    try
    {
        m_Value = std::stod(rFloatString, nullptr);
    }
    catch (const std::invalid_argument &)
    {
        throw EXCEPTIONS::ConversionError("Cannot convert to double: ", rFloatString);
    }
    catch (const std::out_of_range &)
    {
        throw EXCEPTIONS::Overflow("Out of range double value: " + rFloatString);
    }
}

std::string PARSER::FloatResult::GetFloatString() const
{
    if (m_String.empty())
    {
        std::ostringstream strStream;
        strStream << m_Value;
        return strStream.str();
    }
    return m_String;
}
