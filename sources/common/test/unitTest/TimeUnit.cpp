/// @file common/test/unitTest/TimeUnit.cpp
///
/// The 'time unit' unit test.
///
/// @ingroup UnitTest
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

#include <cmath>

#include "catch.hpp"

#include "TimeUnit.h"

using namespace std::string_literals;

/// Vector of strings.
using StringVector = std::vector<std::string>;

/// Unit test for Split().
TEST_CASE("Unit::GetTimeUnits")
{
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnits() == (StringVector{"s"s, "ms"s, "us"s, "ns"s, "ps"s, "fs"s}));
}

/// Unit test for IsTimeUnitValid().
TEST_CASE("Unit::IsTimeUnitValid")
{
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("s"s));
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("ms"s));
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("us"s));
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("ns"s));
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("ps"s));
    REQUIRE(TIME::Unit::GetInstance().IsTimeUnitValid("fs"s));

    REQUIRE_FALSE(TIME::Unit::GetInstance().IsTimeUnitValid("ks"s));
}

/// Unit test for GetTimeUnitIndex().
TEST_CASE("Unit::GetTimeUnitIndex")
{
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("s"s) == 0);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("ms"s) == 1);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("us"s) == 2);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("ns"s) == 3);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("ps"s) == 4);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnitIndex("fs"s) == 5);

    REQUIRE_THROWS(TIME::Unit::GetInstance().GetTimeUnitIndex("ks"s));
}

/// Unit test for GetTimeUnit().
TEST_CASE("Unit::GetTimeUnit")
{
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(0) == "s"s);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(1) == "ms"s);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(2) == "us"s);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(3) == "ns"s);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(4) == "ps"s);
    REQUIRE(TIME::Unit::GetInstance().GetTimeUnit(5) == "fs"s);

    REQUIRE_THROWS(TIME::Unit::GetInstance().GetTimeUnit(6));
}

/// Unit test for GetTenPower()
TEST_CASE("Unit::GetTenPower")
{
    for (uint32_t i = 0; i < 6; i++)
    {
        REQUIRE(TIME::Unit::GetInstance().GetTenPower(i) == std::pow(1000, i));
    }

    REQUIRE_THROWS(TIME::Unit::GetInstance().GetTenPower(6));
}
