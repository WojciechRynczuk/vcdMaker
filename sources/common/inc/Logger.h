/// @file common/inc/Logger.h
///
/// An error and warning logger.
///
/// @par Full Description
/// This is a simple module for printing error and warning messages.
///
/// @ingroup Logger
///
/// @par Copyright (c) 2017 vcdMaker team
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

/// @defgroup Logger Logger
///
/// @brief Errors and warnings logging.
///
/// @par Full Description
/// This is a simple module for printing error and warning messages.

#include "VcdException.h"

/// A simple message logger.
namespace LOGGER
{
    /// A simple message logging module.
    /// The module is used for logging warning and error messages.
    class Logger
    {
        public:
            /// The warning logging method.
            void LogWarning(uint32_t number, const std::string &rMessage);

            /// The error logging method.
            void LogError(const EXCEPTION::VcdException &rException);

            /// Let the logger be a singleton.
            static Logger &GetInstance()
            {
                static Logger instance;
                return instance;
            }

            /// Sets the output stream.
            /// The method is supposed for unit testing.
            ///
            /// @param pOutputStream The default outputstream for warnings and errors.
            void SetOutput(std::ostream *pOutputStream);

        private:
            /// Let it be a singleton.
            Logger();

            /// Returns the formatted exception number.
            ///
            /// @param number The numeric value to be converted and formatted.
            const std::string FormatNumber(uint32_t number) const;

            /// Logging method.
            ///
            /// @param rType The string representing the type of the logged message (error, warning).
            /// @param number The catalogued number of the warnning or error message.
            /// @param rMessage The message to be logged.
            void Log(const std::string &rType, uint32_t number, const std::string &rMessage);

            /// The logger output.
            std::ostream *m_pOutput;
    };
}
