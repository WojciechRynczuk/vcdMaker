/// @file vcdMerge/inc/Merge.h
///
/// The merging unit.
///
/// @par Full Description
/// The merging unit.
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

#pragma once

/// @defgroup Merge Merge
///
/// @brief Merge related classes.
///
/// @par Full Description
/// The group gathers classes needed by the VCD merging application.

#include "SignalSource.h"

/// The merging engine.
namespace MERGE
{
    /// The merging unit class.
    /// Allows for merging different signal sources.
    class Merge
    {
        public:
            /// The merge constructor.
            ///
            /// @throws VcdError if sources cannot be merged.
            /// @param verboseMode 'true' enables the verbose mode.
            /// @param rTimeUnit The time unit of the output file.
            Merge(bool verboseMode, const std::string &rTimeUnit) :
                m_Sources(),
                m_TimeUnit(rTimeUnit),
                m_MaxLeadingTime(),
                m_pMerged(),
                m_VerboseMode(verboseMode)
            {
            }

            /// Adds a signal source to be merged.
            void AddSource(const SignalSource *pSource)
            {
                m_Sources.push_back(pSource);
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
            std::string FindMinUnit() const;

            /// Returns the max leading time - the time between the first
            /// event and the synchronization point.
            TIME::Timestamp FindMaxLeadingTime() const;

            /// Returns the time value represented in the target time unit.
            ///
            /// @throws std::runtime_error() if the new time value is out of bounds.
            /// @param rTime A time value to be transformed.
            /// @param rTargetTimeUnit The target time unit.
            /// @param rSourceTimeUnit The source time unit.
            TIME::Timestamp TransformTimestamp(const TIME::Timestamp &rTime,
                                               const std::string &rTargetTimeUnit,
                                               const std::string &rSourceTimeUnit) const;

            /// Returns the new signal's time.
            ///
            /// @throws std::runtime_error() is the new time value is out of bounds.
            /// @param rTime The original signal's timestamp.
            /// @param rSync The source's sync point.
            TIME::Timestamp CalculateNewTime(const TIME::Timestamp &rTime,
                                             const TIME::Timestamp &rSyncPoint) const;

            /// A type defining a container for signal sources.
            using SignalSourcesT = std::vector<const SignalSource *>;

            /// The set of sources.
            SignalSourcesT m_Sources;

            /// Merging time unit.
            std::string m_TimeUnit;

            /// The minimum merging unit.
            std::string m_MinTimeUnit;

            /// The greatest leading time among sources.
            /// Expressed in the time output unit.
            TIME::Timestamp m_MaxLeadingTime;

            /// The output database.
            std::unique_ptr<SIGNAL::SignalDb> m_pMerged;

            /// Verbose mode.
            bool m_VerboseMode;
    };
}
