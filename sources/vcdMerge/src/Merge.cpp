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

#include <array>
#include <algorithm>
#include <cmath>

#include "Merge.h"

void MERGE::Merge::Run()
{
    // The minimum time unit used in sources.
    std::string minUnit = FindMinUnit();

    // If the output time unit is not forced use the minimum value.
    if (m_TimeUnit == "")
    {
        m_TimeUnit = minUnit;
    }

    // Set the time unit of the merged signals.
    m_pMerged = std::make_unique<SIGNAL::SignalDb>(m_TimeUnit);

    // Find the longest span (distance between the first signal and the sync).
    // The value is normalized.
    m_NormMaxSpan = FindMaxSpan();

    // Merge Sources.
    for (const Source *source : m_Sources)
    {
        // Get the source's time unit.
        const std::string sourceTimeUnit = source->GetTimeUnit();

        // Normalized source sync time.
        uint64_t normSourceSync = Normalize(source->GetSync(), sourceTimeUnit);

        // Get the source prefix.
        const std::string prefix = source->GetPrefix();

        // Merge signals here.
        for (auto current_signal : source->Get()->GetSignals())
        {
            SIGNAL::Signal *signal = current_signal->Clone();

            // Set the signal's new timestamp.
            signal->SetTimestamp(CalculateNewTime(signal->GetTimestamp(),
                                                  sourceTimeUnit,
                                                  normSourceSync));

            // Update its name.
            signal->SetName(prefix + signal->GetName());

            // Add to the output signals database.
            m_pMerged->Add(signal);
        }
    }
}

std::string MERGE::Merge::FindMinUnit()
{
    const std::array<std::string, 6> tunits = { "s", "ms", "us", "ns", "ps", "fs" };
    size_t maxIndex = 0;

    for (const Source *const source : m_Sources)
    {
        const size_t position =
            (std::find(tunits.cbegin(),
                       tunits.cend(),
                       source->GetTimeUnit()) - tunits.cbegin());

        maxIndex = std::max(position, maxIndex);
    }

    return tunits[maxIndex];
}

uint64_t MERGE::Merge::FindMaxSpan()
{
    uint64_t max_span = 0;

    for (const Source *source : m_Sources)
    {
        uint64_t span = Normalize(source->GetSpan(),
                                  source->GetTimeUnit());
        if (span > max_span)
        {
            max_span = span;
        }
    }
    return max_span;
}

uint64_t MERGE::Merge::Normalize(uint64_t time,
                                 const std::string &sourceTimeUnit)
{
    uint64_t newTime = time;
    uint32_t nominator = 0;
    uint32_t denominator = 0;

    uint32_t targetPower = GetUnitPower(m_TimeUnit);
    uint32_t sourcePower = GetUnitPower(sourceTimeUnit);

    if (targetPower > sourcePower)
    {
        nominator = targetPower - sourcePower;
    }
    else if (targetPower < sourcePower)
    {
        denominator = sourcePower - targetPower;
        /// @todo Range checking must be done.
        newTime = time + static_cast<uint64_t>(((std::pow(10, denominator)) / 2));
    }

    /// @todo Range checking must be done.
    return static_cast<uint64_t>(newTime * ((std::pow(10, nominator)) / (std::pow(10, denominator))));
}

uint32_t MERGE::Merge::GetUnitPower(const std::string &timeUnit)
{
    const std::array<std::string, 6> tunits = { "s", "ms", "us", "ns", "ps", "fs" };

    const size_t position =
        (std::find(tunits.cbegin(),
                   tunits.cend(),
                   timeUnit) - tunits.cbegin());

    // 1 [s] = 1000 [ms], 1 [ms] = 1000 [us], etc.
    return 3 * position;
}

uint64_t MERGE::Merge::CalculateNewTime(uint64_t time,
                                        const std::string &sourceUnit,
                                        uint64_t normSync)
{
    /// @todo Detect uint64_t overflow.
    return (Normalize(time, sourceUnit) + m_NormMaxSpan - normSync);
}
