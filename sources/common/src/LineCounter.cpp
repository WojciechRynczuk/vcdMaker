/// @file LineCounter.cpp
///
/// The line counting class.
///
/// @par Full Description
/// The object of this class allows for keeping a record of the line
/// counting information. It is supposed to be used by the text parser.
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


#include "LineCounter.h"

#include "ISignal.h"

const std::string PARSER::LineCounter::DEFAULT_TOP_MODULE_NAME = "Top";
const std::string PARSER::LineCounter::HIGH_COUNTER_NAME = "High";
const std::string PARSER::LineCounter::LOW_COUNTER_NAME = "Low";

PARSER::LineCounter::LineCounter(const std::string &counterName) :
    m_CounterName(CreateCounterName(counterName)),
    m_CounterNameLow(m_CounterName + SIGNAL::Signal::SIGNAL_NAME_DELIM + LOW_COUNTER_NAME),
    m_CounterNameHigh(m_CounterName + SIGNAL::Signal::SIGNAL_NAME_DELIM + HIGH_COUNTER_NAME)
{
}

void PARSER::LineCounter::Update(uint64_t timestamp, LineNumberT lineNumber)
{
    // Check if the source has been already registered.
    const CounterSignalT::iterator it = m_Counter.find(timestamp);

    if (it != m_Counter.end())
    {
        // Update the high boundary.
        if (lineNumber > it->second.m_LineHigh)
        {
            it->second.m_LineHigh = lineNumber;
        }

        // Update the low boundary.
        if (lineNumber < it->second.m_LineLow)
        {
            it->second.m_LineLow = lineNumber;
        }
    }
    else
    {
        // The initializer list is not supported by VS.
        // m_Counter[timestamp] = { lineNumber, lineNumber };
        m_Counter[timestamp].m_LineLow = lineNumber;
        m_Counter[timestamp].m_LineHigh = lineNumber;
    }
}

void PARSER::LineCounter::RecordToSignalDb(SIGNAL::SignalDb &signalDb,
                                           SIGNAL::SourceRegistry::HandleT sourceHandle)
{
    for (const auto &counterRecord : m_Counter)
    {
        SIGNAL::ISignal *low_counter =
            new SIGNAL::ISignal(m_CounterNameLow,
                                COUNTER_SIGNAL_SIZE,
                                counterRecord.first,
                                counterRecord.second.m_LineLow,
                                sourceHandle);
        signalDb.Add(low_counter);

        SIGNAL::ISignal *high_counter =
            new SIGNAL::ISignal(m_CounterNameHigh,
                                COUNTER_SIGNAL_SIZE,
                                counterRecord.first,
                                counterRecord.second.m_LineHigh,
                                sourceHandle);
        signalDb.Add(high_counter);
    }
}

std::string PARSER::LineCounter::CreateCounterName(const std::string &desiredName)
{
    const std::string::size_type delim_position =
        desiredName.find(SIGNAL::Signal::SIGNAL_NAME_DELIM);

    if (delim_position != std::string::npos)
    {
        if (delim_position == 0)
        {
            return (DEFAULT_TOP_MODULE_NAME + desiredName);
        }
        else
        {
            return desiredName;
        }
    }
    else
    {
        return (DEFAULT_TOP_MODULE_NAME + SIGNAL::Signal::SIGNAL_NAME_DELIM + desiredName);
    }
}
