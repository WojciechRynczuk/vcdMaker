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

    // Parse the log file.
    PARSER::TxtParser parser(m_Filename,
                             m_TimeUnit,
                             m_rSignalRegistry,
                             m_LineCounter,
                             m_VerboseMode);

    m_pSignalDb = parser.MoveSignalDb();
}

void MERGE::Source::SetFormat(std::string &)
{
    /// @todo Implement it. Skip for now. Just check for 'T'.
}

void MERGE::Source::SetSyncPoint(std::string &syncPoint)
{
    /// @todo Handle the exception.
    m_SyncPoint = std::stoll(syncPoint, 0, 10);
}

void MERGE::Source::SetTimeUnit(std::string &timeUnit)
{
    /// @todo Check if correct.
    m_TimeUnit = timeUnit;
}

void MERGE::Source::SetPrefix(std::string &prefix)
{
    /// @todo Check if correct.
    m_Prefix = prefix;
}

void MERGE::Source::SetCounterName(std::string &lineCounter)
{
    /// @todo Check if correct.
    m_LineCounter = lineCounter;
}

void MERGE::Source::SetFilename(std::string &filename)
{
    m_Filename = filename;
}

void MERGE::Source::ParseParameters()
{
    SourceParametersT params = GetSourceParameters();
    /// @todo Replace the magic number.
    if (params.size() != 6)
    {
        /// @todo Throw the exception.
    }
    else
    {
        SetFormat(params[0]);
        SetSyncPoint(params[1]);
        SetTimeUnit(params[2]);
        SetPrefix(params[3]);
        SetCounterName(params[4]);
        SetFilename(params[5]);
    }
}

/// @todo Move the method to utils (and create the utils).
///       There's a similar function in the Signal.cpp
MERGE::Source::SourceParametersT MERGE::Source::GetSourceParameters() const
{
    SourceParametersT source_fields;
    std::stringstream name_stream(m_SourceDescription);
    std::string name_field;

    while (std::getline(name_stream, name_field, SOURCE_PARAM_DELIM))
    {
        source_fields.push_back(name_field);
    }

    return source_fields;
}
