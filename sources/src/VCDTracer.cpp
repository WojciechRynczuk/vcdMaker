/// @file VCDTracer.h
///
/// The VCD generation module.
///
/// @par Full Description
/// The class provides means for collecting signals
/// and storing the data in the VCD format.
///
/// @ingroup Tracer
///
/// @par Copyright (c) 2016 Wojciech Rynczuk
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
#include <array>
#include <algorithm>

#include "VCDTracer.h"

TRACER::VCDTracer::VCDTracer(const std::string &outputFile, const std::string &timeUnit) :
    m_File(outputFile, std::ifstream::out | std::ifstream::binary),
    m_TimeUnit(timeUnit),
    m_SignalState(),
    m_LastSignalState(),
    m_SignalSet()
{
}

void TRACER::VCDTracer::Log(const SIGNAL::Signal *signal)
{
    // Is this a new signal to be logged?
    if (m_SignalState.find(signal->GetName()) == m_SignalState.end())
    {
        m_SignalState[signal->GetName()] = signal;
    }

    // Store the full signal data
    m_SignalSet.insert(signal);
}

void TRACER::VCDTracer::Dump()
{
    GenerateHeader();
    GenerateBody();
}

void TRACER::VCDTracer::GenerateHeader()
{
    // So as to make things simpler the header has been split into three
    // different sections.
    GenerateBasicInformation();
    GenerateSignalStructure();
    GenerateSignalDefaults();
}

void TRACER::VCDTracer::GenerateBasicInformation()
{
    DumpLine("$date December 8, 2014 14:15:00");
    DumpLine("$end");
    DumpLine("$version VCD Tracer \"Matylda\" Release v.1.0.1");
    DumpLine("$end");
    DumpLine("$timescale 1 " + m_TimeUnit);
    DumpLine("$end");
}

void TRACER::VCDTracer::GenerateSignalStructure()
{
    std::vector<std::string> structure; // Tokenized signal
    std::vector<std::string> indents;   // Indents stack
    std::string vline = ""; // VCD line
    std::string indent = ""; // Indent tabs
    uint32_t    level = 0;  // Indent level

    // Iterate through the all collected signals
    for (SignalStateT::iterator it = m_SignalState.begin(); it != m_SignalState.end(); ++it)
    {
        // Split the signal name into the path elements
        SIGNAL::Signal::SignalNameFieldsT signals = it->second->GetNameFields();

        uint32_t pos = 0;
        // Create the current structure
        for (pos = 0; pos < signals.size() - 1; pos++)
        {
            if (pos < level)
            {
                if (signals[pos] != structure[pos])
                {
                    // Roll down the existing structure and create the new one
                    while (pos != level)
                    {
                        vline = indents.back() + "$upscope $end";
                        DumpLine(vline);
                        structure.pop_back();
                        indents.pop_back();
                        level--;
                    }

                    // Add new element to the structure
                    if (indents.size() > 0)
                    {
                        indent = indents.back() + "\t";
                    }
                    vline = indent + "$scope module " + signals[pos] + " $end";
                    structure.push_back(signals[pos]);
                    indents.push_back(indent);
                    level++;
                    DumpLine(vline);
                }
            }
            else
            {
                // Add new element to the structure
                if (indents.size() > 0 )
                {
                    indent = indents.back() + "\t";
                }
                vline = indent + "$scope module " + signals[pos] + " $end";
                structure.push_back(signals[pos]);
                indents.push_back(indent);
                level++;
                DumpLine(vline);
            }
        }

        while ((signals.size() - 1) != level)
        {
            vline = indents.back() + "$upscope $end";
            DumpLine(vline);
            structure.pop_back();
            indents.pop_back();
            level--;
        }

        // Add the signal
        vline = indents.back() + "\t" + "$var " + it->second->GetType() + " " + \
                std::to_string(it->second->GetSize()) + " " + it->second->GetName() + \
                " " + signals[pos] + " $end";
        DumpLine(vline);
    }

    while (0 != level)
    {
        vline = indents.back() + "$upscope $end";
        DumpLine(vline);
        structure.pop_back();
        indents.pop_back();
        level--;
    }
}

