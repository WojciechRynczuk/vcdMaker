/// @file parsers/inc/FloatResult.h
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

#pragma once

#include <string>

namespace PARSER
{
    /// The float result class
    class FloatResult
    {
        public:
            /// The string based float constructor.
            ///
            /// @param rFloatString The string from which the float result is constructed.
            FloatResult(const std::string &rFloatString);

            /// The direct float constructor.
            ///
            /// @param floatValue The float value from which the float result is constructed.
            FloatResult(double floatValue) :
                m_Value(floatValue),
                m_String("")
            {}

            /// Returns the value of the float result.
            double GetFloatValue() const
            {
                return m_Value;
            }

            /// Returns the string representing the value of the float result.
            std::string GetFloatString() const;

        private:

            /// The float value.
            double m_Value;

            /// The float string.
            const std::string m_String;
    };
}
