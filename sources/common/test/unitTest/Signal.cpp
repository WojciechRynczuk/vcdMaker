/// @file Signal.cpp
///
/// Unit test for Signal class.
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

#include "Signal.h"
#include "stub/DummySignal.h"

TEST_CASE("Signal")
{
    DummySignal dummySignal1("dummy1", 1);
    DummySignal dummySignal2("dummy2", 2);
    DummySignal dummySignal3("dummy2", 2);

    SIGNAL::Signal &rSignal1 = dummySignal1;
    SIGNAL::Signal &rSignal2 = dummySignal2;
    SIGNAL::Signal &rSignal3 = dummySignal3;

    SECTION("operator==")
    {
        REQUIRE(rSignal1 == rSignal1);
        REQUIRE(rSignal2 == rSignal3);
        REQUIRE_FALSE(rSignal1 == rSignal2);
    }
    SECTION("operator!=")
    {
        REQUIRE_FALSE(rSignal1 != rSignal1);
        REQUIRE_FALSE(rSignal2 != rSignal3);
        REQUIRE(rSignal1 != rSignal2);
    }
    SECTION("PtrTimestampLtComparator")
    {
        SIGNAL::PtrTimestampLtComparator ltComparator;

        REQUIRE_FALSE((ltComparator(&rSignal1, &rSignal1)));
        REQUIRE_FALSE((ltComparator(&rSignal2, &rSignal1)));
        REQUIRE_FALSE((ltComparator(&rSignal2, &rSignal3)));
        REQUIRE((ltComparator(&rSignal1, &rSignal2)));
    }
}

