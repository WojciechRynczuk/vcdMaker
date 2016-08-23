/// @file vcdMaker.cpp
///
/// The main module of the vcdMaker application.
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
#include <string>

#include "VCDTracer.h"
#include "CliMaker.h"
#include "TxtParser.h"
#include "SourceRegistry.h"
#include "vcdExceptions.h"

///  The vcdMaker main function.
///
///  @param argc Number of arguments.
///  @param argv The table of arguments.
///  @return The execution status.
int main(int argc, const char *argv[])
{
    // Parse input parameters
    CLI::CliMaker cli;
    cli.Parse(argc, argv);

	// Source registry.
	SIGNAL::SourceRegistry Registry;

    try
    {
        // Parse the log file.
        PARSER::TxtParser txtLog(cli.GetInputFileName(), 
								 cli.GetTimebase(), 
			                     cli.IsVerboseMode(), 
			                     cli.GetLineCounterName(),
				                 Registry);

        // Create the VCD tracer and dump the output file.
        TRACER::VCDTracer vcd_trace(cli.GetOutputFileName(),
                                    txtLog.GetSignalDb());
        vcd_trace.Dump();
    }
	catch (const EXCEPTION::ConflictingNames &exception)
	{
		// Conflicting signal names in different sources.
		std::cerr << exception.what() << " Signal " << exception.GetName() << " in the sources: " 
			<< *Registry.GetName(exception.GetSourceA()) << " and " << *Registry.GetName(exception.GetSourceB()) << '\n';
	}
    catch (const std::runtime_error &exception)
    {
        std::cerr << exception.what() << '\n';
    }
}

