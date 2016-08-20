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

#include <iostream>

#include "LineCounter.h"

void PARSER::LineCounter::Update(uint64_t time, LineNumberT lineNumber)
{
    CounterT::iterator it;

    // Check if the source has been already registered.
    it = m_Counter.find(time);
    if (it != m_Counter.end())
    {
        // Update the high boundary.
        if (lineNumber > it->second[1])
        {
            it->second[1] = lineNumber;
        }

        // Update the low boundary.
        if (lineNumber < it->second[0])
        {
            it->second[0] = lineNumber;
        }
    }
    else
    {
        CounterValueT counter = { lineNumber, lineNumber };
        m_Counter[time] = counter;
        m_CounterIt = m_Counter.begin();
    }
}

bool PARSER::LineCounter::Get(LineCounterT &record)
{
    if (m_CounterIt != m_Counter.end())
    {
        record.counterNameLow = m_CounterName + ".Low";
        record.counterNameHigh = m_CounterName + ".High";
        record.time = m_CounterIt->first;
        record.low = m_CounterIt->second[0];
        record.high = m_CounterIt->second[1];

        ++m_CounterIt;
        return true;
    }
    return false;
}