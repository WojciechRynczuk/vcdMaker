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

#pragma once

/// @defgroup Tracer Tracer
///
/// @brief The VCD tracer core.
///
/// @par Full Description
/// The Tracer subsystem is the core of the application. It is responsible
/// for collecting the signals and storing them in the VCD format.

#include <fstream>
#include <string>

#include "Signal.h"

namespace TRACER
{

    ///  This class collects signals and creates the output VCD file.
    ///
    /// The class provides means for storing signals and creating
    /// the output VCD file.
    class VCDTracer
    {
        public:

            /// The VCDTracer constructor.
            ///
            /// @param outputFile Name of the output VCD file.
            /// @param timeUnit Selection of time units in which logged signals are timestamped.
            VCDTracer(const std::string &outputFile, const std::string &timeUnit);

            /// The destructor.
            ~VCDTracer();

            /// Logs a signal.
            ///
            /// This method adds a signal to the signals' container.
            /// IMPORTANT!!! The signals do not have to be ordered (in the terms of time).
            /// They will be re-ordered automatically upon dumping the VCD file.
            void Log(const SIGNAL::Signal *signal);

            /// Creates the output VCD file.
            ///
            /// Funcgtion creates the header of the VCF file as well as the body
            /// listing all signal changes.
            void Dump();

            /// Validates given time unit string.
            static bool IsTimeUnitValid(const std::string &timeUnit);

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
            /// @note Multiple changes in the same timestamp are not checked.
            void GenerateBody();

            /// Write on line to output file.
            void DumpLine(const std::string &line)
            {
                m_File << line << '\n';
            }

            /// The VCD output file.
            std::ofstream m_File;

            /// The VCD time unit in which the signals are timestamped.
            const std::string m_TimeUnit;

            /// The current signals state.
            SIGNAL::UniqueSignalsCollectionT m_AddedSignals;

            /// The container for the signals.
            SIGNAL::SignalCollectionT m_SignalSet;
    };

}
