/// @file CliParserImpl.h
///
/// The VCD maker CliParser implementation.
///
/// @ingroup CLI
///
/// @par Copyright (c) 2016 Wojciech Rynczuk
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

#include "stdafx.h"
#include <iostream>

#include "CliParserImpl.h"

void CLI::CliParserImpl::OneLineHelp() const
{
    std::cout << "Use: 'vcdMaker.exe -h' for help." << std::endl;
}

void CLI::CliParserImpl::Help() const
{
    std::cout << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "vcdMaker -f file_in -o file_out -t [s|ms|us|ns|ps|fs] [-v]" << std::endl;
    std::cout << "\t file_in  - Input log filename." << std::endl;
    std::cout << "\t file_out - Ouput VCD filename." << std::endl;
    std::cout << "\t tbase    - Base time unit to be selected. One of the available options shall be used, e.g. \"ms\"." <<
              std::endl;
    std::cout << "\t -v       - This optional parameter enables the verbose mode." << std::endl;
    std::cout << std::endl;
    std::cout << "\t Example: vcdMaker -f log.txt -o wave.vcd -t ms" << std::endl;
}

bool CLI::CliParserImpl::Validator() const
{
    bool result = true;
    char *log_file = GetParamValue("-f");
    if (log_file == NULL)
    {
        std::cout << "No log filename provided." << std::endl;
        result = false;
    }

    char *vcd_file = GetParamValue("-o");
    if (vcd_file == NULL)
    {
        std::cout << "No VCD filename provided." << std::endl;
        result = false;
    }

    char *tbase = GetParamValue("-t");
    if (tbase == NULL)
    {
        std::cout << "No time base unit provided." << std::endl;
        result = false;
    }

    if (false == result)
    {
        OneLineHelp();
    }

    return result;
}
