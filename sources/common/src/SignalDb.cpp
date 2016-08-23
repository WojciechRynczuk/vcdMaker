/// @file SignalDb.cpp
///
/// Signal database class.
///
/// @par Full Description
/// The class is a database of signals. It shall group signals from a single
/// source.
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

#include "SignalDb.h"
#include "vcdExceptions.h"

SIGNAL::SignalDb::SignalDb(const std::string &timeUnit) :
    m_TimeUnit(timeUnit)
{
}

SIGNAL::SignalDb::~SignalDb()
{
    for (const SIGNAL::Signal *signal : m_SignalSet)
    {
        delete signal;
    }
}

void SIGNAL::SignalDb::Add(const SIGNAL::Signal *signal)
{
    // A signal shall have a valid source once added to the database.
    if (0 == signal->GetSource())
    {
        throw std::logic_error("Invalid signal source.");
    }

    const auto it = m_AddedSignals.find(signal->GetName());

    // Is this a new signal to be logged?
    if (it == m_AddedSignals.end())
    {
        m_AddedSignals[signal->GetName()] = signal;
    }
    else
    {
        if ( (it->second->GetName() == signal->GetName()) &&
                (it->second->GetSource() != signal->GetSource()) )
        {
            // There are duplicated signal names in different sources.
            throw EXCEPTION::ConflictingNames(signal->GetName(), it->second->GetSource(), signal->GetSource());
        }
    }

    // Store the full signal data
    m_SignalSet.insert(signal);
}
