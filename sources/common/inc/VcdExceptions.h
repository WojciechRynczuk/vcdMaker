/// @file VcdExceptions.h
///
/// The exceptions that could occur in the system.
///
/// @par Full Description
/// The module defines the exceptions that could occur in the system.
///
/// @ingroup Exception
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

#pragma once

/// @defgroup Exception Exception
///
/// @brief The module defines the exceptions that could occur in the system.
///
/// @par Full Description
/// The module defines the exceptions that could occur in the system.

#include <stdexcept>

#include "SourceRegistry.h"

namespace EXCEPTION
{
    /// The conflicting name exception. Provides information allowing
    /// for returning meaningful details to the user.

    /// The conflicting name exception.
    class ConflictingNames : public std::runtime_error
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
            /// @param signalName The name of the conflicting signal.
            /// @param sourceA The first source of the signal.
            /// @param sourceB The second source of the signal.
            ConflictingNames(const std::string &signalName,
                             SIGNAL::SourceRegistry::HandleT sourceA,
                             SIGNAL::SourceRegistry::HandleT sourceB) :
                std::runtime_error("Conflicting signal names!"),
                m_SignalName(signalName),
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

        private:
            /// The duplicated signal's name.
            const std::string m_SignalName;

            /// The first source of the signal.
            const SIGNAL::SourceRegistry::HandleT m_SourceA;

            /// The second source of the signal.
            const SIGNAL::SourceRegistry::HandleT m_SourceB;
    };
}
