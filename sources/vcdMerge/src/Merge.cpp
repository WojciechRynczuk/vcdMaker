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

#include <algorithm>
#include <ratio>

#include "Merge.h"
#include "Utils.h"

const uint64_t MERGE::Merge::TEN_POWER[] =
{
    1ull,
    static_cast<uint64_t>(std::kilo::num),
    static_cast<uint64_t>(std::mega::num),
    static_cast<uint64_t>(std::giga::num),
    static_cast<uint64_t>(std::tera::num),
    static_cast<uint64_t>(std::peta::num)
};

void MERGE::Merge::Run()
{
    // Find the minimum merging unit.
    m_MinTimeUnit = FindMinUnit();

    // If the output time unit is not forced use the minimum value.
    if (m_TimeUnit.empty())
    {
        // The minimum time unit used in sources.
        m_TimeUnit = m_MinTimeUnit;
    }

    // Create the output signal database and set its base time unit.
    m_pMerged = std::make_unique<SIGNAL::SignalDb>(m_TimeUnit);

    // Find the longest leading time for among all sources.
    m_MaxLeadingTime = FindMaxLeadingTime();

    // Merge Sources.
    for (const SignalSource *source : m_Sources)
    {
        // Get the source's time unit.
        const std::string sourceTimeUnit = source->GetTimeUnit();

        // Source sync time in the target unit.
        const uint64_t transformedSourceSync =
            TransformUnit(source->GetSyncPoint(), m_MinTimeUnit, sourceTimeUnit);

        // Merge signals here.
        for (auto current_signal : source->Get()->GetSignals())
        {
            SIGNAL::Signal *signal = current_signal->Clone();

            // Set the signal's new timestamp.
            signal->SetTimestamp(CalculateNewTime(TransformUnit(signal->GetTimestamp(), 
                                                                m_MinTimeUnit, 
                                                                sourceTimeUnit),
                                                  transformedSourceSync));

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

    for (const SignalSource *const source : m_Sources)
    {
        const size_t index = UTILS::GetTimeUnitIndex(source->GetTimeUnit());
        maxIndex = std::max(index, maxIndex);
    }

    return SIGNAL::Signal::TIME_UNITS[maxIndex];
}

uint64_t MERGE::Merge::FindMaxLeadingTime()
{
    uint64_t maxLeadingTime = 0;

    for (const SignalSource *const source : m_Sources)
    {
        uint64_t leadingTime = TransformUnit(source->GetLeadingTime(),
                                             m_MinTimeUnit,
                                             source->GetTimeUnit());
        maxLeadingTime = std::max(leadingTime, maxLeadingTime);
    }

    return maxLeadingTime;
}

uint64_t MERGE::Merge::TransformUnit(uint64_t time,
                                     const std::string &targetTimeUnit,
                                     const std::string &sourceTimeUnit)
{
    uint64_t newTime = time;
    uint32_t nominator = 0;
    uint32_t denominator = 0;

    const uint32_t targetPower = UTILS::GetTimeUnitIndex(targetTimeUnit);
    const uint32_t sourcePower = UTILS::GetTimeUnitIndex(sourceTimeUnit);

    if (targetPower > sourcePower)
    {
        nominator = (targetPower - sourcePower);
    }
    else if (targetPower < sourcePower)
    {
        denominator = (sourcePower - targetPower);
        /// @todo Range checking must be done.
        newTime = time + (TEN_POWER[denominator]) / 2);
    }

    const double unitsRatio =
        static_cast<double>(TEN_POWER[nominator]) / TEN_POWER[denominator];

    /// @todo Range checking must be done.
    return static_cast<uint64_t>(newTime * unitsRatio);
}

uint64_t MERGE::Merge::CalculateNewTime(uint64_t time,
                                        uint64_t syncPoint)
{
    /// @todo Detect uint64_t overflow.
    return (TransformUnit(time + m_MaxLeadingTime - syncPoint, m_TimeUnit, m_MinTimeUnit));
}
