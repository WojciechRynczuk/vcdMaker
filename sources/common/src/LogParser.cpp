/// @file common/src/LogParser.cpp
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

#include "LogParser.h"
#include "VcdException.h"

PARSER::LogParser::LogParser(const std::string &rFilename,
                             SIGNAL::SignalDb * const pSignalDb,
                             SIGNAL::SourceRegistry &rSourceRegistry,
                             bool verboseMode) :
    m_pSignalDb(pSignalDb),
    m_FileName(rFilename),
    m_LogFile(m_FileName),
    m_SourceHandle(rSourceRegistry.Register(rFilename)),
    m_VerboseMode(verboseMode)
{
    if (!m_LogFile.is_open())
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::CANNOT_OPEN_FILE,
                                      "Opening file '" + m_FileName + "' failed, it either doesn't exist or is inaccessible.");
    }
}

void PARSER::LogParser::Attach(INSTRUMENT::Instrument &rInstrument)
{
    m_vpInstruments.push_back(&rInstrument);
}

void PARSER::LogParser::TerminateInstruments()
{
    for (auto instrument : m_vpInstruments)
    {
        instrument->Terminate();
    }
}

void PARSER::LogParser::Execute()
{
    Parse();
    TerminateInstruments();
}

