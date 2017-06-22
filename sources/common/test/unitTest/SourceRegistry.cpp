/// @file SourceRegistry.cpp
///
/// Unit test for SourceRegistry class.
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

#include "SourceRegistry.h"

constexpr SIGNAL::SourceRegistry::HandleT SIGNAL::SourceRegistry::BAD_HANDLE;

/// Unit test for SourceRegistry class.
TEST_CASE("SourceRegistry")
{
    const std::string name1 = "abcd";
    const std::string name2 = "efgh";

    SIGNAL::SourceRegistry registry;

    const SIGNAL::SourceRegistry::HandleT handle1 =
        registry.Register(name1);

    SECTION("SourceRegistry::Register")
    {
        REQUIRE(handle1 != SIGNAL::SourceRegistry::BAD_HANDLE);
        REQUIRE(handle1 != registry.Register(name2));
        REQUIRE(handle1 == registry.Register(name1));
    }

    SECTION("SourceRegistry::GetSourceName")
    {
        REQUIRE(name1 == registry.GetSourceName(handle1));
        REQUIRE_THROWS(registry.GetSourceName(SIGNAL::SourceRegistry::BAD_HANDLE));
        REQUIRE_THROWS(registry.GetSourceName(handle1 + 1));
    }
}

