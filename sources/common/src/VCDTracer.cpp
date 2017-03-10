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

#include <array>
#include <algorithm>

#include "VCDTracer.h"
#include "SignalStructureBuilder.h"
#include "TimeFrame.h"
#include "Version.h"

TRACER::VCDTracer::VCDTracer(const std::string &outputFile,
                             const SIGNAL::SignalDb &signalDb) :
    m_File(outputFile, std::ifstream::out | std::ifstream::binary),
    m_rSignalDb(signalDb)
{

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
    DumpLine("$version VCD Tracer \"Perun\" Release v." + std::string(VERSION::STRING));
    DumpLine("$end");
    DumpLine("$timescale 1 " + m_rSignalDb.GetTimeUnit());
    DumpLine("$end");
}

void TRACER::VCDTracer::GenerateSignalStructure()
{
    SignalStructureBuilder structure_builder(m_rSignalDb.GetSignalFootprint(), m_File);
    structure_builder.Dump();
}

void TRACER::VCDTracer::GenerateSignalDefaults()
{
    DumpLine("$dumpvars");
    for (const auto &signal : m_rSignalDb.GetSignalFootprint())
    {
        const std::string footprint = signal.second->Footprint();
        if (!footprint.empty())
        {
            DumpLine(signal.second->Footprint());
        }
    }
    DumpLine("$end");
}

void TRACER::VCDTracer::GenerateBody()
{
    TimeFrame frame(0, m_File);
    uint64_t previous_timestamp = 0;

    for (const SIGNAL::Signal *current_signal : m_rSignalDb.GetSignals())
    {
        const uint64_t current_timestamp = current_signal->GetTimestamp();

        if (current_timestamp != previous_timestamp)
        {
            frame.DumpAndClear();

            previous_timestamp = current_timestamp;
            frame.SetTime(current_timestamp);
        }

        frame.Add(current_signal);
    }

    frame.DumpAndClear();
}

