/// @file EventSignal.cpp
///
/// Unit test for EventSignal class.
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

#include "EventSignal.h"
#include "stub/DummySignal.h"

/// Create valid VCD line for EventSignal.
static inline std::string getEventSignalPrint()
{
    return ('1' + std::string(DummySignal::DUMMY_NAME));
}

/// Create EventSignal.
static inline SIGNAL::EventSignal getEventSignal()
{
    return {DummySignal::DUMMY_NAME,
            DummySignal::DUMMY_TIMESTAMP,
            DummySignal::DUMMY_HANDLE};
}

TEST_CASE("EventSignal::Print")
{
    const SIGNAL::EventSignal signal = getEventSignal();

    const std::string expectedPrint = getEventSignalPrint();

    REQUIRE(signal.Print() == expectedPrint);
}

TEST_CASE("EventSignal::Footprint")
{
    const SIGNAL::EventSignal signal = getEventSignal();

    REQUIRE(signal.Footprint().empty());
}

TEST_CASE("EventSignal::EqualTo")
{
    SIGNAL::EventSignal signal1 = getEventSignal();
    SIGNAL::Signal &rSignal1 = signal1;

    SIGNAL::EventSignal signal2 = getEventSignal();
    SIGNAL::Signal &rSignal2 = signal2;

    DummySignal dummySignal(DummySignal::DUMMY_NAME,
                            DummySignal::DUMMY_TIMESTAMP);
    SIGNAL::Signal &rDummySignal = dummySignal;

    SECTION("operator==")
    {
        REQUIRE_FALSE(rSignal1 == rSignal1);
        REQUIRE_FALSE(rSignal1 == rSignal2);

        REQUIRE_FALSE(rSignal1 == rDummySignal);
        REQUIRE_FALSE(rDummySignal == rSignal1);
    }
    SECTION("operator!=")
    {
        REQUIRE(rSignal1 != rSignal1);
        REQUIRE(rSignal1 != rSignal2);

        REQUIRE(rSignal1 != rDummySignal);
        REQUIRE(rDummySignal != rSignal1);
    }
}

