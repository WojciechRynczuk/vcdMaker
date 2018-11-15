/// @file common/src/TxtParser.cpp
///
/// The text log parser.
///
/// @par Full Description
/// The text log parser. It expects the basic vcdMaker log syntax.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2018 vcdMaker team
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
#include "VcdException.h"

PARSER::TxtParser::TxtParser(const std::string &rFilename,
                             const std::string &rTimeBase,
                             SIGNAL::SourceRegistry &rSourceRegistry,
                             PARSER::SignalFactory &rSignalFactory,
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
    if (0 == std::uncaught_exceptions())
    {
        // Print the summary.
        std::cout << '\n' << "Parsed " << m_FileName << ": \n";
        std::cout << "Valid lines:   " << m_ValidLines << '\n';
        std::cout << "Invalid lines: " << m_InvalidLines << '\n';
    }
}

void PARSER::TxtParser::Parse()
{
    // Line counter.
    INSTRUMENT::Instrument::LineNumberT lineNumber = 1;

    // Process the log file.
    std::string input_line;
    while (std::getline(m_LogFile, input_line))
    {
        std::vector<const SIGNAL::Signal *> vpSignals =
            m_rSignalFactory.Create(input_line, lineNumber, m_SourceHandle);
        const SIGNAL::Signal *pSignal = nullptr;

        if (!vpSignals.empty())
        {
            while (!vpSignals.empty())
            {
                try
                {
                    pSignal = vpSignals.back();
                    vpSignals.pop_back();
                    m_pSignalDb->Add(pSignal);
                }
                catch (const EXCEPTION::VcdException &rException)
                {
                    delete pSignal;
                    while (!vpSignals.empty())
                    {
                        delete vpSignals.back();
                        vpSignals.pop_back();
                    }
                    if (EXCEPTION::Error::INCONSISTENT_SIGNAL == rException.GetId())
                    {
                        throw EXCEPTION::VcdException(rException.GetId(), std::string(rException.what()) +
                                                      " At line " + std::to_string(lineNumber) + ".");
                    }
                    else
                    {
                        throw rException;
                    }
                }

                for (auto instrument : m_vpInstruments)
                {
                    instrument->Notify(lineNumber, *pSignal);
                }
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

        ++lineNumber;
    }
}
