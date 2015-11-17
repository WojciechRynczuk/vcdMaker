/*!
  @file isignal.cpp

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

// SYSTEM INCLUDES
#include "stdafx.h"  // Precompiled header for the Windows platform
// Create the empty stdafx.h file for other platforms.

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "isignal.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The signal constructor.

  @par Full Description
  The constructor initializes the basic signal's properties like the name,
  the size, the timestamp and the value.

  @param name The name of the signal.
  @param size The size of the signal.
  @param timestamp The timestamp of the signal.
  @param value The value of the signal.
  @return None
*/
SIGNAL::ISignal::ISignal(const std::string &name, uint32_t size, uint64_t timestamp, uint64_t value) : Signal(name,
            size, "wire")
{
    m_Timestamp = timestamp;
    m_Value = value;
};

/*!
  The signal default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
SIGNAL::ISignal::~ISignal()
{
}

/*!
  Set the signal's value.

  @par Full Description
  It sets the signal's value and the timestamp indicating when the change
  occured.

  @param timestamp The timestamp of the signal.
  @param value The value of the signal.
  @return None
*/
void SIGNAL::ISignal::SetValue(uint64_t timestamp, uint64_t value)
{
    m_Timestamp = timestamp;
    m_Value = value;
};

/*!
  Get the signal's value.

  @par Full Description
  It reads the signal's value.

  @return The signal's value.
*/
uint64_t SIGNAL::ISignal::GetValue() const
{
    return m_Value;
};

/*!
  Get the signal's value in the VCD format.

  @par Full Description
  It returns the signal's value in the VCD format.

  @return String describing the signal's value.
*/
std::string SIGNAL::ISignal::Print() const
{
    std::string vcd_value = "b";

    for (int pos = m_Size - 1; pos >= 0; pos--)
    {
        if (m_Value & ((uint64_t)1 << pos))
        {
            vcd_value += "1";
        }
        else
        {
            vcd_value += "0";
        }
    }
    vcd_value += " ";
    vcd_value += m_Name;
    vcd_value += "\n";

    return vcd_value;
}

/*!
  Get the signal's footprint in the VCD format.

  @par Full Description
  It returns the signal's footprint in the VCD format.

  @return String describing the signal's footprint.
*/
std::string SIGNAL::ISignal::Footprint() const
{
    std::string vcd_value;
    vcd_value = "b";
    for (int pos = m_Size - 1; pos >= 0; pos--)
    {
        vcd_value += "x";
    }
    vcd_value += " ";
    vcd_value += m_Name;
    vcd_value += "\n";

    return vcd_value;
}

/*!
  Compare two integer signals.

  @par Full Description
  It compares two integer signals returning TRUE when they are equal.

  @return The comparison result.
*/
bool SIGNAL::ISignal::equal_to(Signal const &other) const
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

