/// @file TimeFrame.cpp
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

#include "TimeFrame.h"

void TRACER::TimeFrame::Add(const SIGNAL::Signal *signal)
{
    auto it = m_Signals.find(signal->GetName());
    if ( (it == m_Signals.end()) ||
         (*it->second != *signal) )
    {
        // The signal wasn't logged yet or it had an old value.
        m_Signals[signal->GetName()] = signal;
        m_FrameSignals[signal->GetName()] = signal;
    }
}

void TRACER::TimeFrame::DumpAndClear()
{
    if (!m_FrameSignals.empty())
    {
        DumpLine('#' + std::to_string(m_Timestamp));

        for (const auto &signal : m_FrameSignals)
        {
            DumpLine(signal.second->Print());
        }

        m_FrameSignals.clear();
    }
}
