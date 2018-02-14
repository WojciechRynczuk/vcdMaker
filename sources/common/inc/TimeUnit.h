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
#include <string>

namespace TIME
{
    /// The time unit class.
    class Unit
    {
        public:
            /// Unit is a singleton class.
            static Unit &GetInstance()
            {
                static Unit instance;
                return instance;
            }

            /// Checks if given time unit is supported.
            bool IsTimeUnitValid(const std::string &rUnit) const;

            /// Returns given time unit index in supported units list.
            ///
            /// @throws VcdError if the time unit is out of spec.
            /// @param rUnit The time unit string.
            size_t GetTimeUnitIndex(const std::string &rUnit) const;

            /// Returns the literal of the time unit.
            ///
            /// @param index The time unit index.
            const std::string &GetTimeUnit(size_t index) const;

            /// Returns the list of available time units.
            constexpr const std::vector<std::string> &GetTimeUnits() const
            {
                return TIME_UNITS;
            }

            /// Returns the 10^N value according to the given unit index.
            ///
            /// @param index The index of the unit.
            uint64_t GetTenPower(size_t index) const;

        private:
            /// The default constructor.
            Unit();

            /// Number of units.
            static const uint32_t UNITS_N = 6;

            /// Available time units.
            static const std::vector<std::string> TIME_UNITS;

            /// A table containing integer values of 10^(3*n) where n equals position in the table.
            static const uint64_t TEN_POWER[UNITS_N];
    };
    inline Unit::Unit() = default;
}
