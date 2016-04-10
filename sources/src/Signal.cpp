/// @file Signal.h
///
/// The base VCD signal class.
///
/// @par Full Description
/// The base signal class contains the common signal properties and
/// methods.
///
/// @ingroup Signal
///
/// @par Copyright (c) 2016 Wojciech Rynczuk
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

#include "stdafx.h"

#include "signal.h"

SIGNAL::Signal::Signal(const std::string &name, uint32_t size, const std::string &type) : m_Name(name), m_Size(size),
    m_Timestamp(0), m_Type(type)
{
};

SIGNAL::Signal::Signal() : m_Name(""), m_Size(0), m_Timestamp(0), m_Type("")
{
};

SIGNAL::Signal::~Signal()
{
};

std::string  SIGNAL::Signal::GetName() const
{
    return m_Name;
};

uint32_t SIGNAL::Signal::GetSize() const
{
    return m_Size;
};

uint64_t SIGNAL::Signal::GetTimestamp() const
{
    return m_Timestamp;
};

std::string SIGNAL::Signal::GetType() const
{
    return m_Type;
};

std::string SIGNAL::Signal::Print() const
{
    return "";
};

std::string SIGNAL::Signal::Footprint() const
{
    return "";
};

bool  SIGNAL::Signal::operator() (const Signal *signal1, const Signal *signal2) const
{
    return signal1->m_Timestamp < signal2->m_Timestamp;
};

bool SIGNAL::Signal::equal_to(Signal const &other) const
{
    return 0;
}

bool SIGNAL::operator == (const Signal &lsignal, const Signal &rsignal)
{
    return lsignal.equal_to(rsignal);
};

bool SIGNAL::operator != (const Signal &lsignal, const Signal &rsignal)
{
    return !lsignal.equal_to(rsignal);
};
