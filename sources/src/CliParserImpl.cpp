/// @file CliParserImpl.h
///
/// The VCD maker CliParser implementation.
///
/// @ingroup CLI
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

#include <iostream>

#include "CliParserImpl.h"

void CLI::CliParserImpl::OneLineHelp() const
{
    std::cout << "Use: 'vcdMaker.exe -h' for help.\n";
}

void CLI::CliParserImpl::Help() const
{
    std::cout << "\n"
              << "Usage: \n"
              << "vcdMaker -f file_in -o file_out -t [s|ms|us|ns|ps|fs] [-v]\n"
              << "\t file_in  - Input log filename.\n"
              << "\t file_out - Ouput VCD filename.\n"
              << "\t tbase    - Base time unit to be selected. One of the available options shall be used, e.g. \"ms\".\n"
              << "\n"
              << "\t -v       - This optional parameter enables the verbose mode.\n"
              << "\n"
              << "\t Example: vcdMaker -f log.txt -o wave.vcd -t ms\n";
}

bool CLI::CliParserImpl::Validator() const
{
    bool result = true;

    const std::string log_file = GetParamValue("-f");
    if (log_file.empty())
    {
        std::cout << "No log filename provided.\n";
        result = false;
    }

    const std::string vcd_file = GetParamValue("-o");
    if (vcd_file.empty())
    {
        std::cout << "No VCD filename provided.\n";
        result = false;
    }

    const std::string tbase = GetParamValue("-t");
    if (tbase.empty())
    {
        std::cout << "No time base unit provided.\n";
        result = false;
    }

    if (false == result)
    {
        OneLineHelp();
    }

    return result;
}
