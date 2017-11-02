/// @file vcdMerge/src/Merge.cpp
///
/// The merging unit.
///
/// @par Full Description
/// The class defines the merging entity.
///
/// @ingroup Merge
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

#include <algorithm>
#include <ratio>

#include "Merge.h"
#include "Utils.h"
#include "Logger.h"

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

    // Find the longest leading time among all sources.
    try
    {
        m_MaxLeadingTime = FindMaxLeadingTime();
    }
    catch (std::out_of_range &)
    {
        // Sources cannot be merged.
        throw EXCEPTION::VcdException(EXCEPTION::Error::LEADING_TIME_OUT_OF_BOUNDS,
                                      "Leading time out of bounds.");
    }

    // Merge Sources.
    for (const SignalSource *pSource : m_Sources)
    {
        // Get the source's time unit.
        const std::string source_time_unit = pSource->GetTimeUnit();

        // Source sync time in the target unit.
        TIME::Timestamp transformed_source_sync = 0;

        try
        {
            transformed_source_sync =
                TransformTimestamp(pSource->GetSyncPoint(), m_MinTimeUnit, source_time_unit);
        }
        catch (std::out_of_range &)
        {
            LOGGER::Logger::GetInstance().LogWarning(EXCEPTION::Warning::SYNCHRONIZATION_TIME_OUT_OF_BOUNDS,
                              "Synchronization time out of bounds. Cannot merge "
                              + pSource->GetDescription()
                              + ".");
            continue;
        }

        // Merge signals here.
        for (auto current_signal : pSource->Get()->GetSignals())
        {
            SIGNAL::Signal *pSignal = current_signal->Clone();

            try
            {
                // Set the signal's new timestamp.
                pSignal->SetTimestamp(CalculateNewTime(TransformTimestamp(pSignal->GetTimestamp(),
                                                      m_MinTimeUnit,
                                                      source_time_unit),
                                      transformed_source_sync));
            }
            catch (std::out_of_range &)
            {
                LOGGER::Logger::GetInstance().LogWarning(EXCEPTION::Warning::TIMESTAMP_OUT_OF_BOUNDS,
                                  "Timestamp out of bounds. Cannot merge " +
                                  pSignal->GetName() +
                                  " at " +
                                  std::to_string(pSignal->GetTimestamp().GetValue()) + " " +
                                  pSource->GetTimeUnit());

                delete pSignal;
                continue;
            }

            // Update its name.
            pSignal->SetName(pSource->GetPrefix() + pSignal->GetName());

            // Add to the output signals database.
            m_pMerged->Add(pSignal);
        }
    }
}

std::string MERGE::Merge::FindMinUnit() const
{
    size_t max_index = 0;

    for (const SignalSource *const source : m_Sources)
    {
        const size_t index = UTILS::GetTimeUnitIndex(source->GetTimeUnit());
        max_index = std::max(index, max_index);
    }

    return SIGNAL::Signal::TIME_UNITS[max_index];
}

TIME::Timestamp MERGE::Merge::FindMaxLeadingTime() const
{
    TIME::Timestamp max_leading_time = 0;

    for (const SignalSource *const source : m_Sources)
    {
        const TIME::Timestamp log_leading_time = TransformTimestamp(source->GetLeadingTime(),
                                                                      m_MinTimeUnit,
                                                                      source->GetTimeUnit());
        const TIME::Timestamp user_leading_time = TransformTimestamp(source->GetSyncPoint(),
                                                                       m_MinTimeUnit,
                                                                       source->GetTimeUnit());
        const TIME::Timestamp leading_time = std::min(log_leading_time, user_leading_time);
        max_leading_time = std::max(leading_time, max_leading_time);
    }

    return max_leading_time;
}

TIME::Timestamp MERGE::Merge::TransformTimestamp(const TIME::Timestamp &rTime,
                                                 const std::string &rTargetTimeUnit,
                                                 const std::string &rSourceTimeUnit) const
{
    TIME::Timestamp new_time = rTime;
    uint32_t nominator = 0;
    uint32_t denominator = 0;

    const uint32_t target_power = UTILS::GetTimeUnitIndex(rTargetTimeUnit);
    const uint32_t source_power = UTILS::GetTimeUnitIndex(rSourceTimeUnit);

    if (target_power > source_power)
    {
        nominator = (target_power - source_power);
    }
    else if (target_power < source_power)
    {
        denominator = (source_power - target_power);
        const TIME::Timestamp rounding(TEN_POWER[denominator] / 2);

        new_time = rTime + rounding;
    }

    const double units_ratio =
        static_cast<double>(TEN_POWER[nominator]) / TEN_POWER[denominator];

    return (new_time * units_ratio);
}

TIME::Timestamp MERGE::Merge::CalculateNewTime(const TIME::Timestamp &rTime,
                                               const TIME::Timestamp &rSyncPoint) const
{
    const TIME::Timestamp max = std::max(rTime, m_MaxLeadingTime);
    const TIME::Timestamp min = std::min(rTime, m_MaxLeadingTime);
    TIME::Timestamp temp_time = 0;

    if (max < rSyncPoint)
    {
        temp_time = max + min;
        temp_time -= rSyncPoint;
    }
    else
    {
        temp_time = max - rSyncPoint;
        temp_time += min;
    }
    return (TransformTimestamp(temp_time, m_TimeUnit, m_MinTimeUnit));
}
