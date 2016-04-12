/// @file CliParser.h
///
/// The base class of the CLI parser.
///
/// @par Full Description
/// The base class of the simple Command Line Interface parser.
///
/// @ingroup CLI
///
/// @par Copyright (c) 2016 Wojciech Rynczuk
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
/// This is a simple CLI parser.

#include <string>
#include <vector>

namespace CLI
{

    /// The base CLI parser class.
    class CliParser
    {
        public:
            /// The CLI constructor.
            ///
            /// This constructor shall be used by the iheriting classes.
            ///
            /// @param argc Arguments count from main function.
            /// @param argv Arguments array from main function.
            CliParser(std::size_t argc, char **argv) : m_Parameters(argv, argv + argc)
            {
            }

            /// Destructor.
            virtual ~CliParser() = 0;

            /// Returns the value of the given parameter.
            ///
            /// Eg. for "-f" it could return the file name.
            /// If not found, NULL is returned.
            ///
            /// @param param Parameter name.
            std::string GetParamValue(const std::string &param) const;

            /// Checks the parameter's existence.
            ///
            /// Returns true if the provided string has been a part of the
            /// command line input.
            ///
            /// @param param Parameter name.
            bool CheckParam(const std::string &param) const;

            /// Validates input parameters.
            ///
            /// Returns true if the input parameters are valid.
            /// It shall be called upon the construction of the object.
            bool Validate() const;

        protected:

            /// Prints one line help information.
            virtual void OneLineHelp() const = 0;

            /// Print full help infomration.
            virtual void Help() const = 0;

            /// The parameters validator.
            ///
            /// The parameters validator method is used by the
            /// Validate() method to analyse the provided input.
            virtual bool Validator() const = 0;

        private:

            /// Parameters vector
            std::vector<std::string> m_Parameters;
    };

    inline CliParser::~CliParser() = default;

}
