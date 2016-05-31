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

/// @defgroup CliMaker vcdMaker CLI
///
/// @brief The vcdMaker CLI implementation.
///
/// @par Full Description
/// The vcdMaker CLI implementation.

#include <iostream>

#include "CliParser.h"

namespace CLI
{
    /// The vcdMaker CLI child class.
    class CliMaker : public CliParser
    {
        public:
            /// The CLI default constructor.
            CliMaker() :
                CliParser("Log to VCD converter.", "2.0.1")
            {
                /// Allowed timebase units
                allowed_timebase.push_back("s");
                allowed_timebase.push_back("ms");
                allowed_timebase.push_back("us");
                allowed_timebase.push_back("ns");
                allowed_timebase.push_back("ps");
                allowed_timebase.push_back("fs");
                allowedVals = new TCLAP::ValuesConstraint<std::string>(allowed_timebase);

                /// Define the timebase parameter.
                timebase = new TCLAP::ValueArg<std::string>("t", "timebase", "Log timebase specification", true, "ms",
                        allowedVals);
                m_pCli->add(timebase);
            }

            /// Destructor.
            ~CliMaker()
            {
            }

            /// Returns the timebase parameter.
            std::string GetTimebase() const
            {
                return timebase->getValue();
            }

        private:
            /// Points to the string containing valid timebase units.
            TCLAP::ValuesConstraint<std::string> *allowedVals;

            /// Points to the timbese parameter.
            TCLAP::ValueArg<std::string> *timebase;

            /// A placeholder for the valid timebase units.
            std::vector<std::string> allowed_timebase;
    };
}
