/// @file common/test/unitTest/FSignal.cpp
///
/// Unit test for FSignal class.
///
/// @ingroup UnitTest
///
/// @par Copyright (c) 2020 vcdMaker team
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

#include "FSignal.h"
#include "stub/DummySignal.h"

/// Create valid VCD line for FSignal.
static inline std::string getFSignalPrint(const std::string &value)
{
    return ('r' + value + ' ' + DummySignal::DUMMY_NAME);
}

/// Create FSignal with given value.
/// Other parameters are dummies.
static inline SIGNAL::FSignal getFSignal(const std::string &value)
{
    return { std::make_shared<const SIGNAL::SignalDescriptor>(DummySignal::DUMMY_NAME, DummySignal::DUMMY_SIZE, DummySignal::DUMMY_TYPE, DummySignal::DUMMY_HANDLE).get(),
            DummySignal::DUMMY_TIMESTAMP,
            value };
}

/// Unit test for FSignal::Print().
TEST_CASE("FSignal::Print")
{
    const std::string test_value = "123456789.10111213141516";

    const SIGNAL::FSignal signal =
        getFSignal(test_value);

    const std::string expectedPrint = getFSignalPrint(test_value);

    REQUIRE(signal.Print() == expectedPrint);
}

/// Unit test for FSignal::Footprint().
TEST_CASE("FSignal::Footprint")
{
    const SIGNAL::FSignal signal =
        getFSignal("0.0");

    const std::string expectedFootprint = getFSignalPrint("0.0");

    REQUIRE(signal.Footprint() == expectedFootprint);
}

/// Unit test for FSignal::EqualTo().
TEST_CASE("FSignal::EqualTo")
{
    SIGNAL::FSignal signal1 = getFSignal("1.1");
    SIGNAL::Signal &rSignal1 = signal1;

    SIGNAL::FSignal signal2 = getFSignal("2.2");
    SIGNAL::Signal &rSignal2 = signal2;

    SIGNAL::FSignal signal3 = getFSignal("2.2");
    SIGNAL::Signal &rSignal3 = signal3;

    DummySignal dummySignal(DummySignal::DUMMY_NAME,
                            DummySignal::DUMMY_TIMESTAMP);
    SIGNAL::Signal &rDummySignal = dummySignal;

    SECTION("operator==")
    {
        REQUIRE(rSignal1 == rSignal1);
        REQUIRE(rSignal2 == rSignal3);
        REQUIRE_FALSE(rSignal1 == rSignal2);

        REQUIRE_FALSE(rSignal1 == rDummySignal);
        REQUIRE_FALSE(rDummySignal == rSignal1);
    }
    SECTION("operator!=")
    {
        REQUIRE_FALSE(rSignal1 != rSignal1);
        REQUIRE_FALSE(rSignal2 != rSignal3);
        REQUIRE(rSignal1 != rSignal2);

        REQUIRE(rSignal1 != rDummySignal);
        REQUIRE(rDummySignal != rSignal1);
    }
}

