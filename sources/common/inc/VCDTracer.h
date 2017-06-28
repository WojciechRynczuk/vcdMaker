/// @file common/inc/VCDTracer.h
///
/// The VCD generation module.
///
/// @par Full Description
/// The class provides means for creating the output VCD files.
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

#pragma once

/// @defgroup Tracer Tracer
///
/// @brief The VCD tracer.
///
/// @par Full Description
/// The Tracer subsystem is responsible for tracing output files.

#include <fstream>

#include "SignalDb.h"

/// VCD tracer.
namespace TRACER
{
    /// The VCD file creator.
    /// The class provides means for creating
    /// the output VCD file.
    class VCDTracer
    {
        public:

            /// The VCDTracer constructor.
            ///
            /// @param outputFile Name of the output VCD file.
            /// @param signalDb Signals database to be traced to the output file.
            VCDTracer(const std::string &outputFile, const SIGNAL::SignalDb &signalDb);

            /// Creates the output VCD file.
            ///
            /// Function creates the header of the VCF file as well as the body
            /// listing all signal changes.
            void Dump();

        private:

            /// Generates the VCD header.
            void GenerateHeader();

            /// Generates the basic header information.
            ///
            /// Currently, the creation date and time are constant.
            /// Only the time unit is adjustable.
            void GenerateBasicInformation();

            /// Generate the VCD signals structure.
            ///
            /// Generates the structure of the traced signals. Although indents are
            /// not necessary they have been intruduced to improve the readability
            /// of the VCD file.
            void GenerateSignalStructure();

            /// Generates the default values of the traced signals.
            void GenerateSignalDefaults();

            /// Generates the VCD body.
            ///
            /// Dumps time-ordered signal value changes.
            void GenerateBody();

            /// Write on line to output file.
            void DumpLine(const std::string &line)
            {
                m_File << line << '\n';
            }

            /// The VCD output file.
            std::ofstream m_File;

            /// The signals database.
            const SIGNAL::SignalDb &m_rSignalDb;
    };
}
