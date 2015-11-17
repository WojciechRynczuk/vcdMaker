/*!
  @file cliparserimpl.cpp

  The VCD maker CliParser implementation.

  @par Full Description
  The VCD maker CliParser implementation.

  @if REVISION_HISTORY_INCLUDED
  @par Edit History
  @li [0]    wojciech.rynczuk@wp.pl    20-JAN-2015    Initial file revision.
  @endif

  @ingroup CLI

  @par Copyright (c) MMXV Wojciech Rynczuk

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

// SYSTEM INCLUDES
#include "stdafx.h"  // Precompiled header for the Windows platform
// Create the empty stdafx.h file for other platforms.
#include <iostream>  // std::cout

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "cliparserimpl.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The CliParser specific constructor.

  @par Full Description
  The CliParser specific constructor.

  @param begin The beginning of the input string (argv).
  @param end The end of the input string (argv+argc).
  @return None
*/
CLI::CliParserImpl::CliParserImpl(char **begin, char **end) : CliParser(begin, end)
{
};

/*!
  The CLI default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
CLI::CliParserImpl::~CliParserImpl()
{
};

//***************************************************************************
// PROTECTED METHODS
//***************************************************************************
/*!
  Print one line help information.

  @par Full Description
  Prints one line help information.

  @return None
*/
void CLI::CliParserImpl::OneLineHelp() const
{
    std::cout << "Use: 'vcdMaker.exe -h' for help." << std::endl;
}

/*!
  Print full help infomration.

  @par Full Description
  Prints full help infomration.

  @return None.
*/
void CLI::CliParserImpl::Help() const
{
    std::cout << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "vcdMaker -f file_in -o file_out -t [s|ms|us|ns|ps|fs]" << std::endl;
    std::cout << "\t file_in  - Input log filename." << std::endl;
    std::cout << "\t file_out - Ouput VCD filename." << std::endl;
    std::cout << "\t tbase    - Base time unit to be selected. One of the available options shall be used, e.g. \"ms\"." <<
              std::endl;
    std::cout << std::endl;
    std::cout << "\t Example: vcdMaker -f log.txt -o wave.vcd -t ms" << std::endl;
}

/*!
  Validate the input.

  @par Full Description
  Validates the input parameters and returns
  true if they are valid.

  @return The result of the validation.
*/
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

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************