void TRACER::VCDTracer::GenerateSignalDefaults()
{
    DumpLine("$dumpvars");
    for (SignalStateT::iterator it = m_SignalState.begin(); it != m_SignalState.end(); ++it)
    {
        m_File << it->second->Footprint();
    }
    DumpLine("$end");

    // Refresh the current state of signals
    m_SignalState.clear();
}

void TRACER::VCDTracer::GenerateBody()
{
    SignalCollectionT::const_iterator iter;
    uint64_t timestamp = 0;
    uint64_t timestamp_prev = 0;
    bool     initialised = false;

    iter = m_SignalSet.begin();

    // Iterate through all of the signals
    while (iter != m_SignalSet.end())
    {
        if (true == initialised)
        {
            timestamp = (*iter)->GetTimestamp();
            if (timestamp != timestamp_prev)
            {
                // Dump signals changes for the given timestamp
                DumpSignals(timestamp_prev);
                timestamp_prev = timestamp;
            }
        }
        else
        {
            timestamp_prev = (*iter)->GetTimestamp();
            initialised = true;
        }
        // Add the signal to the current signal collection
        // It will be dumped with the next DumpSignals() call
        m_SignalState[(*iter)->GetName()] = *iter;
        m_SignalSet.erase(iter++);
    }

    // Dump the remaining signals
    DumpSignals(timestamp);

    // Release the memory
    SignalStateT::iterator inner_iterator = m_SignalState.begin();
    SignalStateT::iterator outer_iterator = m_LastSignalState.begin();
    while (outer_iterator != m_LastSignalState.end())
    {
        if ((inner_iterator = m_SignalState.find((*outer_iterator).second->GetName().c_str())) != m_SignalState.end())
        {
            m_SignalState.erase(inner_iterator);
        }
        delete m_LastSignalState[(*outer_iterator).second->GetName().c_str()];
        m_LastSignalState.erase(outer_iterator++);
    }

    // Close the VCD file
    m_File.close();
}

void TRACER::VCDTracer::DumpSignals(uint64_t timestamp)
{
    uint32_t changes_present = 0;

    // Dump only signals which changed
    SignalStateT::iterator iter = m_SignalState.begin();
    while (iter != m_SignalState.end())
    {
        if (m_LastSignalState.find((*iter).second->GetName().c_str()) != m_LastSignalState.end())
        {
            if (*m_LastSignalState.find((*iter).second->GetName())->second != *m_SignalState.find((
                        *iter).second->GetName())->second)
            {
                //The signal value is no longer needed and the memory can be released
                delete m_LastSignalState[(*iter).second->GetName().c_str()];
                m_LastSignalState[(*iter).second->GetName().c_str()] = (*iter).second;
                if (0 == changes_present)
                {
                    m_File << "#" << timestamp << '\n';
                    changes_present = 1;
                }
                m_File << (*iter).second->Print();
                iter++;
            }
            else
            {
                if (m_LastSignalState.find((*iter).second->GetName())->second != m_SignalState.find((*iter).second->GetName())->second)
                {
                    //The signal value is no longer needed and the memory can be released
                    delete m_SignalState[(*iter).second->GetName().c_str()];
                    m_SignalState.erase(iter++);
                }
                else
                {
                    iter++;
                }
            }
        }
        else
        {
            m_LastSignalState[(*iter).second->GetName().c_str()] = (*iter).second;
            if (0 == changes_present)
            {
                m_File << "#" << timestamp << '\n';
                changes_present = 1;
            }
            m_File << (*iter).second->Print();
            m_SignalState.erase(iter++);
        }
    }
}

bool TRACER::VCDTracer::IsTimeUnitValid(const std::string &timeUnit)
{
    const std::array<std::string, 6> validTimeUnits = { "s", "ms", "us", "ns", "ps", "fs" };

    return (std::find(validTimeUnits.begin(), validTimeUnits.end(), timeUnit) != validTimeUnits.end());
}
