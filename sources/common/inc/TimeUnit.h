/// @file common/inc/TimeUnit.h
///
/// The time unit library.
///
/// @par Full Description
/// The functions for handling time units.
///
/// @ingroup Time
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

#include <vector>
#include <array>
#include <string>

namespace TIME
{
    /// The time unit class.
    class Unit
    {
        private:
            /// Number of units
            static const uint32_t NO_OF_UNITS = 6U;

        public:
            /// Checks if given time unit is supported.
            static bool IsTimeUnitValid(const std::string &rUnit);

            /// Returns given time unit index in supported units list.
            ///
            /// @throws VcdError if the time unit is out of spec.
            /// @param rUnit The time unit string.
            static size_t GetTimeUnitIndex(const std::string &rUnit);

            /// Returns the literal of the time unit.
            ///
            /// @param index The time unit index.
            static const std::string &GetTimeUnit(size_t index);

            /// Returns the list of available time units.
            static const std::array<std::string, NO_OF_UNITS> &GetTimeUnits()
            {
                return TIME_UNITS;
            }

            /// Returns the 10^N value according to the given unit index.
            ///
            /// @param index The index of the unit.
            static uint64_t GetTenPower(size_t index);

        private:
            /// The default constructor.
            Unit() = default;

            /// Available time units.
            static const std::array<std::string, NO_OF_UNITS> TIME_UNITS;

            /// A table containing integer values of 10^(3*n) where n equals position in the table.
            static const std::array<uint64_t, NO_OF_UNITS> TEN_POWER;
    };
}
