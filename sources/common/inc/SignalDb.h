/// @file SignalDb.h
///
/// Signal database class.
///
/// @par Full Description
/// The class is a database of signals. It shall group signals from a single
/// source.
///
/// @ingroup Signal
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

#include "Signal.h"

namespace SIGNAL
{

    ///  This class is a container for signals.
    class SignalDb
    {
        public:

            /// The SignalDb constructor.
            ///
            /// @param rTimeUnit The time unit in which logged signals are timestamped.
            SignalDb(const std::string &rTimeUnit);

            /// The destructor.
            ~SignalDb();

            /// Adds a signal to the database.
            ///
            /// This method adds a signal to the signals' container.
            /// IMPORTANT!!! The signals do not have to be ordered (in the terms of time).
            /// They will be re-ordered automatically when needed.
            ///
            /// @throws VcdError if the signal has a wrong source handle.
            /// @throws VcdError if there are conflicting signal names.
            /// @param pSignal The signal to be added to the database.
            void Add(const SIGNAL::Signal *pSignal);

            /// Returns a reference to the signals collection.
            const SIGNAL::SignalCollectionT &GetSignals() const
            {
                return m_SignalSet;
            }

            /// Returns a reference to the database signal footprint.
            const SIGNAL::UniqueSignalsCollectionT &GetSignalFootprint() const
            {
                return m_AddedSignals;
            }

            /// Returns a time unit used in the database.
            std::string GetTimeUnit() const
            {
                return m_TimeUnit;
            }

        private:
            /// The VCD time unit in which the signals are timestamped.
            const std::string m_TimeUnit;

            /// The unique signals collection.
            SIGNAL::UniqueSignalsCollectionT m_AddedSignals;

            /// The container for the signals.
            SIGNAL::SignalCollectionT m_SignalSet;
    };

}
