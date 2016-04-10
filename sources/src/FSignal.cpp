/// @file FSignal.h
///
/// The signal class supporting real numbers.
///
/// @par Full Description
/// The class supports the VCD real numbers. It allows for printing
/// and comparing real signal values.
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
#include <stdio.h>

#include "fsignal.h"

SIGNAL::FSignal::FSignal(const std::string &name, uint64_t timestamp, double value) : Signal(name, 64, "real")
{
    m_Timestamp = timestamp;
    m_Value = value;
};

SIGNAL::FSignal::~FSignal()
{
}

void SIGNAL::FSignal::SetValue(uint64_t timestamp, double value)
{
    m_Timestamp = timestamp;
    m_Value = value;
};

double SIGNAL::FSignal::GetValue() const
{
    return m_Value;
};

std::string SIGNAL::FSignal::Print() const
{
    std::string vcd_value = "r";
    char buffer[30];

    #ifdef WIN32
    sprintf_s(buffer, 30, "%.16g", m_Value);
    #else
    snprintf(buffer, 30, "%.16g", m_Value);
    #endif
    vcd_value += buffer;

    vcd_value += " ";
    vcd_value += m_Name;
    vcd_value += "\n";

    return vcd_value;
}

std::string SIGNAL::FSignal::Footprint() const
{
    std::string vcd_value = "r0.0 ";

    vcd_value += m_Name;
    vcd_value += "\n";

    return vcd_value;
}

bool SIGNAL::FSignal::equal_to(Signal const &other) const
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
