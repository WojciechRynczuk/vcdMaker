/*!
  @file signalcreator.cpp

  The signal creator interface class.

  @par Full Description
  Every signal can be created differently. The class provides the
  universal interface to create them.

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
#include "signalcreator.h"

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

  @param signalRegEx The regular expression to be matched.
  @return None
*/
CONSTRUCTION::SignalCreator::SignalCreator(char *signalRegEx) : m_SignalRegEx(signalRegEx)
{
};

/*!
  The signal creator default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
CONSTRUCTION::SignalCreator::~SignalCreator()
{
};


//***************************************************************************
// PROTECTED METHODS
//***************************************************************************

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************

