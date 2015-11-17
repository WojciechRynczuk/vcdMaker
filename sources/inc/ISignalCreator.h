/*!
  @file isignalcreator.h

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
#ifndef __ISIGNALCREATOR_H__
#define __ISIGNALCREATOR_H__

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "signalcreator.h"

// FORWARD REFERENCES
// (none)

namespace CONSTRUCTION
{

//!  An integer signal creator class.
    /*!
      The class provides means to create integer signal objects.
    */
    class ISignalCreator : public SignalCreator
    {
        public:
            // PUBLIC METHODS
            //! The signal creator constructor.
            /*!
              The integer signal creator constructor.
            */
            ISignalCreator();

            //! The default destructor.
            /*!
              The default destructor.
            */
            ~ISignalCreator();

            //! The signal creation method.
            SIGNAL::Signal *Create(std::string &logLine);

        protected:
            // PROTECTED METHODS
    };

}

#endif

