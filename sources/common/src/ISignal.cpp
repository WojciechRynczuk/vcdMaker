/// @file ISignal.h
///
/// The signal class supporting integer numbers.
///
/// @par Full Description
/// The class supports the VCD integer numbers. It allows for printing
/// and comparing integer signal values.
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

#include <bitset>

#include "ISignal.h"

std::string SIGNAL::ISignal::Print() const
{
    const std::bitset<64> valueBits(m_Value);
    const std::string valueBitStr =
        valueBits.to_string().substr(valueBits.size() - m_Size);

    return ('b' + valueBitStr + ' ' + m_Name);
}

std::string SIGNAL::ISignal::Footprint() const
{
    const std::string sizeFootprint(m_Size, 'x');
    return ('b' + sizeFootprint + ' ' + m_Name);
}

bool SIGNAL::ISignal::EqualTo(Signal const &other) const
{
    if (ISignal const *p = dynamic_cast<ISignal const *>(&other))
    {
        return (m_Value == p->m_Value);
    }
    else
    {
        return false;
    }
}
