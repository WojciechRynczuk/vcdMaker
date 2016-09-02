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
#include <string>
#include <climits>

#include "SourceRegistry.h"
#include "SignalDb.h"

namespace PARSER
{
    /// The line counter class.
    class LineCounter
    {
        public:
            /// A line number type (integral type).
            using LineNumberT = size_t;

            /// The line counter constructor.
            ///
            /// If the counter name does not provide the top module name
            /// it will be automatically set to "Top".
            ///
            /// @param counterName The counter signal name.
            LineCounter(const std::string &counterName);

            /// Updates the line counting information.
            ///
            /// @param timestamp The time the signal has been registered.
            /// @param lineNumber The line number referencing to the signal's occurrence.
            void Update(uint64_t timestamp, LineNumberT lineNumber);

            /// Adds line counter signal to given database.
            ///
            /// @param signalDb Signal database.
            /// @param sourceHandle Signal source handle.
            void RecordToSignalDb(SIGNAL::SignalDb &signalDb,
                                  SIGNAL::SourceRegistry::HandleT sourceHandle);

        private:
            /// The counter value.
            class CounterValue {
                public:
                    /// The low boundary of the line counter.
                    LineNumberT m_LineLow = 0;

                    /// The high boundary of the line counter.
                    LineNumberT m_LineHigh = 0;
            };

            /// The counter signal map.
            using CounterSignalT = std::map<uint64_t, CounterValue>;

            /// Creates counter name based on desired name.
            std::string CreateCounterName(const std::string &desiredName);

            /// Size of the counter signal.
            static constexpr size_t COUNTER_SIGNAL_SIZE =
                sizeof(LineNumberT) * CHAR_BIT;

            /// Default name for "Top" module.
            static const std::string DEFAULT_TOP_MODULE_NAME;

            /// Low line counter signal name postfix.
            static const std::string LOW_COUNTER_NAME;

            /// High line counter signal name postfix.
            static const std::string HIGH_COUNTER_NAME;

            /// The counter name.
            const std::string m_CounterName{};

            /// The name of the counter signal low boundary.
            const std::string m_CounterNameLow{};

            /// The name of the counter signal high boundary.
            const std::string m_CounterNameHigh{};

            /// The counter storage.
            CounterSignalT m_Counter{};
    };
}
