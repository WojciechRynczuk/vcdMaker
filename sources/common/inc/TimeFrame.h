/// @file TimeFrame.h
///
/// The time frame class.
///
/// @par Full Description
/// The object of this class is supposed to be used by the tracing object
/// to keep a track of signals within the same time frame.
///
/// @ingroup Tracer
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

#include <fstream>

#include "Signal.h"

namespace TRACER
{
    /// The time frame class.
    class TimeFrame
    {
        public:
            /// The time frame constructor.
            ///
            /// @param timestamp The initial timestamp.
            /// @param file The output stream.
            TimeFrame(const uint64_t timestamp, std::ofstream &file) :
                m_Timestamp(timestamp),
                m_rFile(file),
                m_FrameSignals()
            {
            }

            /// Sets the beginning of the frame.
            ///
            /// @param frameStart New timestamp characterizing a frame.
            void SetTime(uint64_t frameStart)
            {
                m_Timestamp = frameStart;
            }

            /// Adds the signal information to the time frame.
            ///
            /// @param signal The signal.
            void Add(const SIGNAL::Signal *signal);

            /// Dumps the time frame information.
            ///
            /// Time frame is dumped to the file and then the frame is cleared.
            void DumpAndClear();

        private:

            /// Write on line to output file.
            void DumpLine(const std::string &line)
            {
                m_rFile << line << '\n';
            }

            /// The timestamp of the time frame.
            uint64_t m_Timestamp;

            /// The output stream.
            std::ofstream &m_rFile;

            /// Time frame signals.
            SIGNAL::UniqueSignalsCollectionT m_FrameSignals;

            /// All signals.
            SIGNAL::UniqueSignalsCollectionT m_Signals;
    };
}
