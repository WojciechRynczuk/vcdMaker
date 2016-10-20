/// @file CliMerge.h
///
/// The vcdMerge CLI implemantation.
///
/// @par Full Description
/// The vcdMerge CLI implemantation.
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
#include "Version.h"

namespace CLI
{

    /// The vcdMaker CLI child class.
    class CliMerge : public CliParser
    {
        public:

            /// The CLI default constructor.
            CliMerge() :
                CliParser("VCD merging tool.", VERSION::STRING)
            {
                m_Cli.add(m_Timebase);
                m_Cli.add(m_SourcesIn);
            }

            /// Return by a list of files to be processed.
            const std::vector<std::string> &GetInputSources()
            {
                return m_SourcesIn.getValue();
            }

            /// Return the output time unit.
            std::string GetTimeBase()
            {
                return m_Timebase.getValue();
            }

        private:

            /// A list of valid timebase units.
            std::vector<std::string> m_AllowedTimebaseValues{ "s", "ms", "us", "ns", "ps", "fs" };

            /// Valid timebases constraint.
            TCLAP::ValuesConstraint<std::string> m_AllowedTimebases{ m_AllowedTimebaseValues };

            /// Timebase parameter.
            TCLAP::ValueArg<std::string> m_Timebase
                { "t", "timebase", "Log timebase specification", false, "", &m_AllowedTimebases };

            /// Input sources.
            TCLAP::UnlabeledMultiArg<std::string> m_SourcesIn
                { "source_in", "Input sources", true, "Source" };
    };

}
