/// @file common/inc/XmlSignalCreator.h
///
/// The generic XML signal creator.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2020 vcdMaker team
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

#include "SignalCreator.h"
#include "Evaluator.h"
#include "ExpressionContext.h"
#include "ExpressionNode.h"

namespace PARSER
{
    /// The class provides means to create XML signal objects.

    ///  An XML signal creator class.
    class XmlSignalCreator : public SignalCreator
    {
        public:
            /// The XML signal creator constructor.
            ///
            /// @param rSignalDescriptorRegistry The signal descriptors registry.
            /// @param rRegEx The regular expression matching the log line.
            /// @param rTimestamp The expression to create the timestamp of the signal.
            /// @param rName The expression to create the name of the signal.
            /// @param rValue The expression to create the value of the signal.
            /// @param rSize The expression to create the size of the signal.
            XmlSignalCreator(SIGNAL::SignalDescriptorRegistry &rSignalDescriptorRegistry,
                             const std::string &rRegEx,
                             const std::string &rTimestamp,
                             const std::string &rName,
                             const std::string &rValue,
                             const std::string &rSize):
                SignalCreator(rSignalDescriptorRegistry, rRegEx),
                m_Timestamp(rTimestamp),
                m_Name(rName),
                m_Value(rValue),
                m_Size(rSize),
                m_TimestampEvaluator("XML"),
                m_DecimalEvaluator("XML"),
                m_FloatEvaluator("XML"),
                m_SizeEvaluator("XML"),
                m_NameEvaluator("XML")
            {
                m_TimestampEvaluator.ParseDecimalString(rTimestamp);
                m_NameEvaluator.ParseStringString(rName);
            }

        protected:
            /// Returns the timestamp of the signal.
            ///
            /// @param rMatch The regular expression groups.
            /// @param lineNumber The log line number.
            TIME::Timestamp GetTimestamp(const std::smatch &rMatch,
                                         INSTRUMENT::Instrument::LineNumberT lineNumber) const;

            /// Returns the name of the signal.
            ///
            /// @param rMatch The regular expression groups.
            std::string GetName(const std::smatch &rMatch) const;

            /// Returns the decimal value of the signal.
            ///
            /// @param rMatch The regular expression groups.
            SafeUInt<uint64_t> GetDecimalValue(const std::smatch &rMatch) const;

            /// Returns the float value of the signal.
            ///
            /// @param rMatch The regular expression groups.
            std::string GetFloatValue(const std::smatch &rMatch) const;

            /// Returns the size of the signal.
            ///
            /// @param rMatch The regular expression groups.
            size_t GetSize(const std::smatch &rMatch) const;

            /// The expression to create the timestamp of the signal.
            const std::string m_Timestamp;

            /// The expression to create the name of the signal.
            const std::string m_Name;

            /// The expression to create the value of the signal.
            const std::string m_Value;

            /// The expression to create the size of the signal.
            const std::string m_Size;

            /// The timestamp evaluator.
            Evaluator m_TimestampEvaluator;

            /// The decimal(vector) value evaluator.
            Evaluator m_DecimalEvaluator;

            /// The float value evaluator.
            Evaluator m_FloatEvaluator;

            /// The size evaluator.
            Evaluator m_SizeEvaluator;

            /// The name evaluator.
            Evaluator m_NameEvaluator;
    };
}
