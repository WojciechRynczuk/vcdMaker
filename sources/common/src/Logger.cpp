/// @file Logger.cpp
///
/// An error and warning logger.
///
/// @par Full Description
/// This is a simple module for printing error and warning messages.
///
/// @ingroup Logger
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

#include <iostream>
#include <sstream>
#include <iomanip>

#include "Logger.h"

void LOGGER::Logger::LogWarning(uint32_t number, const std::string &rMessage)
{
    Log(std::cout, "Warning", number, rMessage);
}

void LOGGER::Logger::Log(const EXCEPTION::VcdException &rException)
{
    Log(std::cerr, "Error", rException.GetId(), rException.what());
}

const std::string LOGGER::Logger::FormatNumber(uint32_t number) const
{
    std::ostringstream exceptionValue;

    exceptionValue << std::setfill('0') << std::setw(4) << number;
    return exceptionValue.str();
}

void LOGGER::Logger::Log(std::ostream &rOs, const std::string &rType, uint32_t number, const std::string &rMessage)
{
    rOs << "[" << rType << " " << FormatNumber(number) << "]: " << rMessage << '\n';
}
