/// @file vcdMerge/src/SignalSource.cpp
///
/// The signal source class.
///
/// @par Full Description
/// The class defines a signal source entity which can be merged
/// with other sources.
///
/// @ingroup Merge
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
/// IN THE SOFTWARE

#include <array>
#include <algorithm>
#include <memory>

#include "SignalSource.h"
#include "LineCounter.h"
#include "Utils.h"
#include "VcdException.h"
#include "XmlSignalFactory.h"
#include "DefaultSignalFactory.h"

const char MERGE::SignalSource::Formats::VCD_TEXT_FORMAT = 'T';
const char MERGE::SignalSource::Formats::USER_XML_FORMAT = 'U';

MERGE::SignalSource::SignalSource(const std::string &rDescription,
                                  SIGNAL::SourceRegistry &rSignalRegistry,
                                  bool verboseMode) :
    m_SourceDescription(rDescription),
    m_rSignalRegistry(rSignalRegistry),
    m_pSignalDb(),
    m_pSignalFactory(),
    m_SyncPoint(),
    m_TimeUnit(),
    m_Prefix(),
    m_LineCounter(),
    m_Filename(),
    m_VerboseMode(verboseMode)
{
    ParseParameters();
}

uint64_t MERGE::SignalSource::GetLeadingTime() const
{
    // Get the timestamp of the first signal in the set.
    const uint64_t t0 = (*(m_pSignalDb->GetSignals().cbegin()))->GetTimestamp();

    // The sync point value is out of bounds.
    if ((t0 > m_SyncPoint) && (m_SyncPoint > 0))
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::SYNCHRONIZATION_POINT_OUT_OF_BOUNDS,
                                      "Synchronization point value out of bounds: " + m_SyncPoint);
    }

    return (m_SyncPoint - t0);
}

void MERGE::SignalSource::Create()
{
    // Parse the log file.
    PARSER::TxtParser parser(m_Filename,
                             m_TimeUnit,
                             m_rSignalRegistry,
                             *m_pSignalFactory,
                             m_VerboseMode);

    // Line counter.
    std::unique_ptr<INSTRUMENT::LineCounter> lineCounter;

    if (!m_LineCounter.empty())
    {
        // Register the line counting instrument.
        lineCounter = std::make_unique<INSTRUMENT::LineCounter>(m_Filename,
                                                                m_LineCounter,
                                                                m_rSignalRegistry,
                                                                parser.GetSignalDb());
        parser.Attach(*lineCounter);
    }

    // Start parsing.
    parser.Execute();

    m_pSignalDb = parser.MoveSignalDb();
}

void MERGE::SignalSource::SetFormat(const std::string &rFormat)
{
    if (IsVcdFormat(rFormat))
    {
        m_pSignalFactory = std::make_unique<PARSER::DefaultSignalFactory>();
        return;
    }

    if (IsUserXmlFormat(rFormat))
    {
        // Extract the file name from the source description.
        // E.g. from 'U{file_name}' the 'file_name' will be extracted.
        // The first two characters must be skipped and the name's length does not include 'U{}'
        const std::string filename(rFormat, 2, rFormat.length() - 3);
        const std::ifstream infile(filename);

        if (!infile.good())
        {
            ThrowFileInaccessibleException(filename);
        }

        m_pSignalFactory = std::make_unique<PARSER::XmlSignalFactory>(filename);
        return;
    }

    throw EXCEPTION::VcdException(EXCEPTION::Error::INVALID_LOG_FILE_FORMAT,
                                  "Invalid log file format: " + rFormat);
}

void MERGE::SignalSource::SetSyncPoint(const std::string &rSyncPoint)
{
    try
    {
        m_SyncPoint = std::stoull(rSyncPoint);
    }
    catch (std::logic_error &)
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::INVALID_SYNCHRONIZATION_POINT_VALUE,
                                      "Invalid synchronization point value: " + rSyncPoint);
    }
}

void MERGE::SignalSource::SetTimeUnit(const std::string &rTimeUnit)
{
    if (UTILS::IsTimeUnitValid(rTimeUnit))
    {
        m_TimeUnit = rTimeUnit;
    }
    else
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::INVALID_TIME_UNIT,
                                      "Invalid time unit: " + rTimeUnit);
    }
}

void MERGE::SignalSource::SetPrefix(const std::string &rPrefix)
{
    if (!rPrefix.empty())
    {
        // The prefix shall contain the terminating '.' but the user
        // does not have to provide it.
        m_Prefix = rPrefix + ".";
    }
    else
    {
        m_Prefix = rPrefix;
    }
}

void MERGE::SignalSource::SetCounterName(const std::string &rLineCounter)
{
    m_LineCounter = rLineCounter;
}

void MERGE::SignalSource::SetFilename(const std::string &rFilename)
{
    const std::ifstream infile(rFilename);

    if (!infile.good())
    {
        ThrowFileInaccessibleException(rFilename);
    }
    m_Filename = rFilename;
}

void MERGE::SignalSource::ParseParameters()
{
    SourceParametersT params = GetSourceParameters();

    if (params.size() != Parameters::SOURCE_PARAM_N)
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::INVALID_NUMBER_OF_SOURCE_PARAMS,
                                      "Invalid number of source parameters: " + m_SourceDescription);
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

MERGE::SignalSource::SourceParametersT MERGE::SignalSource::GetSourceParameters() const
{
    return UTILS::Split(m_SourceDescription, SOURCE_PARAM_DELIM);
}

void MERGE::SignalSource::ThrowFileInaccessibleException(const std::string &rFilename) const
{
    throw EXCEPTION::VcdException(EXCEPTION::Error::CANNOT_OPEN_FILE,
                                  "Opening file '" +
                                  rFilename +
                                  "' failed, it either doesn't exist or is inaccessible.");
}

bool MERGE::SignalSource::IsVcdFormat(const std::string &rFormat) const
{
    if (rFormat == std::string(1,'T'))
    {
        return true;
    }
    return false;
}

bool MERGE::SignalSource::IsUserXmlFormat(const std::string &rFormat) const
{
    // It means there will be at list a single character in the brackets.
    // E.g. U{a}
    if (rFormat.length() > 3)
    {
        if ((rFormat[0] == Formats::USER_XML_FORMAT) &&
            (rFormat[1] == '{') &&
            (rFormat[rFormat.length() - 1] == '}'))
        {
            return true;
        }
    }
    return false;
}
