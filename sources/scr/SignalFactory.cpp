/*!
  @file signalfactory.cpp

  The signal factory class.

  @par Full Description
  The signal factory object creates the appropriate signal objects.

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
#include "signalfactory.h"
#include "ISignalCreator.h"
#include "FSignalCreator.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The signal constructor to be used by inheriting classes.

  @par Full Description
  The constructor initializes the basic signal's properties like the name,
  the size and the type.

  @return None
*/
CONSTRUCTION::SignalFactory::SignalFactory()
{
    // Create creators objects
    ISignalCreator *iMaker = new ISignalCreator();
    FSignalCreator *fMaker = new FSignalCreator();

    // Register creators
    m_vpSignalCreators.push_back(iMaker);
    m_vpSignalCreators.push_back(fMaker);
};

/*!
  The signal factory default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
CONSTRUCTION::SignalFactory::~SignalFactory()
{
    // Creators iterator
    std::vector<SignalCreator *>::const_reverse_iterator it;

    //Destroy signal creators
    for (it = m_vpSignalCreators.crbegin(); it != m_vpSignalCreators.crend(); ++it)
    {
        delete *it;
    }
};

/*!
  Get the signal's name.

  @par Full Description
  It returns a string containing the signal's name.

  @param logLine The log line used to create the signal object.
  @return The name of the signal.
*/
SIGNAL::Signal *CONSTRUCTION::SignalFactory::Create(std::string &logLine)
{
    // Creators iterator
    std::vector<SignalCreator *>::const_reverse_iterator rit;

    // Signal object pointer
    SIGNAL::Signal *pSignal = NULL;

    // Try to use any of the available constructors
    for (rit = m_vpSignalCreators.crbegin(); (rit != m_vpSignalCreators.crend()) && (pSignal == NULL); ++rit)
    {
        pSignal = (*rit)->Create(logLine);
    }
    return pSignal;
}

//***************************************************************************
// PROTECTED METHODS
//***************************************************************************

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************

