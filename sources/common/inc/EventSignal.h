/// @file EventSignal.h
///
/// The signal class supporting events
///
/// @par Full Description
/// The class supports the VCD events.
///
/// @ingroup Signal
///
/// @par Copyright (c) 2016 vcdMaker team
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
/// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#pragma once

#include "Signal.h"

namespace SIGNAL
{
    /// The class inherits from the Signal class and handles VCD events.
    class EventSignal : public Signal
    {
        public:

            /// The event signal constructor.
            ///
            /// It initializes the basic signal properties: the name and the timestamp.
            ///
            /// The name shall consist of any alphanumeric string in which the module's
            /// levels are separated with '.'.
            /// E.g. Module1.Level3.Variable6
            EventSignal(const std::string &name,
                        uint64_t timestamp,
                        SourceRegistry::HandleT sourceHandle) :
                Signal(name, 0, timestamp, "event", sourceHandle)
            {
            }

            /// The event signal cloning method.
            virtual Signal *Clone() const
            {
                return new EventSignal(*this);
            }

            /// @copydoc Signal::Print()
            virtual std::string Print() const
            {
                return ("1" + m_Name);
            }

            /// @copydoc Signal::Footprint()
            virtual std::string Footprint() const
            {
                return "";
            }

        protected:

            /// @copydoc Signal::EqualTo()
            virtual bool EqualTo(Signal const &) const
            {
                return false;
            }

    };

}
