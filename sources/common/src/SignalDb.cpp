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

#include <memory>
#include <iostream>

#include "SignalDb.h"
#include "VcdError.h"
#include "SourceRegistry.h"

/// The invalid signal source exception.
class InvalidSignalSource : public EXCEPTION::VcdErrorGeneric
{
    public:
        /// The invalid signal source exception constructor.
        InvalidSignalSource() : VcdErrorGeneric(EXCEPTION::Error::INVALID_SIGNAL_SOURCE,
                                                    "Invalid signal source.")
        {
        }
};

/// The conflicting name exception.
class ConflictingNames : public EXCEPTION::VcdError
{
    public:

        /// The exception constructor.
        ///
        /// The conflicting name exception might occur while merging
        /// signals from different sources. The signals do not have to
        /// originate from different logs. These could be a log signal
        /// and a line couning signal (created for this log) having the
        /// same name.
        ///
        /// @param rSignalName The name of the conflicting signal.
        /// @param sourceA The first source of the signal.
        /// @param sourceB The second source of the signal.
        ConflictingNames(const std::string &rSignalName,
                         SIGNAL::SourceRegistry::HandleT sourceA,
                         SIGNAL::SourceRegistry::HandleT sourceB) :
            VcdError(EXCEPTION::Error::CONFLICTING_SIGNAL_NAMES),
            m_SignalName(rSignalName),
            m_SourceA(sourceA),
            m_SourceB(sourceB)
        {}

        /// Returns the conflicting signal's name.
        ///
        /// The method is used while providing the detailed information
        /// about the conflicting signal name.
        const std::string &GetName() const
        {
            return m_SignalName;
        }

        /// Returns the handle to the first source providing
        /// the conflicting signal.
        ///
        /// The method is used while providing the detailed information
        /// about the sources of the conflicting signal.
        SIGNAL::SourceRegistry::HandleT GetSourceA() const
        {
            return m_SourceA;
        }

        /// Returns the handle to the second source providing
        /// the conflicting signal.
        ///
        /// The method is used while providing the detailed information
        /// about the sources of the conflicting signal.
        SIGNAL::SourceRegistry::HandleT GetSourceB() const
        {
            return m_SourceB;
        }

    protected:
        const std::string GetInfo() const
        {
            return std::string("Conflicting signal names! " +
                               this->GetName() +
                               " in the sources: " +
                               SIGNAL::SourceRegistry::GetInstance().GetSourceName(this->GetSourceA()) +
                               " and " +
                               SIGNAL::SourceRegistry::GetInstance().GetSourceName(this->GetSourceB()) );
        }

    private:
        /// The duplicated signal's name.
        const std::string m_SignalName;

        /// The first source of the signal.
        const SIGNAL::SourceRegistry::HandleT m_SourceA;

        /// The second source of the signal.
        const SIGNAL::SourceRegistry::HandleT m_SourceB;
};

SIGNAL::SignalDb::SignalDb(const std::string &rTimeUnit) :
    m_TimeUnit(rTimeUnit)
{
}

SIGNAL::SignalDb::~SignalDb()
{
    for (const SIGNAL::Signal *signal : m_SignalSet)
    {
        delete signal;
    }
}

void SIGNAL::SignalDb::Add(const SIGNAL::Signal *pSignal)
{
    // A signal shall have a valid source once added to the database.
    if (pSignal->GetSource() == SourceRegistry::BAD_HANDLE)
    {
        throw InvalidSignalSource();
    }

    const auto it = m_AddedSignals.find(pSignal->GetName());

    // Is this a new signal to be logged?
    if (it == m_AddedSignals.end())
    {
        m_AddedSignals[pSignal->GetName()] = pSignal;
    }
    else
    {
        if ( (it->second->GetName() == pSignal->GetName()) &&
             (it->second->GetSource() != pSignal->GetSource()) )
        {
            // There are duplicated signal names in different sources.
            throw ConflictingNames(pSignal->GetName(),
                                   it->second->GetSource(),
                                   pSignal->GetSource());
        }
    }

    // Store the full signal data
    m_SignalSet.insert(pSignal);
}
