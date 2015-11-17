/*!
  @file isignal.h

  The signal class supporting integer numbers.

  @par Full Description
  The class supports the VCD integer numbers. It allows for printing
  and comparing integer signal values.

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
#ifndef __ISIGNAL_H__
#define __ISIGNAL_H__

// SYSTEM INCLUDES
// (none)

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "signal.h"

// FORWARD REFERENCES
// (none)

namespace SIGNAL
{

//!  This signal class handles integer numbers.
    /*!
      The class inherits from the Signal class and handles the integer
      signal values.
    */
    class ISignal : public Signal
    {
        public:
            // PUBLIC METHODS
            //! The integer signal constructor.
            /*!
              It initializes the basic signal properties: the name, the size, the timestamp
              and the value.

              The name shall consist of any alphanumeric string in which the module's
              levels are separated with '.'.
              E.g. Module1.Level3.Variable6
            */
            ISignal(const std::string &name, uint32_t size, uint64_t timestamp, uint64_t value);

            //! The default destructor.
            ~ISignal();

            //! Set the signal's value.
            void SetValue(uint64_t timestamp, uint64_t value);

            //! Return the signal's value.
            uint64_t GetValue() const;

            //! Print the signal's value in the VCD format.
            std::string Print() const;

            //! Print the signal's footprint in the VCD format.
            std::string Footprint() const;

        protected:
            // PROTECTED METHODS
            //! Compare two integer signals.
            bool equal_to(Signal const &other) const;

            //! The signal's value.
            uint64_t m_Value;
    };

}

#endif

