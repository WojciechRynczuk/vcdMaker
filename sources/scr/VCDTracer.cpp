/*!
  @file vcdtracer.cpp

  The VCD generation module.

  @par Full Description
  The class allows for collecting signals
  and storing the data in the VCD format.

  @if REVISION_HISTORY_INCLUDED
  @par Edit History
  @li [0]    wojciech.rynczuk@wp.pl    16-DEC-2014    Initial file revision.
  @endif

  @ingroup Tracer

  @par Copyright (c) MMXV Wojciech Rynczuk

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

// SYSTEM INCLUDES
#include "stdafx.h"     // Precompiled header for the Windows platform
// Create the empty stdafx.h file for other platforms.
#include <iostream>     // Streams

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "VCDTracer.h"

// FORWARD REFERENCES
// (none)

// MACROS
//! Simplify outputting the VCD lines
#define VCD_LINE(x) m_File << x << std::endl

//***************************************************************************
// PUBLIC METHODS
//***************************************************************************

/*!
  The VCD tracer constructor.

  @par Full Description
  The constructor initializes the output VCD file and sets the time unit.

  @param outputFile The name of the output VCD file.
  @param tunit The time base.
  @return None
*/
TRACER::VCDTracer::VCDTracer(std::string const &outputFile, TimeUnit::_TimeUnit tunit)
{
    // Just open the output file
    m_File.open(outputFile.c_str(), std::ifstream::out);

    // Set the time unit
    switch (tunit)
    {
        case TimeUnit::s:
            m_TimeUnit = "s";
            break;
        case TimeUnit::ms:
            m_TimeUnit = "ms";
            break;
        case TimeUnit::us:
            m_TimeUnit = "us";
            break;
        case TimeUnit::ns:
            m_TimeUnit = "ns";
            break;
        case TimeUnit::ps:
            m_TimeUnit = "ps";
            break;
        case TimeUnit::fs:
            m_TimeUnit = "fs";
            break;
        default:
            m_TimeUnit = "s";
            break;
    }
}

/*!
  Log a signal.

  @par Full Description
  Adds the traced signal to the collection.

  @param signal A signal.
  @return None
*/
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

/*!
  Create the content of the VCD file.

  @par Full Description
  It creates the header of the VCF file as well as the body
  listing all signal changes.

  @return None
*/
void TRACER::VCDTracer::Dump()
{
    GenerateHeader();
    GenerateBody();
}

/*!
  The VCD tracer default destructor.

  @par Full Description
  The default destructor.

  @return None
*/
TRACER::VCDTracer::~VCDTracer()
{
}

//***************************************************************************
// PRIVATE METHODS
//***************************************************************************

/*!
  Generate the header of the VCD file.

  @par Full Description
  Generates the header of the VCD file.

  @return None
*/
void TRACER::VCDTracer::GenerateHeader()
{
    // So as to make things simpler the header has been split into three
    // different sections.
    GenerateBasicInformation();
    GenerateSignalStructure();
    GenerateSignalDefaults();
}

/*!
  Generate the basic VCD header information.

  @par Full Description
  Generates the basic header information. Currently, the creation date and
  time are constant. Only the time unit is adjustable.

  @return None
*/
void TRACER::VCDTracer::GenerateBasicInformation()
{
    VCD_LINE("$date December 8, 2014 14:15:00");
    VCD_LINE("$end");
    VCD_LINE("$version VCD Tracer \"Matylda\" Release v.1.0.1");
    VCD_LINE("$end");
    VCD_LINE("$timescale 1 " + m_TimeUnit);
    VCD_LINE("$end");
}

/*!
  Generate the VCD signals structure.

  @par Full Description
  Generates the structure of the traced signals. Although indents are
  not necessary they have been intruduced to improve the readability
  of the VCD file.

  @return None
*/
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
        std::vector<std::string> signals = SplitSignal(it->second->GetName(), '.');

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
                        VCD_LINE(vline);
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
                    VCD_LINE(vline);
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
                VCD_LINE(vline);
            }
        }

        while ((signals.size() - 1) != level)
        {
            vline = indents.back() + "$upscope $end";
            VCD_LINE(vline);
            structure.pop_back();
            indents.pop_back();
            level--;
        }

        // Add the signal
        vline = indents.back() + "\t" + "$var " + it->second->GetType() + " " + \
                std::to_string(it->second->GetSize()) + " " + it->second->GetName() + \
                " " + signals[pos] + " $end";
        VCD_LINE(vline);
    }

    while (0 != level)
    {
        vline = indents.back() + "$upscope $end";
        VCD_LINE(vline);
        structure.pop_back();
        indents.pop_back();
        level--;
    }
}

/*!
  Generate the VCD signals default values.

  @par Full Description
  Generates the default values of the traced signals.

  @return None
*/
void TRACER::VCDTracer::GenerateSignalDefaults()
{
    VCD_LINE("$dumpvars");
    for (SignalStateT::iterator it = m_SignalState.begin(); it != m_SignalState.end(); ++it)
    {
        m_File << it->second->Footprint();
    }
    VCD_LINE("$end");

    // Refresh the current state of signals
    m_SignalState.clear();
}

/*!
  Generate the VCD body.

  @par Full Description
  Generates the body of the VCD file. It dumps signals values in the time-ordered
  fashion.

  @return None
*/
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

/*!
  Dumps the signals changes for the given timestamp.

  @par Full Description
  Dumps the signals changes for the given timestamp.

  @param timestamp The timestamp for which the dump is made.
  @return None
*/
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
                    m_File << "#" << timestamp << std::endl;
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
                m_File << "#" << timestamp << std::endl;
                changes_present = 1;
            }
            m_File << (*iter).second->Print();
            m_SignalState.erase(iter++);
        }
    }
}

/*!
  Splits the signal name into the module, the sub-module(s) and the signal name.

  @par Full Description
  Splits the signal name. The module, the sub-module and the signal name must
  be separated by a single '.'.

  @param name The full signal name.
  @param delim The delimiter.
  @return The vector containing the separated strings.
*/
std::vector<std::string> TRACER::VCDTracer::SplitSignal(std::string name, const char delim)
{
    std::vector<std::string> tokenized_string;
    std::string word;

    for (std::string::const_iterator i = name.begin(); i < name.end(); ++i)
    {
        if (*i != delim)
        {
            word += *i;
        }
        else
        {
            tokenized_string.push_back(word);
            word = "";
        }
    }
    if (word.size() != 0)
    {
        tokenized_string.push_back(word);
    }
    return tokenized_string;
}

