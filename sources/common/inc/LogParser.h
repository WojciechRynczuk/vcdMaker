/// @file common/inc/LogParser.h
///
/// The log parser interface class.
///
/// @par Full Description
/// The log parser interface class.
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

/// @defgroup Parser Parser
///
/// @brief The log parser group.
///
/// @par Full Description
/// The group provides means for reading input files.

#include <fstream>
#include <sstream>

#include "Instrument.h"

namespace PARSER
{
    /// The log parser base class.
    class LogParser
    {
        public:

            /// Returns the const reference to the signal database.
            const SIGNAL::SignalDb &GetSignalDb() const
            {
                return const_cast<SIGNAL::SignalDb &>((this)->GetSignalDb());
            }

            /// Returns the non-const reference to the signal database.
            SIGNAL::SignalDb &GetSignalDb()
            {
                return *m_pSignalDb;
            }

            /// Invokes the parser.
            void Execute();

            /// Attaches an instrument to the parser.
            ///
            /// @param rInstrument An instrument to be attached.
            virtual void Attach(INSTRUMENT::Instrument &rInstrument);

            /// Triggers the final instrument actions.
            virtual void TerminateInstruments();

        protected:

            /// The log parser constructor.
            ///
            /// This constructor shall be used by the inheriting classes.
            /// It opens the input log file and sets the verbose mode.
            ///
            /// @throws VcdError if the file cannot be open.
            /// @param rFilename The log file name.
            /// @param pSignalDb The signal databse. The container for parsed signals.
            /// @param rSourceRegistry Signal sources registry.
            /// @param verboseMode Value 'true' enables the verbose mode.
            LogParser(const std::string &rFilename,
                      SIGNAL::SignalDb * const pSignalDb,
                      SIGNAL::SourceRegistry &rSourceRegistry,
                      bool verboseMode);

            /// The log parser destructor.
            virtual ~LogParser() = 0;

            /// Triggers parsing the source.
            virtual void Parse() = 0;

            /// The signal database.
            SIGNAL::SignalDb * const m_pSignalDb;

            /// Instruments.
            std::vector<INSTRUMENT::Instrument *> m_vpInstruments;

            /// The input file name.
            std::string m_FileName;

            /// The input log file.
            std::ifstream m_LogFile;

            /// Source handle.
            SIGNAL::SourceRegistry::HandleT m_SourceHandle;

            /// Verbose mode.
            bool m_VerboseMode;
    };

    inline LogParser::~LogParser() = default;

}
