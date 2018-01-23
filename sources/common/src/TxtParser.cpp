/// @file common/src/TxtParser.cpp
///
/// The text log parser.
///
/// @par Full Description
/// The text log parser. It expects the basic vcdMaker log syntax.
///
/// @ingroup Parser
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

#include "TxtParser.h"
#include "SignalFactory.h"

PARSER::TxtParser::TxtParser(const std::string &rFilename,
                             const std::string &rTimeBase,
                             SIGNAL::SourceRegistry &rSourceRegistry,
                             const PARSER::SignalFactory &rSignalFactory,
                             bool verboseMode) :
    LogParser(rFilename, rTimeBase, rSourceRegistry, verboseMode),
    m_ValidLines(0),
    m_InvalidLines(0),
    m_SourceHandle(rSourceRegistry.Register(rFilename)),
    m_rSignalFactory(rSignalFactory)
{
}

PARSER::TxtParser::~TxtParser()
{
    // Print the summary.
    std::cout << '\n' << "Parsed " << m_FileName << ": \n";
    std::cout << "Valid lines:   " << m_ValidLines << '\n';
    std::cout << "Invalid lines: " << m_InvalidLines << '\n';
}

void PARSER::TxtParser::Parse()
{
    // Line counter.
    INSTRUMENT::Instrument::LineNumberT line_number = 1;

    // Process the log file.
    std::string input_line;
    while (std::getline(m_LogFile, input_line))
    {
        const SIGNAL::Signal *signal =
            m_rSignalFactory.Create(input_line, m_SourceHandle);

        if (signal)
        {
            m_pSignalDb->Add(signal);
            for (auto instrument : m_vpInstruments)
            {
                instrument->Notify(line_number, *signal);
            }
            ++m_ValidLines;
        }
        else
        {
            if (m_VerboseMode)
            {
                std::cout << "Invalid log line "
                          << m_ValidLines + m_InvalidLines
                          << ": "
                          << input_line
                          << '\n';
            }
            ++m_InvalidLines;
        }

        ++line_number;
    }
}
