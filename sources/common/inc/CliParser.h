/// @file CliParser.h
///
/// The CLI facade class.
///
/// @par Full Description
/// The facade class of the TCLAP parser.
/// http://tclap.sourceforge.net/
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

/// @defgroup CLI CLI
///
/// @brief The Command Line Interface group.
///
/// @par Full Description
/// Common CLI implementation.

#include "tclap/CmdLine.h"

namespace CLI
{
    /// The base CLI parser class.
    class CliParser
    {
        public:
            /// The default costructor
            ///
            /// It is forbidden
            CliParser() = delete;

            /// The CliParser constructor.
            ///
            /// This constructor shall be used by the iheriting classes.
            ///
            /// @param desc A description of the application.
            /// @param version A version number of the application.
            CliParser(const std::string &desc, const std::string &version) :
                m_pCli(new TCLAP::CmdLine(desc, ' ', version))
            {
                // Define the unput file parameter.
                m_pFileIn = new TCLAP::ValueArg<std::string>("f", "file_in", "Input log filename", true, "log.txt", "string");
                m_pCli->add(m_pFileIn);

                // Define the output file parameter.
                m_pFileOut = new TCLAP::ValueArg<std::string>("o", "file_out", "Ouput VCD filename", true, "log.vcd", "string");
                m_pCli->add(m_pFileOut);

                // Define the verbose mode switch.
                m_pVerboseMode = new TCLAP::SwitchArg("v", "verbose", "Verbose mode", false);
                m_pCli->add(m_pVerboseMode);
            }

            /// Destructor.
            ~CliParser()
            {
                delete m_pCli;
                delete m_pFileIn;
                delete m_pFileOut;
                delete m_pVerboseMode;
            }

            /// The parsing method.
            ///
            /// This method shall be invoked to parse the application command line options.
            ///
            /// @param argc Arguments count from main function.
            /// @param argv Arguments array from main function.
            void Parse(int argc, const char *argv[])
            {
                m_pCli->parse(argc, argv);
            }

            /// Returns the output file name.
            std::string GetOutputFileName() const
            {
                return m_pFileOut->getValue();
            }

            /// Returns the input file name.
            std::string GetInputFileName() const
            {
                return m_pFileIn->getValue();
            }

            /// Returns the verbose mode value.
            ///
            /// Returns 'true' for the verbose mode enabled.
            bool IsVerboseMode() const
            {
                return m_pVerboseMode->getValue();
            }

        private:
            /// Points to the input file parameter.
            TCLAP::ValueArg<std::string> *m_pFileIn;

            /// Points to the output file parameter.
            TCLAP::ValueArg<std::string> *m_pFileOut;

            // Points to the verbose mode switch state.
            TCLAP::SwitchArg *m_pVerboseMode;

        protected:
            /// The tclap CLI structure
            TCLAP::CmdLine *m_pCli;
    };
}
