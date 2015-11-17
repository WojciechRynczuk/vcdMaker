/*!
  @file signal.h

  The base VCD signal class.

  @par Full Description
  The base signal class contains the common signal properties and
  methods.

  @if REVISION_HISTORY_INCLUDED
  @par Edit History
  @li [0]    wojciech.rynczuk@wp.pl    16-DEC-2014    Initial file revision.
  @endif

  @ingroup Signal

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
#ifndef __SIGNAL_H__
#define __SIGNAL_H__

/*!
    @defgroup Signal Signal

    @brief The group defines different types of signals.

    @par Full Description
    The group consists of the base class defining the common behaviours as
    well as of the inheriting signal classes specifying concrete signals.

*/

// SYSTEM INCLUDES
#include <stdint.h>  //Standard types
#include <string>    //std::string

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
// (none)

// FORWARD REFERENCES
// (none)

namespace SIGNAL
{

//!  A base signal class.
    /*!
      The base VCD signal class. The integer and real signal classes
      inherit from it.
    */
    class Signal
    {
        public:
            // PUBLIC METHODS
            //! The signal constructor.
            /*!
              This constructor shall be used by the iheriting classes.
              It initializes the basic signal properties: the name, the size
              and the type.

              The name shall consist of any alphanumeric string in which the module's
              levels are separated with '.'.
              E.g. Module1.Level3.Variable6

              The size usually corresponds to any of the integral data type
              sizes: 8, 16, 32 or 64.

              The type string is used to produce the VCD header. It describes
              the type of the signal and shall equal to "wire" or "real".
            */
            Signal(const std::string &name, uint32_t size, const std::string &type);

            //! The default constructor.
            /*!
              It is needed by the multiset container within the VCD tracer module.
            */
            Signal();

            //! The default destructor.
            /*!
              The default destructor.
            */
            ~Signal();

            //! Get the signal name.
            /*!
              Returns the signal's name.
              The method is used while generating the header and the body
              of the VCD file.
            */
            std::string GetName() const ;

            //! Get the signal size.
            /*!
              Returns the signal's size in bits.
              The method is used while generating the VCD header.
            */
            uint32_t GetSize() const ;

            //! Get the signal timestamp.
            /*!
              Returns the signal's timestamp in time units.
              The method is used while generating the body of the VCD file.
            */
            uint64_t GetTimestamp() const ;

            //! Get the signal type.
            /*!
              Returns the signal's type.
              The method is used while generating the VCD header.
            */
            std::string GetType() const;

            //! Get the signal's value as a string.
            /*!
              Returns the signal's value as a string in the VCD format.
              The method is used while generating the body of the VCD file.
            */
            virtual std::string Print() const;

            //! Get the signal's footprint as a string.
            /*!
              Returns the signal's footprint as a string in the VCD format.
              The method is used while generating the header of the VCD file.
            */
            virtual std::string Footprint() const;

            //! The overloaded () operator.
            /*!
              The () operator has to be overloaded so as the multiset container
              could use pointers to the Signal class.
            */
            bool operator() (const Signal *signal1, const Signal *signal2) const;

        protected:
            // PROTECTED METHODS
            //! The signal comparison method.
            /*!
              This comparison method is used by the overloaded comparison operator
              within the base class. It allows for comparing two signals of the same
              type. It is not important if it's greater or lesser. It is crucial to
              determine its change.
            */
            virtual bool equal_to(Signal const &other) const;

        private:
            // PRIVATE METHODS
            //! The overloaded == operator.
            /*!
              It is used to compare two signals of the same type so as to tell
              if's changed or not.
            */
            friend bool operator == (const Signal &lsignal, const Signal &rsignal);

            //! The overloaded != operator.
            /*!
              Not used but implemented to main the consistency with the == operator.
            */
            friend bool operator != (const Signal &lsignal, const Signal &rsignal);

        protected:
            // MEMBER VARIABLES
            //! The signal's name.
            std::string m_Name;

            //! The signal's type.
            std::string m_Type;

            //! The signal's size.
            uint32_t m_Size;

            //!The signal's timestamp.
            uint64_t m_Timestamp;
    };

}

#endif

