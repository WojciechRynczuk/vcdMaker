/// @file common/inc/SignalFactory.h
///
/// The signal factory class.
///
/// @par Full Description
/// The signal factory object creates the appropriate signal objects.
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

#include "SignalCreator.h"

namespace PARSER
{
    /// The class implements the factory method design pattern so as to handle
    /// building different types of signals.

    /// The signal factory base class.
    class SignalFactory
    {
        public:

            /// The signal factory constructor.
            SignalFactory();

            /// Creates the appropriate signal objects.
            ///
            /// Returns the pointer to the list of created signal objects.
            /// If emtpy no signal could be created.
            ///
            /// @param rLogLine One line from the log.
            /// @param lineNumber The log line number.
            /// @param rPrefix Signal prefix.
            /// @param sourceHandle Signal source handle.
            std::vector<const SIGNAL::Signal*> Create(const std::string &rLogLine,
                                                      INSTRUMENT::Instrument::LineNumberT lineNumber,
                                                      const std::string &rPrefix,
                                                      SIGNAL::SourceRegistry::HandleT sourceHandle) const;

        protected:

            /// The table of pointers to signal creators.
            std::vector<std::unique_ptr<SignalCreator>> m_vpSignalCreators;

            /// Factory specific signal prefix.
            const std::string m_Prefix;

        private:

            /// Returns log line details.
            ///
            /// Returns the string containing the log line information.
            /// @param sourceHandle The handle to the log source.
            /// @param lineNumber The log line number.
            /// @param logLine The log line.
            std::string GetLogLineInfo(SIGNAL::SourceRegistry::HandleT sourceHandle,
                                       size_t lineNumber,
                                       const std::string &logLine) const;
    };

}
