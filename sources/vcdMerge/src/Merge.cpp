/// @file Merge.cpp
///
/// The merging unit.
///
/// @par Full Description
/// The class defines the merging entity.
///
/// @ingroup Merge
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

#include <functional>

#include "Merge.h"

void MERGE::Merge::Run()
{
    /// @todo Fixed unit still being used.
    m_pMerged = std::make_unique<SIGNAL::SignalDb>("us");

    // Find the longest span.
    uint64_t max_span = FindMaxSpan();

    for (const Source *source : m_Sources)
    {
        std::function<uint64_t(uint64_t)> pFcn;
        uint64_t sourceSync = source->GetSync();

        if (max_span != sourceSync)
        {
            /// @todo Detect uint64_t overflow.
            pFcn = [&](uint64_t tstamp)
            {
                return (tstamp + max_span - sourceSync);
            };
        }
        else
        {
            // Assign 1 just to get rid of the warning.
            pFcn = [&](uint64_t tstamp)
            {
                tstamp = 1;
                return max_span;
            };
        }

        // Merge signals here.
        for (auto current_signal : source->Get()->GetSignals())
        {
            SIGNAL::Signal *signal = current_signal->Clone();
            signal->SetTimestamp(pFcn(signal->GetTimestamp()));
            m_pMerged->Add(signal);
        }
    }
}

const uint64_t MERGE::Merge::FindMaxSpan()
{
    uint64_t max_span = 0;
    for (const Source *source : m_Sources)
    {
        uint64_t span = source->GetSpan("us");
        if (span > max_span)
        {
            max_span = span;
        }
    }
    return max_span;
}
