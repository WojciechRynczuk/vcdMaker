/// @file Utils.cpp
///
/// The utilities unit test.
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

#include "catch.hpp"

#include "Utils.h"

using namespace std::string_literals;

using StringVector = std::vector<std::string>;

/// Unit test for Split().
TEST_CASE("UTILS::Split")
{
    REQUIRE((UTILS::Split(""s, '\0')) == (StringVector{}));
    REQUIRE((UTILS::Split("abcd"s, '\0')) == (StringVector{"abcd"s}));
    REQUIRE((UTILS::Split("a b c d"s, ' ')) == (StringVector{"a"s, "b"s, "c"s, "d"s}));
    REQUIRE((UTILS::Split(" a b c d"s, ' ')) == (StringVector{"a"s, "b"s, "c"s, "d"s}));
    REQUIRE((UTILS::Split("a b c d "s, ' ')) == (StringVector{"a"s, "b"s, "c"s, "d"s}));
    REQUIRE((UTILS::Split(" a b c d "s, ' ')) == (StringVector{"a"s, "b"s, "c"s, "d"s}));
    REQUIRE((UTILS::Split("a b   c  d"s, ' ')) == (StringVector{"a"s, "b"s, "c"s, "d"s}));
}

/// Unit test for IsTimeUnitValid().
TEST_CASE("UTILS::IsTimeUnitValid")
{
    REQUIRE(UTILS::IsTimeUnitValid("a"s));
    REQUIRE(UTILS::IsTimeUnitValid("b"s));
    REQUIRE(UTILS::IsTimeUnitValid("c"s));
    REQUIRE(UTILS::IsTimeUnitValid("d"s));

    REQUIRE_FALSE(UTILS::IsTimeUnitValid("e"s));
}

/// Unit test for GetTimeUnitIndex().
TEST_CASE("UTILS::GetTimeUnitIndex")
{
    REQUIRE(UTILS::GetTimeUnitIndex("a"s) == 0);
    REQUIRE(UTILS::GetTimeUnitIndex("b"s) == 1);
    REQUIRE(UTILS::GetTimeUnitIndex("c"s) == 2);
    REQUIRE(UTILS::GetTimeUnitIndex("d"s) == 3);

    REQUIRE_THROWS(UTILS::GetTimeUnitIndex("e"s));
}
