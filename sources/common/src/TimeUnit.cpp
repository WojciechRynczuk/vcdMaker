/// @file common/src/TimeUnit.cpp
///
/// The utilities.
///
/// The time unit library.
///
/// @par Full Description
/// The functions for handling time units.
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
#include <stdexcept>
#include <vector>
#include <string>
#include <ratio>

#include "TimeUnit.h"
#include "VcdException.h"

const std::vector<std::string> TIME::Unit::TIME_UNITS =
{ "s", "ms", "us", "ns", "ps", "fs" };

const std::vector<uint64_t> TIME::Unit::TEN_POWER =
{
    1ull,
    static_cast<uint64_t>(std::kilo::num),
    static_cast<uint64_t>(std::mega::num),
    static_cast<uint64_t>(std::giga::num),
    static_cast<uint64_t>(std::tera::num),
    static_cast<uint64_t>(std::peta::num)
};

bool TIME::Unit::IsTimeUnitValid(const std::string &rUnit) const
{
    return (std::find(TIME_UNITS.cbegin(),
                      TIME_UNITS.cend(),
                      rUnit) != TIME_UNITS.cend());
}

size_t TIME::Unit::GetTimeUnitIndex(const std::string &rUnit) const
{
    const size_t index = (std::find(TIME_UNITS.cbegin(),
                                    TIME_UNITS.cend(),
                                    rUnit) - TIME_UNITS.cbegin());

    if (index == TIME_UNITS.size())
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::INVALID_TIME_UNIT,
                                      "Invalid time unit: " + rUnit);
    }
    else
    {
        return index;
    }
}

const std::string &TIME::Unit::GetTimeUnit(size_t index) const
{
    if (index >= TIME_UNITS.size())
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::TIME_UNIT_INDEX_OUT_OF_BOUNDS,
                                      "Time unit index out of bounds.");
    }
    return TIME_UNITS[index];
}

uint64_t TIME::Unit::GetTenPower(size_t index) const
{
    if (index >= TEN_POWER.size())
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::TIME_UNIT_INDEX_OUT_OF_BOUNDS,
                                      "Time unit index out of bounds.");
    }
    return TEN_POWER[index];
}
