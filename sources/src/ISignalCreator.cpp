/*!
  @file isignalcreator.cpp

  The integer signal creator.

  @par Full Description
  The integer signal creator.

  @if REVISION_HISTORY_INCLUDED
  @par Edit History
  @li [0]    wojciech.rynczuk@wp.pl    09-JAN-2015    Initial file revision.
  @endif

  @ingroup Construction

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

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "isignalcreator.h"
#include "isignal.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The signal creator constructor.

  @par Full Description
  The constructor initializes the regular expression member variable
  which will be matched against the log line.

  @return None
*/
CONSTRUCTION::ISignalCreator::ISignalCreator() : SignalCreator("^#([[:d:]]+) ([[:graph:]]+) ([[:d:]]+) ([[:d:]]+).*$")
{
};

/*!
  The signal creator default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
CONSTRUCTION::ISignalCreator::~ISignalCreator()
{
}

/*!
  Create the integer signal object.

  @par Full Description
  It creates the integer signal object if the log line is valid and returns
  the pointer to the newly created object.
  If the log line is not matching the integer object specification
  then NULL is returned.

  @param logLine The log line serving as the creation specification.
  @return Signal pointer if the object has been created or NULL.
*/
SIGNAL::Signal *CONSTRUCTION::ISignalCreator::Create(std::string &logLine)
{
    std::tr1::cmatch result;
    SIGNAL::Signal *pSignal = NULL;
    if (true == std::tr1::regex_search(logLine.begin(), logLine.end(), m_SignalRegEx))
    {
        //Parse the log line
        std::tr1::regex_search(logLine.c_str(), result, m_SignalRegEx);

        //Create the signal object
        pSignal = new SIGNAL::ISignal(result[2].str(), std::stoi(result[4].str()), std::stoll(result[1].str()),
                                      std::stoll(result[3].str()));
    }
    return pSignal;
}

