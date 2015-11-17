/*!
  @file signal.cpp

  The base VCD signal class.

  @par Full Description
  The base signal class contains the common signal properties and
  methods.

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
#include "signal.h"

// FORWARD REFERENCES
// (none)

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The signal constructor to be used by inheriting classes.

  @par Full Description
  The constructor initializes the basic signal's properties like the name,
  the size and the type.

  @param name The name of the signal.
  @param size The size of the signal.
  @param type The type of the signal.
  @return None
*/
SIGNAL::Signal::Signal(const std::string &name, uint32_t size, const std::string &type) : m_Name(name), m_Size(size),
    m_Timestamp(0), m_Type(type)
{
};

/*!
  The signal default constructor.

  @par Full Description
  The default constructor to be used by the multiset container.

  @return None
*/
SIGNAL::Signal::Signal() : m_Name(""), m_Size(0), m_Timestamp(0), m_Type("")
{
};

/*!
  The signal default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
SIGNAL::Signal::~Signal()
{
};

/*!
  Get the signal's name.

  @par Full Description
  It returns a string containing the signal's name.

  @return The name of the signal.
*/
std::string  SIGNAL::Signal::GetName() const
{
    return m_Name;
};

/*!
  Get the signal's size.

  @par Full Description
  It returns the size of the signal.

  @return The size of the signal.
*/
uint32_t SIGNAL::Signal::GetSize() const
{
    return m_Size;
};

/*!
  Get the signal's timestamp.

  @par Full Description
  It returns the timestamp of the signal.

  @return The timestamp of the signal.
*/
uint64_t SIGNAL::Signal::GetTimestamp() const
{
    return m_Timestamp;
};

/*!
  Get the signal's type.

  @par Full Description
  It returns the type of the signal.

  @return The type of the signal.
*/
std::string SIGNAL::Signal::GetType() const
{
    return m_Type;
};

/*!
  Get the signal's value in the string format.

  @par Full Description
  It returns the signal's value in the VCD string format.

  @return The string representing the signal's value.
*/
std::string SIGNAL::Signal::Print() const
{
    return "";
};

/*!
  Get the signal's footprint in the string format.

  @par Full Description
  It returns the signal's footprint in the VCD string format.

  @return The string representing the signal's footprint.
*/
std::string SIGNAL::Signal::Footprint() const
{
    return "";
};

/*!
  The overloaded () operator.

  @par Full Description
  The () operator is overloaded so as the multiset container could use
  pointers to the Signal class.

  @param signal1 The first signal to compare.
  @param signal2 The second signal to compare.
  @return The result of the comparison operation.
*/
bool  SIGNAL::Signal::operator() (const Signal *signal1, const Signal *signal2) const
{
    return signal1->m_Timestamp < signal2->m_Timestamp;
};

//***************************************************************************
// PROTECTED METHODS
//***************************************************************************
/*!
  The virtual equal_to() method for comparing two signals.

  @par Full Description
  This method must be implemented by the inheriting classes so as signals
  of the same type could be effectively compared. It is used by the
  overloadad '==' and '!=' operators.

  @param other A signal to compare to.
  @return The result of the comparison operation.
*/
bool SIGNAL::Signal::equal_to(Signal const &other) const
{
    return 0;
}

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************
/*!
  The overloaded '==' operator.

  @par Full Description
  It is used to compare two signals.

  @param lsignal The first signal to compare.
  @param rsignal The second signal to compare.
  @return The result of the comparison operation.
*/
bool SIGNAL::operator == (const Signal &lsignal, const Signal &rsignal)
{
    return lsignal.equal_to(rsignal);
};

/*!
  The overloaded '!=' operator.

  @par Full Description
  It is not currently used. It has been provided as a complementary
  part to '=='.

  @param lsignal The first signal to compare.
  @param rsignal The second signal to compare.
  @return The result of the comparison operation.
*/
bool SIGNAL::operator != (const Signal &lsignal, const Signal &rsignal)
{
    return !lsignal.equal_to(rsignal);
};

