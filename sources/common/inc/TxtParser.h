/// @file TxtParser.h
///
/// The text log parser.
///
/// @par Full Description
/// The text log parser. It expects the basic vcdMaker log syntax.
///
/// @ingroup Parser
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

#include <iostream>

#include "LogParser.h"
#include "SignalFactory.h"

namespace PARSER
{
    /// The text log parser class.
    class TxtParser : public LogParser
    {
        public:

            /// The text log parser constructor.
            ///
            /// This constructor is used by the vcdMaker app.
            /// It opens the input log file, sets the timebase and the verbose mode.
            ///
            /// @param filename The name of the log file to be open.
            /// @param tbase The time base used in the log.
            /// @param verboseMode Value 'true' enables the verbose mode.
            TxtParser(std::string filename, std::string tbase, bool verboseMode) : LogParser(filename, verboseMode)
            {
                m_pSignalDb = new SIGNAL::SignalDb(tbase);
                m_ValidLines = 0;
                m_InvalidLines = 0;

                // Process the log
                Parse();
            }

            /// The destructor.
            ~TxtParser()
            {
                // Print the summary.
                std::cout << '\n' << "Parsed " << m_FileName << ": \n";
                std::cout << "\t Valid lines:   " << m_ValidLines << '\n';
                std::cout << "\t Invalid lines: " << m_InvalidLines << '\n';

                delete m_pSignalDb;
            };

        private:

            /// Parses the input file.
            void Parse()
            {
                // Create the signal factory.
                const SignalFactory signal_factory;

                // Process the log file.
                std::string input_line;
                while (std::getline(m_LogFile, input_line))
                {
                    SIGNAL::Signal *signal = signal_factory.Create(input_line);
                    if (signal)
                    {
                        m_pSignalDb->Add(signal);
                        m_ValidLines++;
                    }
                    else
                    {
                        if (m_VerboseMode)
                        {
                            std::cout << "Invalid log line " << m_ValidLines + m_InvalidLines << ": " << input_line << '\n';
                        }
                        ++m_InvalidLines;
                    }
                }
            }

            /// The number of valid lines.
            uint64_t m_ValidLines;

            /// The number of invalid lines.
            uint64_t m_InvalidLines;
    };

}
