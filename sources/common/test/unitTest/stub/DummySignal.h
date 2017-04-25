/// @file DummySignal.h
///
/// The dummy signal class.
///
/// @par Full Description
/// The dummy signal class. It implements Signal interface for Unit Test
/// purposes.
///
/// @ingroup UnitTest
///
/// @par Copyright (c) 2017 vcdMaker team
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

/// Dummy signal class.
class DummySignal : public SIGNAL::Signal
{
    public:

        static const size_t DUMMY_SIZE = 1;
        static constexpr const char *DUMMY_TYPE = "dummy";
        static const SIGNAL::SourceRegistry::HandleT DUMMY_HANDLE = 1;

        /// Dumy signal signal constructor.
        DummySignal(const std::string &name,
                    uint64_t timestamp) :
            Signal(name,
                   DUMMY_SIZE,
                   timestamp,
                   DUMMY_TYPE,
                   DUMMY_HANDLE)
        {
        }

        /// Dumy signal signal cloning method.
        virtual Signal *Clone() const
        {
            return new DummySignal(*this);
        }

        /// @copydoc Signal::Print()
        virtual std::string Print() const
        {
            return "PRINT " + GetName();
        }

        /// @copydoc Signal::Footprint()
        virtual std::string Footprint() const
        {
            return "FOOTPRINT " + GetName();
        }

    protected:

        /// @copydoc Signal::EqualTo()
        virtual bool EqualTo(Signal const &other) const
        {
            return (GetName() == other.GetName());
        }
};
