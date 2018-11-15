/// @file common/src/XmlSignalCreator.cpp
///
/// The XML signal creator.
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

#include "XmlSignalCreator.h"

TIME::Timestamp PARSER::XmlSignalCreator::GetTimestamp(std::smatch &rMatch,
                                                       INSTRUMENT::Instrument::LineNumberT lineNumber)
{
    m_TimestampEvaluator.SetContext(&rMatch, lineNumber);
    return m_TimestampEvaluator.EvaluateUint();
}

std::string PARSER::XmlSignalCreator::GetName(std::smatch &rMatch)
{
    m_NameEvaluator.SetContext(&rMatch, 0);
    return m_NameEvaluator.EvaluateString();
}

SafeUInt<uint64_t> PARSER::XmlSignalCreator::GetDecimalValue(std::smatch &rMatch)
{
    m_DecimalEvaluator.SetContext(&rMatch, 0);
    return m_DecimalEvaluator.EvaluateUint();
}

std::string PARSER::XmlSignalCreator::GetFloatValue(std::smatch &rMatch)
{
    m_FloatEvaluator.SetContext(&rMatch, 0);

    double value;
    std::string stringValue;
    std::tie(value, stringValue) = m_FloatEvaluator.EvaluateDouble();

    return stringValue;
}

size_t PARSER::XmlSignalCreator::GetSize(std::smatch &rMatch)
{
    m_SizeEvaluator.SetContext(&rMatch, 0);
    return static_cast<size_t>(m_SizeEvaluator.EvaluateUint());
}
