/// @file Source.cpp
///
/// The signal source class.
///
/// @par Full Description
/// The class defines a signal source entity which can be merged
/// with other sources.
///
/// @ingroup Merge
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

#include "Source.h"
#include "Utils.h"

MERGE::Source::Source(const std::string &description,
                      SIGNAL::SourceRegistry &signalRegistry,
                      bool verboseMode) :
    m_SourceDescription(description),
    m_rSignalRegistry(signalRegistry),
    m_VerboseMode(verboseMode)
{
    // Only configure the source.
    ParseParameters();
    m_Parser = NULL;
    m_pSignalDb = NULL;
    m_SyncPoint = 0;
}

void MERGE::Source::Create()
{
    // Currently only the txt parser is available.
    m_Parser = new PARSER::TxtParser(m_Filename,
                                     m_TimeUnit,
                                     m_rSignalRegistry,
                                     m_LineCounter,
                                     m_VerboseMode);

    m_pSignalDb = &m_Parser->GetSignalDb();
}

const SIGNAL::SignalDb *MERGE::Source::Get() const
{
    return m_pSignalDb;
}

const std::string& MERGE::Source::GetSourceDescription() const
{
	return m_SourceDescription;
}

void MERGE::Source::SetFormat(std::string &format)
{
    if (format != "T")
    {
        throw std::runtime_error("Invalid log file format: " + format);
    }
    format = format;
}

void MERGE::Source::SetSyncPoint(std::string &syncPoint)
{
    try
    {
        m_SyncPoint = std::stoll(syncPoint, 0, 10);
    }
    catch (...)
    {
        throw std::runtime_error("Invalid synchronization point value: " + syncPoint);
    }

}

void MERGE::Source::SetTimeUnit(std::string &timeUnit)
{
    /// @todo Check if correct.
    m_TimeUnit = timeUnit;
}

void MERGE::Source::SetPrefix(std::string &prefix)
{
    m_Prefix = prefix;
}

void MERGE::Source::SetCounterName(std::string &lineCounter)
{
    m_LineCounter = lineCounter;
}

void MERGE::Source::SetFilename(std::string &filename)
{
    m_Filename = filename;
}

void MERGE::Source::ParseParameters()
{
    SourceParametersT params = GetSourceParameters();

    if (params.size() != SOURCE_PARAM_N)
    {
        throw std::runtime_error("Invalid number of source parameters: " + m_SourceDescription);
    }
    else
    {
        SetFormat(params[LOG_FORMAT]);
        SetSyncPoint(params[SYNC_POINT]);
        SetTimeUnit(params[TIME_UNIT]);
        SetPrefix(params[PREFIX]);
        SetCounterName(params[LINE_COUNTER]);
        SetFilename(params[FILENAME]);
    }
}

MERGE::Source::SourceParametersT MERGE::Source::GetSourceParameters() const
{
	return UTILS::Split(m_SourceDescription, SOURCE_PARAM_DELIM);
}