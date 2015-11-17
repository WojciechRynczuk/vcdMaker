/*!
  @file signalcreator.h

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
#ifndef __SIGNALCREATOR_H__
#define __SIGNALCREATOR_H__

// SYSTEM INCLUDES
#include <string>      //std::string
#include <regex>       //std::tr1::regex

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "signal.h"

// FORWARD REFERENCES
// (none)

namespace CONSTRUCTION
{

//!  A base signal creator class.
    /*!
      The class provides the interface to create the signal object.
    */
    class SignalCreator
    {
        public:
            // PUBLIC METHODS
            //! The signal creator constructor.
            /*!
              The default signal creator constructor.
            */
            SignalCreator(char *signalRegEx);

            //! The default destructor.
            /*!
              The default destructor.
            */
            ~SignalCreator();

            //! Return the pointer to the signal object.
            /*!
              Return the pointer to the newly created object or NULL.
            */
            virtual SIGNAL::Signal *Create(std::string &logLine) = 0;

        protected:
            // PROTECTED METHODS

        private:
            // PRIVATE METHODS

        protected:
            // MEMBER VARIABLES
            //! The RegEx matching the signal description.
            std::tr1::regex m_SignalRegEx;
    };

}

#endif

