/*!
  @file cliparser.cpp

  The base class of the CLI parser.

  @par Full Description
  The base class of the simple Command Line Interface parser.

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
#include <algorithm> // std::find

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "cliparser.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The CliParser constructor.

  @par Full Description
  The CliParser constructor to be used by inheriting classes.

  @param begin The beginning of the input string (argv).
  @param end The end of the input string (argv+argc).
  @return None
*/
CLI::CliParser::CliParser(char **begin, char **end) : m_Begin(begin), m_End(end)
{
};

/*!
  The CLI object default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
CLI::CliParser::~CliParser()
{
};

/*!
  Get the value of the given input parameter.

  @par Full Description
  Returns the value of the given input parameter as a char*.
  If not found, NULL is returned.

  @param param The parameter.
  @return The value of the input parameter.
*/
char *CLI::CliParser::GetParamValue(const std::string &param) const
{
    char **itr = std::find(m_Begin, m_End, param);
    if (itr != m_End && ++itr != m_End)
    {
        return *itr;
    }
    return NULL;
};

/*!
  Check if the given input parameter has been provided.

  @par Full Description
  Returns true if the given parameter has been provided.

  @param param The parameter.
  @return The result of the check.
*/
bool CLI::CliParser::CheckParam(const std::string &param) const
{
    return std::find(m_Begin, m_End, param) != m_End;
};

/*!
  Validate the input.

  @par Full Description
  Validates the data within the object.

  @return Returns true if the input is proper.
*/
bool CLI::CliParser::Validate() const
{
    if ((m_End - m_Begin) < 2)
    {
        OneLineHelp();
        return false;
    }

    if (CheckParam("-h"))
    {
        Help();
        return false;
    }

    return Validator();
};

//***************************************************************************
// PROTECTED METHODS
//***************************************************************************

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************

