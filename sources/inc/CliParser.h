/*!
  @file cliparser.h

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
#ifndef __CLIPARSER_H__
#define __CLIPARSER_H__

/*!
    @defgroup CLI CLI

    @brief The Command Line Interface group.

    @par Full Description
    This is a simple CLI parser.

*/

// SYSTEM INCLUDES
#include <string>    //std::string

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
// (none)

// FORWARD REFERENCES
// (none)

namespace CLI
{

//!  The base CLI parser class.
    /*!
      The base CLI parser class.
    */
    class CliParser
    {
        public:
            // PUBLIC METHODS
            //! The CLI constructor.
            /*!
              This constructor shall be used by the iheriting classes.
              The begin argument shall point to argv while the end shall
              point to argv+argc.
            */
            CliParser(char **begin, char **end);

            //! The default destructor.
            /*!
              The default destructor.
            */
            ~CliParser();

            //! Get the value of the given parameter.
            /*!
              Returns the value of the given parameter.
              E.g. for "-f" it could return the file name.
            */
            char *GetParamValue(const std::string &param) const ;

            //! Check the parameter's existence.
            /*!
              Returns true if the provided string has been a part of the
              command line input.
            */
            bool CheckParam(const std::string &param) const ;

            //! Validates input parameters.
            /*!
              Returns true if the input parameters are valid.
              It shall be called upon the construction of the object.
            */
            bool Validate() const ;

        protected:
            // PROTECTED METHODS
            //! Print one line help information.
            /*!
              Prints one line help information.
            */
            virtual void OneLineHelp() const = 0;

            //! Print full help infomration.
            /*!
              Prints full help infomration.
            */
            virtual void Help() const = 0;

            //! The parameters validator.
            /*!
              The parameters validator method is used by the
              Validate() method to analyse the provided input.
            */
            virtual bool Validator() const = 0;

        private:
            // PRIVATE METHODS
            // (none)

            // MEMBER VARIABLES
            //! The beginning of the CLI string.
            char **m_Begin;

            //! The end of the CLI string.
            char **m_End;
    };

}

#endif

