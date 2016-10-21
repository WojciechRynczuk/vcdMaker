/// @file Utils.h
///
/// The utilities.
///
/// @par Full Description
/// The utilities used among vcdMaker applications.
///
/// @ingroup Utils
///
/// @par Copyright (c) 2016 vcdMaker team
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
#include <sstream>
#include <stdexcept>

#include "Utils.h"
#include "Signal.h"

std::vector<std::string> UTILS::Split(const std::string &inString,
                                      const char delimiter)
{
    std::vector<std::string> outStrings;
    std::stringstream inStream(inString);
    std::string outField;

    while (std::getline(inStream, outField, delimiter))
    {
        outStrings.push_back(outField);
    }

    return outStrings;
}

bool UTILS::IsTimeUnitValid(const std::string &unit)
{
    return (std::find(SIGNAL::Signal::TIME_UNITS.cbegin(),
                      SIGNAL::Signal::TIME_UNITS.cend(),
                      unit) != SIGNAL::Signal::TIME_UNITS.cend());
}

size_t UTILS::GetTimeUnitIndex(const std::string &unit)
{
    const size_t index = (std::find(SIGNAL::Signal::TIME_UNITS.cbegin(),
                                    SIGNAL::Signal::TIME_UNITS.cend(),
                                    unit) - SIGNAL::Signal::TIME_UNITS.cbegin());

    if (index == SIGNAL::Signal::TIME_UNITS.size())
    {
        throw std::runtime_error("Invalid time unit " + unit);
    }
    else
    {
        return index;
    }
}
