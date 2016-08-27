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

    /// The CLI base class.
    class CliParser
    {
        public:

            /// The default costructor.
            ///
            /// It is forbidden.
            CliParser() = delete;

            /// The CliParser constructor.
            ///
            /// This constructor shall be used by the inheriting classes.
            ///
            /// @param desc A description of the application.
            /// @param version A version number of the application.
            CliParser(const std::string &desc, const std::string &version) :
                m_Cli(desc, ' ', version)
            {
                m_Cli.add(m_FileOut);
                m_Cli.add(m_VerboseMode);
            }

            /// The parsing method.
            ///
            /// This method shall be invoked to parse the application command line options.
            ///
            /// @param argc Arguments count from main function.
            /// @param argv Arguments array from main function.
            void Parse(int argc, const char *argv[])
            {
                m_Cli.parse(argc, argv);
            }

            /// Returns the output file name.
            const std::string &GetOutputFileName()
            {
                return m_FileOut.getValue();
            }

            /// Returns the verbose mode value.
            ///
            /// Returns 'true' for the verbose mode enabled.
            bool IsVerboseMode()
            {
                return m_VerboseMode.getValue();
            }

        protected:

            /// The tclap CLI class.
            TCLAP::CmdLine m_Cli;

        private:

            /// Output file parameter.
            TCLAP::ValueArg<std::string> m_FileOut
                {"o", "file_out", "Ouput VCD filename", true, "log.vcd", "string"};

            // Verbose mode switch state.
            TCLAP::SwitchArg m_VerboseMode
                {"v", "verbose", "Enables verbose mode", false};
    };

}
