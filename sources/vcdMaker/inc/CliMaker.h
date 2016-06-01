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
                m_AllowedTimebase.push_back("s");
                m_AllowedTimebase.push_back("ms");
                m_AllowedTimebase.push_back("us");
                m_AllowedTimebase.push_back("ns");
                m_AllowedTimebase.push_back("ps");
                m_AllowedTimebase.push_back("fs");
                m_pAllowedVals = new TCLAP::ValuesConstraint<std::string>(m_AllowedTimebase);

                /// Define the timebase parameter.
                m_pTimebase = new TCLAP::ValueArg<std::string>("t", "timebase", "Log timebase specification", true, "ms",
                        m_pAllowedVals);
                m_pCli->add(m_pTimebase);
            }

            /// Destructor.
            ~CliMaker()
            {
                delete m_pTimebase;
                delete m_pAllowedVals;
            }

            /// Returns the timebase parameter.
            std::string GetTimebase() const
            {
                return m_pTimebase->getValue();
            }

        private:
            /// Points to the string containing valid timebase units.
            TCLAP::ValuesConstraint<std::string> *m_pAllowedVals;

            /// Points to the timbese parameter.
            TCLAP::ValueArg<std::string> *m_pTimebase;

            /// A placeholder for the valid timebase units.
            std::vector<std::string> m_AllowedTimebase;
    };
}
