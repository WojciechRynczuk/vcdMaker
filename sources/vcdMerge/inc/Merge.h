/// @file Merge.h
///
/// The merging unit.
///
/// @par Full Description
/// The merging unit.
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

#pragma once

/// @defgroup Merge Merge
///
/// @brief Merge related classes.
///
/// @par Full Description
/// The group gathers classes needed by the VCD merging application.

#include "SignalSource.h"

namespace MERGE
{
    /// The merging unit class. Allows for merging different
    /// signal sources.

    /// The merging unit class.
    class Merge
    {
        public:
            /// The merge constructor.
            ///
            /// @param verboseMode 'true' enables the verbose mode.
            /// @param timeUnit The time unit of the output file.
            Merge(bool verboseMode, const std::string &timeUnit) :
                m_Sources(),
                m_TimeUnit(timeUnit),
                m_MaxLeadingTime(),
                m_pMerged(),
                m_VerboseMode(verboseMode)
            {
            }

            /// Adds a signal source to be merged.
            void AddSource(const SignalSource *source)
            {
                m_Sources.push_back(source);
            }

            /// Triggers the merge.
            void Run();

            /// Returns the merged signals database.
            const SIGNAL::SignalDb &GetSignals() const
            {
                return *(m_pMerged.get());
            }

        private:

            /// Returns the minimal unit.
            ///
            /// @param The result time unit.
            std::string FindMinUnit();

            /// Returns the max leading time - the time between the first
            /// event and the synchronization point.
            uint64_t FindMaxLeadingTime();

            /// Returns the time value represented in the target time unit.
            ///
            /// @param time A time value to be transformed.
            /// @param targetTimeUnit The target time unit.
            /// @param sourceTimeUnit The source time unit.
            uint64_t TransformUnit(uint64_t time,
                                   const std::string &targetTimeUnit,
                                   const std::string &sourceTimeUnit);

            /// Returns the new signal's time.
            ///
            /// @param time The original signal's timestamp.
            /// @param sync The source's sync point.
            uint64_t CalculateNewTime(uint64_t time,
                                      uint64_t syncPoint);

            /// A type defining a container for signal sources.
            using SignalSourcesT = std::vector<const SignalSource *>;

            /// Number of units.
            static const uint32_t UNITS_N = 6;

            /// A table containing integer values of 10^(3*n) where n equals position in the table.
            static const uint64_t TEN_POWER[UNITS_N];

            /// The set of sources.
            SignalSourcesT m_Sources;

            /// Merging time unit.
            std::string m_TimeUnit;

            /// The minimum merging unit.
            std::string m_MinTimeUnit;

            /// The greatest leading time among sources.
            /// Expressed in the time output unit.
            uint64_t m_MaxLeadingTime;

            /// The output database.
            std::unique_ptr<SIGNAL::SignalDb> m_pMerged;

            /// Verbose mode.
            bool m_VerboseMode;
    };
}
