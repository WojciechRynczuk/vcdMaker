/// @file common/test/unitTest/TimeUnit.cpp
///
/// The 'time unit' unit test.
///
/// @ingroup UnitTest
///
/// @par Copyright (c) 2018 vcdMaker team
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

#include "catch.hpp"

#include "TimeUnit.h"

using namespace std::string_literals;

/// Vector of strings.
using StringArray = std::array<std::string, 6>;

/// Unit test for Split().
TEST_CASE("Unit::GetTimeUnits")
{
    REQUIRE(TIME::Unit::GetTimeUnits() == (StringArray{"s"s, "ms"s, "us"s, "ns"s, "ps"s, "fs"s}));
}

/// Unit test for IsTimeUnitValid().
TEST_CASE("Unit::IsTimeUnitValid")
{
    REQUIRE(TIME::Unit::IsTimeUnitValid("s"s));
    REQUIRE(TIME::Unit::IsTimeUnitValid("ms"s));
    REQUIRE(TIME::Unit::IsTimeUnitValid("us"s));
    REQUIRE(TIME::Unit::IsTimeUnitValid("ns"s));
    REQUIRE(TIME::Unit::IsTimeUnitValid("ps"s));
    REQUIRE(TIME::Unit::IsTimeUnitValid("fs"s));

    REQUIRE_FALSE(TIME::Unit::IsTimeUnitValid("ks"s));
}

/// Unit test for GetTimeUnitIndex().
TEST_CASE("Unit::GetTimeUnitIndex")
{
    REQUIRE(TIME::Unit::GetTimeUnitIndex("s"s) == 0);
    REQUIRE(TIME::Unit::GetTimeUnitIndex("ms"s) == 1);
    REQUIRE(TIME::Unit::GetTimeUnitIndex("us"s) == 2);
    REQUIRE(TIME::Unit::GetTimeUnitIndex("ns"s) == 3);
    REQUIRE(TIME::Unit::GetTimeUnitIndex("ps"s) == 4);
    REQUIRE(TIME::Unit::GetTimeUnitIndex("fs"s) == 5);

    REQUIRE_THROWS(TIME::Unit::GetTimeUnitIndex("ks"s));
}

/// Unit test for GetTimeUnit().
TEST_CASE("Unit::GetTimeUnit")
{
    REQUIRE(TIME::Unit::GetTimeUnit(0) == "s"s);
    REQUIRE(TIME::Unit::GetTimeUnit(1) == "ms"s);
    REQUIRE(TIME::Unit::GetTimeUnit(2) == "us"s);
    REQUIRE(TIME::Unit::GetTimeUnit(3) == "ns"s);
    REQUIRE(TIME::Unit::GetTimeUnit(4) == "ps"s);
    REQUIRE(TIME::Unit::GetTimeUnit(5) == "fs"s);

    REQUIRE_THROWS(TIME::Unit::GetTimeUnit(6));
}

/// Unit test for GetTenPower()
TEST_CASE("Unit::GetTenPower")
{
    for (uint32_t i = 0; i < 6; i++)
    {
        REQUIRE(TIME::Unit::GetTenPower(i) == std::pow(1000, i));
    }

    REQUIRE_THROWS(TIME::Unit::GetTenPower(6));
}
