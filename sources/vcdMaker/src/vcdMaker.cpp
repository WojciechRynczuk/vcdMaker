/// @file vcdMaker/src/vcdMaker.cpp
///
/// The main module of the vcdMaker application.
///
/// @par Copyright (c) 2019 vcdMaker team
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

#include <memory>

#include "VCDTracer.h"
#include "CliMaker.h"
#include "TxtParser.h"
#include "SourceRegistry.h"
#include "LineCounter.h"
#include "VcdException.h"
#include "Logger.h"
#include "XmlSignalFactory.h"
#include "DefaultSignalFactory.h"
#include "OutOfMemory.h"

///  The vcdMaker main function.
///
///  @param argc Number of arguments.
///  @param argv The table of arguments.
///  @return The execution status.
int main(int argc, const char *argv[])
{
    // The application execution status.
    int32_t executionStatus = EXECUTION::APP_OK;

    std::set_new_handler(OutOfMemory);

    try
    {
        // Parse input parameters
        CLI::CliMaker cli;
        cli.Parse(argc, argv);

        // Build the signal factory.
        std::unique_ptr<PARSER::SignalFactory> pSignalFactory = NULL;
        if (!cli.GetUserLogFormat().empty())
        {
            pSignalFactory = std::make_unique<PARSER::XmlSignalFactory>(cli.GetUserLogFormat());
        }
        else
        {
            pSignalFactory = std::make_unique<PARSER::DefaultSignalFactory>();
        }

        // Create the log parser.
        PARSER::TxtParser txtLog(cli.GetInputFileName(),
                                 cli.GetTimebase(),
                                 SIGNAL::SourceRegistry::GetInstance(),
                                 *pSignalFactory,
                                 cli.IsVerboseMode());

        // Line counter.
        std::unique_ptr<INSTRUMENT::LineCounter> lineCounter;

        if (!cli.GetLineCounterName().empty())
        {
            // Register the line counting instrument.
            lineCounter = std::make_unique<INSTRUMENT::LineCounter>(cli.GetInputFileName(),
                                                                    cli.GetLineCounterName(),
                                                                    SIGNAL::SourceRegistry::GetInstance(),
                                                                    txtLog.GetSignalDb());
            txtLog.Attach(*lineCounter);
        }

        // Start parsing.
        txtLog.Execute();

        // Create the VCD tracer and dump the output file.
        TRACER::VCDTracer vcd_trace(cli.GetOutputFileName(),
                                    txtLog.GetSignalDb());
        vcd_trace.Dump();
    }
    catch (const EXCEPTION::VcdException &rException)
    {
        LOGGER::Logger::GetInstance().LogError(rException);
        executionStatus = EXECUTION::APP_ERROR;
    }
    catch (const TCLAP::CmdLineParseException &)
    {
        executionStatus = EXECUTION::APP_ERROR;
    }
    catch (const TCLAP::SpecificationException &)
    {
        executionStatus = EXECUTION::APP_ERROR;
    }

    return executionStatus;
}
