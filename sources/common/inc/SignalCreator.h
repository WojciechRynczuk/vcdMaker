/// @file common/inc/SignalCreator.h
///
/// The signal creator interface class.
///
/// @par Full Description
/// Every signal can be created differently. The class provides the
/// universal interface to create them.
///
/// @ingroup Parser
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

#pragma once

#include <regex>

#include "Signal.h"
#include "SignalDescriptorRegistry.h"
#include "Instrument.h"

namespace PARSER
{
    /// The class provides the interface to create the signal object.

    /// A base signal creator class.
    class SignalCreator
    {
        public:

            /// The signal creator constructor.
            ///
            /// The constructor initializes the regular expression member variable
            /// which will be matched against the log line.
			///
            /// @param rDescriptorRegistry The reference to the signal descriptors registry.
            /// @param rSignalRegEx The regular expression to be match against the log line.
            SignalCreator(SIGNAL::SignalDescriptorRegistry &rDescriptorRegistry,
                          const std::string &rSignalRegEx) :
                m_rSignalDescriptorRegistry(rDescriptorRegistry),
                m_SignalRegEx("^" + rSignalRegEx + "\r?$"),
                m_RegEx(rSignalRegEx)
            {
            }

            /// The destructor.
            virtual ~SignalCreator() = 0;

            /// Return the pointer to the newly created object or nullptr.
            ///
            /// It creates the integer signal object if the log line is valid and returns
            /// the pointer to the newly created object.
            /// If the log line is not matching the integer object specification
            /// then nullptr is returned.
            ///
            /// @param rLogLine The log line serving as the creation specification.
            /// @param lineNumber The log line number.
            /// @param sourceHandle Signal source handle.
            /// @return Signal pointer if the object has been created or nullptr.
            virtual const SIGNAL::Signal *Create(const std::string &rLogLine,
                                                 INSTRUMENT::Instrument::LineNumberT lineNumber,
                                                 SIGNAL::SourceRegistry::HandleT sourceHandle) const = 0;

            /// Returns the regex.
            const std::string &GetRegEx() const
            {
                return m_RegEx;
            }

        protected:

            /// The RegEx matching the signal description.
            const std::regex m_SignalRegEx;

            /// The original RegEx string.
            const std::string m_RegEx;

            /// The signal descriptors registry.
            SIGNAL::SignalDescriptorRegistry &m_rSignalDescriptorRegistry;
    };

    inline SignalCreator::~SignalCreator() = default;

}
