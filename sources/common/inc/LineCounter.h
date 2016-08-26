/// @file LineCounter.h
///
/// The line counting class.
///
/// @par Full Description
/// The object of this class allows for keeping a record of the line
/// counting information. It is supposed to be used by the text parser.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2016 vcdMaker team
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

#include <map>
#include <array>

namespace PARSER
{
    /// The line counter class.
    class LineCounter
    {
        public:
            /// A line number type.
            using LineNumberT = unsigned int;

            /// A line counter record.
            using LineCounterT = struct
            {
                /// The name of the counter signal low boundary.
                std::string counterNameLow;

                /// The name of the counter signal high boundary.
                std::string counterNameHigh;

                /// The timestamp of the line counting record.
                uint64_t time;

                /// The low boundary of the line counter.
                LineNumberT low;

                /// The high boundary of the line counter.
                LineNumberT high;
            };

            /// The line counter constructor.
            ///
            /// If the counter name does not provide the top module name
            /// it will be automatically set to "Top".
            ///
            /// @param counterName The counter name.
            LineCounter(const std::string &counterName);

            /// The destructor.
            ~LineCounter()
            {}

            /// Updates the line counting information.
            ///
            /// @param time The time the signal has been registered.
            /// @param lineNumber The line number referencing to the signal's occurrence.
            /// @return void
            void Update(uint64_t time, LineNumberT lineNumber);

            /// Returns the consectutive line counter records.
            ///
            /// @param record The placeholder for the record to be returned.
            /// @return true if a valid record has been returned, false otherwise.
            bool Get(LineCounterT &record);

        private:
            /// The counter value.
            using CounterValueT = std::array<LineNumberT, 2>;

            /// The counter map.
            using CounterT = std::map<uint64_t, CounterValueT>;

            /// The counter name.
            std::string m_CounterName;

            /// The counter storage.
            CounterT m_Counter;

            /// The counter iterator.
            CounterT::const_iterator m_CounterIt = m_Counter.begin();
    };
}
