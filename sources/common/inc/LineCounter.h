/// @file common/inc/LineCounter.h
///
/// The line counting class.
///
/// @par Full Description
/// The object of this class allows for keeping a record of the line
/// counting information. It is supposed to be used by the text parser.
///
/// @ingroup Instrument
///
/// @par Copyright (c) 2017 vcdMaker team
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

#include <climits>

#include "Instrument.h"

namespace INSTRUMENT
{
    /// The line counter class.
    class LineCounter : public Instrument
    {
        public:
            /// The line counter constructor.
            ///
            /// If the counter name does not provide the top module name
            /// it will be automatically set to "Top".
            ///
            /// @param rFilename The name of the file associated with the counter.
            /// @param rCounterName The counter signal name.
            /// @param rSourceRegistry Signal sources registry.
            /// @param rSignalDb The signal database to be used.
            LineCounter(const std::string &rFilename,
                        const std::string &rCounterName,
                        SIGNAL::SourceRegistry &rSourceRegistry,
                        SIGNAL::SignalDb &rSignalDb);

            /// @copydoc Instrument::Notify()
            virtual void Notify(LineNumberT lineNumber, const SIGNAL::Signal &rSignal);

            /// @copydoc Instrument::Terminate()
            virtual void Terminate() const;

        private:
            /// The counter value.
            class CounterValue
            {
                public:
                    /// The low boundary of the line counter.
                    LineNumberT m_LineLow = 0;

                    /// The high boundary of the line counter.
                    LineNumberT m_LineHigh = 0;
            };

            /// The counter signal map.
            using CounterSignalT = std::map<uint64_t, CounterValue>;

            /// Creates counter name based on desired name.
            std::string CreateCounterName(const std::string &rDesiredName);

            /// Size of the counter signal.
            static constexpr size_t COUNTER_SIGNAL_SIZE =
                sizeof(LineNumberT) * CHAR_BIT;

            /// Line counter suffix for name in source registry.
            static const std::string LINE_COUNTER_SUFFIX;

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
