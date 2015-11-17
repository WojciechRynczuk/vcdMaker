/*!
  @file cliparserimpl.h

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
#ifndef __CLIPARSERIMPL_H__
#define __CLIPARSERIMPL_H__

// SYSTEM INCLUDES
#include <string>      //std::string

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "CliParser.h"

// FORWARD REFERENCES
// (none)

namespace CLI
{

//!  The specific implementation of the CliParser class.
    /*!
      The specific implementation of the CliParser class.
    */
    class CliParserImpl : public CliParser
    {
        public:
            // PUBLIC METHODS
            //! The constructor.
            /*!
              The begin argument shall point to argv while the end shall
              point to argv+argc.
            */
            CliParserImpl(char **begin, char **end);

            //! The default destructor.
            /*!
              The default destructor.
            */
            ~CliParserImpl();

        protected:
            // PROTECTED METHODS
            //! Print one line help information.
            /*!
              Prints one line help information.
            */
            virtual void OneLineHelp() const;

            //! Print full help infomration.
            /*!
              Prints full help infomration.
            */
            virtual void Help() const;

            //! The parameters' validator.
            /*!
              The parameters' validator method is used by the
              Validate() method to analyse the provided input.
            */
            virtual bool Validator() const;

        private:
            // PRIVATE METHODS
            // (none)

            // MEMBER VARIABLES
    };

}

#endif

