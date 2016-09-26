/// @file TxtParser.cpp
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

#include <iostream>

#include "TxtParser.h"
#include "SignalFactory.h"

const std::string PARSER::TxtParser::LINE_COUNTER_SUFFIX = "-LineCounter";

PARSER::TxtParser::TxtParser(const std::string &filename,
                             const std::string &timeBase,
                             SIGNAL::SourceRegistry &sourceRegistry,
                             const std::string &lineCounter,
                             bool verboseMode) :
    LogParser(filename, sourceRegistry, verboseMode),
    m_ValidLines(0),
    m_InvalidLines(0),
    m_SourceHandle(sourceRegistry.Register(filename)),
    m_LineCounter(lineCounter),
    m_LineCounterEnabled(!lineCounter.empty()),
    m_LineCounterSourceHandle(SIGNAL::SourceRegistry::BAD_HANDLE)
{
    m_pSignalDb = std::make_unique<SIGNAL::SignalDb>(timeBase);

    // Check if the line counter has been enabled
    if (m_LineCounterEnabled)
    {
        m_LineCounterSourceHandle = sourceRegistry.Register(m_FileName + LINE_COUNTER_SUFFIX);
    }

    // Process the log
    Parse();

    // Dump the line counting information.
    if (m_LineCounterEnabled)
    {
        m_LineCounter.RecordToSignalDb(*(m_pSignalDb.get()),
                                       m_LineCounterSourceHandle);
    }
}

PARSER::TxtParser::~TxtParser()
{
    // Print the summary.
    std::cout << '\n' << "\tParsed " << m_FileName << ": \n";
    std::cout << "\tValid lines:   " << m_ValidLines << '\n';
    std::cout << "\tInvalid lines: " << m_InvalidLines << '\n';
}

void PARSER::TxtParser::Parse()
{
    // Create the signal factory.
    const SignalFactory signal_factory;

    // Line counter.
    LineCounter::LineNumberT line_number = 1;

    // Process the log file.
    std::string input_line;
    while (std::getline(m_LogFile, input_line))
    {
        const SIGNAL::Signal *signal =
            signal_factory.Create(input_line, m_SourceHandle);

        if (signal)
        {
            m_pSignalDb->Add(signal);
            if (m_LineCounterEnabled)
            {
                m_LineCounter.Update(signal->GetTimestamp(), line_number);
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
