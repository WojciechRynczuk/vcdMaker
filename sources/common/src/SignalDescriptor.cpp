/// @file common/src/SignalDescriptor.cpp
///
/// The signal descriptor.
///
/// @par Full Description
/// The signal descriptor defines a signal's constant properties such as
/// name, size, type and source.
///
/// @ingroup Signal
///
/// @par Copyright (c) 2020 vcdMaker team
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

#include "SignalDescriptor.h"

/// Returns the signal's name.
const std::string &SIGNAL::SignalDescriptor::GetName() const
{
    return m_Name;
}

/// Returns the signal's size in bits.
size_t SIGNAL::SignalDescriptor::GetSize() const
{
    return m_Size;
}

/// Returns the signal's type.
const std::string &SIGNAL::SignalDescriptor::GetType() const
{
    return m_Type;
}

/// Returns the source handle of the signal.
SIGNAL::SourceRegistry::HandleT SIGNAL::SignalDescriptor::GetSource() const
{
    return m_SourceHandle;
}

/// Check signal consistency.
bool SIGNAL::SignalDescriptor::SimilarTo(const std::string &rType, size_t size, SourceRegistry::HandleT sourceHandle) const
{
    return ((GetType() == rType) &&
            (GetSize() == size) &&
            (GetSource() == sourceHandle));
}

/// Checks if two descriptors match.
bool SIGNAL::SignalDescriptor::EqualTo(SignalDescriptor const &other) const
{
    return ((m_Name == other.GetName()) &&
            (m_Type == other.GetType()) &&
            (m_Size == other.GetSize()) &&
            (m_SourceHandle == other.GetSource()));
}
