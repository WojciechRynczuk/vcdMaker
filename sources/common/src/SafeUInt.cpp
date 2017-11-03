/// @file common/src/SafeUInt.cpp
///
/// The safe integer implementations.
///
/// @par Full Description
/// The basic safe integer implementations.
///
/// @ingroup Generic
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

#include "SafeUInt.h"

/// Overrides the output stream operator.
std::ostream &operator<<(std::ostream &out, SafeUInt<uint64_t> &ts)
{
    out << ts.GetValue();
    return out;
}

/// Overrides the multiplication operator.
SafeUInt<uint64_t> operator*(uint64_t lhs, const SafeUInt<uint64_t> &rhs)
{
    if (lhs)
    {
        if ((std::numeric_limits<uint64_t>::max() / lhs) < rhs.GetValue())
        {
            throw std::out_of_range("");
        }
    }
    return SafeUInt<uint64_t>(lhs * rhs.GetValue());
}
