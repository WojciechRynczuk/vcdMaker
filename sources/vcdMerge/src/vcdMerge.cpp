/// @file vcdMerge.cpp
///
/// The main module of the vcdMerge application.
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

#include "CliMerge.h"
#include "VCDTracer.h"
#include "Source.h"
#include "SourceRegistry.h"
#include "VcdExceptions.h"

///  The vcdMerge main function.
///
///  @param argc Number of arguments.
///  @param argv The table of arguments.
///  @return The execution status.
int main(int argc, const char *argv[])
{
    // Parse input parameters
    CLI::CliMerge cli;
    cli.Parse(argc, argv);

    // Source registry.
    SIGNAL::SourceRegistry registry;

    try
    {
        // Get input filenames
        std::vector<std::string> inSources;
        cli.GetInputSources(inSources);

        // Print all file to be merged
        std::cout << "Merging: " << std::endl;
        for (const std::string &source : inSources)
        {
            std::cout << '\n' << '\t' << source << '\n';
            MERGE::Source *pSource = new MERGE::Source(source, registry, cli.IsVerboseMode());
            delete pSource;
        }
        std::cout << '\n';
    }
    catch (const EXCEPTION::ConflictingNames &exception)
    {
        // Conflicting signal names in different sources.
        std::cerr << exception.what()
                  << " Signal "
                  << exception.GetName()
                  << " in the sources: "
                  << registry.GetSourceName(exception.GetSourceA())
                  << " and "
                  << registry.GetSourceName(exception.GetSourceB())
                  << '\n';
    }
    catch (const std::runtime_error &exception)
    {
        std::cerr << exception.what() << '\n';
    }
}


