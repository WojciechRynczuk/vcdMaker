/// @file common/src/FSignal.cpp
///
/// The signal class supporting real numbers.
///
/// @par Full Description
/// The class supports the VCD real numbers. It allows for printing
/// and comparing real signal values.
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

#include <sstream>

#include "FSignal.h"

std::string SIGNAL::FSignal::Print() const
{
    return ('r' + m_Value + ' ' + m_Name);
}

bool SIGNAL::FSignal::EqualTo(Signal const &other) const
{
    if (FSignal const *p = dynamic_cast<FSignal const *>(&other))
    {
        return (m_Value == p->m_Value);
    }
    else
    {
        return false;
    }
}
