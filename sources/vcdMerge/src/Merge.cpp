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

#include <cmath>
#include <array>
#include <algorithm>

#include "Merge.h"
#include "Utils.h"

void MERGE::Merge::Run()
{
    // If the output time unit is not forced use the minimum value.
    if (m_TimeUnit.empty())
    {
        // The minimum time unit used in sources.
        m_TimeUnit = FindMinUnit();
    }

    /// @todo: The following comment is wrong.
    // Set the time unit of the merged signals.
    m_pMerged = std::make_unique<SIGNAL::SignalDb>(m_TimeUnit);

    /// @todo Here is the explanation for "span". Use it in docs, not here.
    ///       Term "normalized" is not explained anywhere.
    // Find the longest span (distance between the first signal and the sync).
    // The value is normalized.
    m_NormMaxSpan = FindMaxSpan();

    // Merge Sources.
    for (const Source *source : m_Sources)
    {
        // Get the source's time unit.
        const std::string sourceTimeUnit = source->GetTimeUnit();

        // Normalized source sync time.
        /// @todo Name is wrong.
        const uint64_t normSourceSync =
            Normalize(source->GetSync(), sourceTimeUnit);

        // Merge signals here.
        for (auto current_signal : source->Get()->GetSignals())
        {
            SIGNAL::Signal *signal = current_signal->Clone();

            // Set the signal's new timestamp.
            signal->SetTimestamp(CalculateNewTime(signal->GetTimestamp(),
                                                  sourceTimeUnit,
                                                  normSourceSync));

            // Update its name.
            signal->SetName(source->GetPrefix() + signal->GetName());

            // Add to the output signals database.
            m_pMerged->Add(signal);
        }
    }
}

std::string MERGE::Merge::FindMinUnit()
{
    size_t maxIndex = 0;

    for (const Source *const source : m_Sources)
    {
        const size_t index = UTILS::GetTimeUnitIndex(source->GetTimeUnit());
        maxIndex = std::max(index, maxIndex);
    }

    return SIGNAL::Signal::TIME_UNITS[maxIndex];
}

uint64_t MERGE::Merge::FindMaxSpan()
{
    uint64_t maxSpan = 0;

    for (const Source *const source : m_Sources)
    {
        uint64_t span = Normalize(source->GetSpan(),
                                  source->GetTimeUnit());
        maxSpan = std::max(span, maxSpan);
    }

    return maxSpan;
}

uint64_t MERGE::Merge::Normalize(uint64_t time,
                                 const std::string &sourceTimeUnit)
{
    uint64_t newTime = time;
    uint32_t nominator = 0;
    uint32_t denominator = 0;

    const uint32_t targetPower = GetUnitPower(m_TimeUnit);
    const uint32_t sourcePower = GetUnitPower(sourceTimeUnit);

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
    const size_t index = UTILS::GetTimeUnitIndex(timeUnit);

    // 1 [s] = 1000 [ms], 1 [ms] = 1000 [us], etc.
    return (3 * index);
}

uint64_t MERGE::Merge::CalculateNewTime(uint64_t time,
                                        const std::string &sourceUnit,
                                        uint64_t normSync)
{
    /// @todo Detect uint64_t overflow.
    return (Normalize(time, sourceUnit) + m_NormMaxSpan - normSync);
}
