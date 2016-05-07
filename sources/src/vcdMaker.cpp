/// @file vcdMaker.cpp
///
/// The main module of the vcdMaker application.
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

#include <iostream>
#include <fstream>
#include <string>

#include "VCDTracer.h"
#include "SignalFactory.h"
#include "CliParserImpl.h"

///  The vcdMaker main function.
///
///  @param argc Number of arguments.
///  @param argv The table of arguments.
///  @return The execution status.
int main(int argc, char *argv[])
{
    // Parse input parameters
    CLI::CliParserImpl CLI(argc, argv);
    if (false == CLI.Validate())
    {
        return -1;
    }

    // Get parameters' values
    const std::string log_file = CLI.GetParamValue("-f");
    const std::string vcd_file = CLI.GetParamValue("-o");
    const std::string tbase = CLI.GetParamValue("-t");

    // Check if the verbose mode has been enabled
    bool is_verbose = CLI.CheckParam("-v");
    uint32_t valid_lines = 0;
    uint32_t invalid_lines = 0;

    // Validate the time base.
    if (!TRACER::VCDTracer::isTimeUnitValid(tbase))
    {
        std::cout << "Invalid time base.\n";
        return -1;
    }

    // Open the log file
    std::ifstream file(log_file);
    if (!file)
    {
        std::cout << "File " << log_file << " does not exist.\n";
        return -1;
    }
    std::string line;

    // Create VCD tracer
    TRACER::VCDTracer  VcdTrace(vcd_file, tbase);

    // Create the signal factory
    CONSTRUCTION::SignalFactory signalFactory;

    // A signal
    SIGNAL::Signal *pSignal = nullptr;

    // Process the log file
    while (std::getline(file, line))
    {
        pSignal = signalFactory.Create(line);
        if (pSignal != nullptr)
        {
            VcdTrace.Log(pSignal);
            valid_lines++;
        }
        else
        {
            if (true == is_verbose)
            {
                std::cout << "Invalid log line " << valid_lines + invalid_lines << " : " << line << '\n';
            }
            invalid_lines++;
        }
    }

    // Create the VCD file
    VcdTrace.Dump();

    // Summary
    std::cout << '\n' << "Parsed " << log_file << ": \n";
    std::cout << "\t Valid lines:   " << valid_lines << '\n';
    std::cout << "\t Invalid lines: " << invalid_lines << '\n';
}

