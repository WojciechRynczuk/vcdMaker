/// @file CliMaker.h
///
/// The vcdMaker CLI implemantation.
///
/// @par Full Description
/// The vcdMaker CLI implemantation.
///
/// @ingroup CLI
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

#include "CliParser.h"
#include "Signal.h"
#include "Version.h"

namespace CLI
{

    /// The vcdMaker CLI child class.
    class CliMaker : public CliParser
    {
        public:

            /// The CLI default constructor.
            CliMaker() :
                CliParser("Log file to VCD converter.", VERSION::STRING)
            {
                m_Cli.add(m_Timebase);
                m_Cli.add(m_FileIn);
                m_Cli.add(m_LineCounter);
            }

            /// Returns the timebase parameter.
            const std::string& GetTimebase()
            {
                return m_Timebase.getValue();
            }

            /// Returns the input filename.
            const std::string& GetInputFileName()
            {
                return m_FileIn.getValue();
            }

            /// Returns the line counter signal name.
            const std::string& GetLineCounterName()
            {
                return m_LineCounter.getValue();
            }

        private:

            /// Valid timebases constraint.
            TCLAP::ValuesConstraint<std::string> m_AllowedTimebases{SIGNAL::Signal::TIME_UNITS};

            /// Timebase parameter.
            TCLAP::ValueArg<std::string> m_Timebase
                {"t", "timebase", "Log timebase specification", true, "ms", &m_AllowedTimebases};

            /// Input filename parameter.
            TCLAP::UnlabeledValueArg<std::string> m_FileIn
                { "file_in", "Input log filename", true, "log.txt", "input-file" };

            /// Line counter parameter.
            TCLAP::ValueArg<std::string> m_LineCounter
                { "c", "line_counter", "Line counter signal name", false, "", "line-counter-signal-name"};
    };

}
