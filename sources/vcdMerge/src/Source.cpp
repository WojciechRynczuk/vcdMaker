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
/// IN THE SOFTWARE

#include <algorithm>

#include "Source.h"
#include "Utils.h"

MERGE::Source::Source(const std::string &description,
                      SIGNAL::SourceRegistry &signalRegistry,
                      bool verboseMode) :
    m_SourceDescription(description),
    m_rSignalRegistry(signalRegistry),
    m_pSignalDb(),
    m_SyncPoint(),
    m_TimeUnit(),
    m_Prefix(),
    m_LineCounter(),
    m_Filename(),
    m_VerboseMode(verboseMode)
{
    ParseParameters();
}

const uint64_t MERGE::Source::GetSync() const
{
    return m_SyncPoint;
}

const uint64_t MERGE::Source::GetSpan(const std::string tunit) const
{
    /// @todo Ignored tunit.

    // Get the timestamp of the first signal in the set.
    uint64_t t0 = (*(m_pSignalDb->GetSignals().begin()))->GetTimestamp();

    // The sync point value is out of bounds.
    if (t0 > m_SyncPoint)
    {
        throw std::runtime_error("Synchronization point value out of bounds: " + m_SyncPoint);
    }

    return (m_SyncPoint - t0);
}

void MERGE::Source::Create()
{
    // Parse the log file.
    PARSER::TxtParser parser(m_Filename,
                             m_TimeUnit,
                             m_rSignalRegistry,
                             m_LineCounter,
                             m_VerboseMode);

    m_pSignalDb = parser.MoveSignalDb();
}

void MERGE::Source::SetFormat(const std::string &format)
{
    if (format != "T")
    {
        throw std::runtime_error("Invalid log file format: " + format);
    }
}

void MERGE::Source::SetSyncPoint(const std::string &syncPoint)
{
    try
    {
        m_SyncPoint = std::stoll(syncPoint);
    }
    catch (...)
    {
        throw std::runtime_error("Invalid synchronization point value: " + syncPoint);
    }
}

void MERGE::Source::SetTimeUnit(const std::string &timeUnit)
{
    std::vector<std::string> tunits = { "s", "ms", "us", "ns", "ps", "fs" };
    if (std::any_of(tunits.begin(), tunits.end(), [&](std::string& element) {return (element == timeUnit);} ))
    {
        m_TimeUnit = timeUnit;
    }
    else
    {
        throw std::runtime_error("Invalid time unit: " + timeUnit);
    }

}

void MERGE::Source::SetPrefix(const std::string &prefix)
{
    m_Prefix = prefix;
}

void MERGE::Source::SetCounterName(const std::string &lineCounter)
{
    m_LineCounter = lineCounter;
}

void MERGE::Source::SetFilename(const std::string &filename)
{
    std::ifstream infile(filename);

    if (infile.good())
    {
        m_Filename = filename;
    }
    else
    {
        throw std::runtime_error("No such file: " + filename);
    }
}

void MERGE::Source::ParseParameters()
{
    SourceParametersT params = GetSourceParameters();

    if (params.size() != Parameters::SOURCE_PARAM_N)
    {
        throw std::runtime_error("Invalid number of source parameters: " + m_SourceDescription);
    }
    else
    {
        SetFormat(params[Parameters::LOG_FORMAT]);
        SetSyncPoint(params[Parameters::SYNC_POINT]);
        SetTimeUnit(params[Parameters::TIME_UNIT]);
        SetPrefix(params[Parameters::PREFIX]);
        SetCounterName(params[Parameters::LINE_COUNTER]);
        SetFilename(params[Parameters::FILENAME]);
    }
}

MERGE::Source::SourceParametersT MERGE::Source::GetSourceParameters() const
{
    return UTILS::Split(m_SourceDescription, SOURCE_PARAM_DELIM);
}
