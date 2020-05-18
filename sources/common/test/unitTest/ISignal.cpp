/// @file common/test/unitTest/ISignal.cpp
///
/// Unit test for ISignal class.
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

#include <type_traits>

#include "catch.hpp"

#include "ISignal.h"
#include "stub/DummySignal.h"

/// Create valid VCD line for ISignal.
static inline std::string getISignalPrint(const std::string &value)
{
    return ('b' + value + ' ' + DummySignal::DUMMY_NAME);
}

/// Create ISignal with given value and size (dummy by default).
/// Other parameters are dummies.
static inline SIGNAL::ISignal getISignal(uint64_t value,
                                         size_t size = DummySignal::DUMMY_SIZE)
{
    return {std::make_shared<const SIGNAL::SignalDescriptor>(DummySignal::DUMMY_NAME, size, DummySignal::DUMMY_TYPE, DummySignal::DUMMY_HANDLE).get(),
            DummySignal::DUMMY_TIMESTAMP,
            value};
}

/// Structure describing expected signal value.
class SignalValueTest
{
    public:
        /// Signal size.
        size_t m_Size;

        /// Signal value.
        uint64_t m_Value;

        /// Signal value string.
        std::string m_ValueString;
};

/// ISignal::Print() test vector.
SignalValueTest SIGNAL_VALUE_TESTS[] =
{
    { 1, 0, "0" },
    { 1, 1, "1" },
    { 8, 0, "00000000" },
    { 8, 1, "00000001" },
    { 8, 63, "00111111" },
    { 8, 201, "11001001" },
    { 8, 255, "11111111" },
    { 64, 0, "0000000000000000000000000000000000000000000000000000000000000000" },
    { 64, UINT64_C(2548849195707703904), "0010001101011111010101001101011011010000001100101010001001100000" }
};

/// Unit test for ISignal::Print().
TEST_CASE("ISignal::Print")
{
    for (const auto &testCase : SIGNAL_VALUE_TESTS)
    {
        const SIGNAL::ISignal signal =
            getISignal(testCase.m_Value, testCase.m_Size);

        const std::string expectedPrint = getISignalPrint(testCase.m_ValueString);

        REQUIRE(signal.Print() == expectedPrint);
    }
}

/// Structure describing expected signal footprint.
class SignalSizeTest
{
    public:
        /// Signal size.
        size_t m_Size;

        /// Signal footprint string.
        std::string m_Footprint;
};

/// ISignal::Footprint() test vector.
SignalSizeTest SIGNAL_SIZE_TESTS[] =
{
    { 1,  "x" },
    { 8,  "xxxxxxxx" },
    { 32, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" },
    { 64, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" }
};

/// Unit test for ISignal::Footprint().
TEST_CASE("ISignal::Footprint")
{
    for (const auto &testCase : SIGNAL_SIZE_TESTS)
    {
        const SIGNAL::ISignal signal =
            getISignal(0, testCase.m_Size);

        const std::string expectedFootprint = getISignalPrint(testCase.m_Footprint);

        REQUIRE(signal.Footprint() == expectedFootprint);
    }
}

/// Unit test for ISignal::EqualTo().
TEST_CASE("ISignal::EqualTo")
{
    SIGNAL::ISignal signal1 = getISignal(1);
    SIGNAL::Signal &rSignal1 = signal1;

    SIGNAL::ISignal signal2 = getISignal(2);
    SIGNAL::Signal &rSignal2 = signal2;

    SIGNAL::ISignal signal3 = getISignal(2);
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

