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
#include <array>
#include <algorithm>

#include "VCDTracer.h"
#include "SignalStructureBuilder.h"

TRACER::VCDTracer::VCDTracer(const std::string &outputFile, const std::string &timeUnit) :
    m_File(outputFile, std::ifstream::out | std::ifstream::binary),
    m_TimeUnit(timeUnit),
    m_AddedSignals(),
    m_SignalSet()
{
}

TRACER::VCDTracer::~VCDTracer()
{
    for (const SIGNAL::Signal *signal : m_SignalSet)
    {
        delete signal;
    }
}

void TRACER::VCDTracer::Log(const SIGNAL::Signal *signal)
{
    // Is this a new signal to be logged?
    if (m_AddedSignals.find(signal->GetName()) == m_AddedSignals.end())
    {
        m_AddedSignals[signal->GetName()] = signal;
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
    SignalStructureBuilder structure_builder(m_AddedSignals, m_File);
    structure_builder.Dump();
}

void TRACER::VCDTracer::GenerateSignalDefaults()
{
    DumpLine("$dumpvars");
    for (const auto &signal : m_AddedSignals)
    {
        DumpLine(signal.second->Footprint());
    }
    DumpLine("$end");
}

void TRACER::VCDTracer::GenerateBody()
{
    SIGNAL::UniqueSignalsCollectionT previous_signals;
    uint64_t previous_timestamp = 0;
    bool has_printed_first = false;

    for (const SIGNAL::Signal *current_signal : m_SignalSet)
    {
        const uint64_t current_timestamp = current_signal->GetTimestamp();

        const bool should_print_timestamp =
            (!has_printed_first || (current_timestamp != previous_timestamp));

        const std::string signal_name = current_signal->GetName();

        const auto previous_signal_it = previous_signals.find(signal_name);
        const bool previous_signal_exists = (previous_signal_it != previous_signals.end());

        if (!previous_signal_exists ||
            (*current_signal != *(previous_signal_it->second)))
        {
            if (should_print_timestamp)
            {
                DumpLine('#' + std::to_string(current_timestamp));
                previous_timestamp = current_timestamp;
                has_printed_first = true;
            }

            DumpLine(current_signal->Print());
            previous_signals[signal_name] = current_signal;
        }
    }
}

bool TRACER::VCDTracer::IsTimeUnitValid(const std::string &timeUnit)
{
    const std::array<std::string, 6> validTimeUnits = { "s", "ms", "us", "ns", "ps", "fs" };

    return (std::find(validTimeUnits.begin(), validTimeUnits.end(), timeUnit) != validTimeUnits.end());
}
