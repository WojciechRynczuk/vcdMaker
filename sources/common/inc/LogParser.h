/// @file LogParser.h
///
/// The log parser interface class.
///
/// @par Full Description
/// The log parser interface class.
///
/// @ingroup Parser
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

/// @defgroup Parser Parser
///
/// @brief The log parser group.
///
/// @par Full Description
/// The group provides means for reading input files.

#include <fstream>
#include <sstream>

#include "SignalDb.h"

namespace PARSER
{
    /// The log parser base class.
    class LogParser
    {
        public:

            /// The log parser constructor.
            ///
            /// This constructor shall be used by the iheriting classes.
            /// It opens the input log file and sets the verbose mode.
            ///
            /// @param filename The name of the log file to be open.
            /// @param verboseMode Value 'true' enables the verbose mode.
            LogParser(std::string filename, bool verboseMode)
            {
                m_FileName = filename;

                m_LogFile.open(filename, std::ifstream::out);
                if (false == m_LogFile.is_open())
                {
                    std::ostringstream msg;
                    msg << "Opening file '" << filename
                        << "' failed, it either doesn't exist or is inaccessible.";
                    throw std::runtime_error(msg.str());
                }
                m_VerboseMode = verboseMode;
            }

            /// The destructor.
            ~LogParser()
            {
                m_LogFile.close();
            }

            /// Returns the pointer to the signal database.
            SIGNAL::SignalDb *GetSignalDb()
            {
                return m_pSignalDb;
            }

        protected:

            /// The signal databse.
            SIGNAL::SignalDb *m_pSignalDb;

            /// The input file name.
            std::string m_FileName;

            /// The input log file.
            std::ifstream m_LogFile;

            /// Verbose mode.
            bool m_VerboseMode;
    };

}
