/// @file LogParser.cpp
///
/// The log parser interface class.
///
/// @par Full Description
/// The log parser interface class.
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

#include "LogParser.h"

PARSER::LogParser::LogParser(std::string filename, bool verboseMode)
{
    m_FileName = filename;

    m_LogFile.open(filename, std::ifstream::out);
    if (false == m_LogFile.is_open())
    {
        std::ostringstream msg;
        msg << "Opening file '" << filename
            << "' failed, it either doesn't exist or is inaccessible.";
        throw std::runtime_error(msg.str());
    }
    m_VerboseMode = verboseMode;
}

PARSER::LogParser::~LogParser()
{
    m_LogFile.close();
}

SIGNAL::SignalDb *PARSER::LogParser::GetSignalDb()
{
    return m_pSignalDb;
}
