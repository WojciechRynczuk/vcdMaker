/// @file Source.h
///
/// The signal source class.
///
/// @par Full Description
/// The class defines a signal source entity which can be merged
/// with other sources.
///
/// @ingroup Merge
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

/// @defgroup Merge Merge
///
/// @brief Merge related classes.
///
/// @par Full Description
/// The group gathers classes needed by the merge application.

#include "SignalDb.h"
#include "TxtParser.h"

namespace MERGE
{
    /// The base source class. The objects of this class
    /// can be merged.

    /// A base source class.
    class Source
    {
        public:
            /// Source fields delimeter.
            static const char SOURCE_PARAM_DELIM = ':';

            /// The source constructor.
            ///
            /// @param description The description of the source.
            /// @param signalRegistry The reference to the signal registry common for all sources.
            /// @param verboseMode 'true' enables the verbose mode.
            Source(const std::string &description,
                   SIGNAL::SourceRegistry &signalRegistry,
                   bool verboseMode);

			const SIGNAL::SignalDb* Get();

        private:
            /// A type for splited source parameters.
            using SourceParametersT = std::vector<std::string>;

            /// Source description.
            std::string m_SourceDescription;

			/// Parser.
			PARSER::TxtParser *m_Parser;

            /// Signal registry.
            SIGNAL::SourceRegistry &m_rSignalRegistry;

            /// The signals database.
            const SIGNAL::SignalDb *m_rSignalDb;

            /// The source synchronization point.
            uint64_t m_SyncPoint;

            /// The time unit.
            std::string m_TimeUnit;

            /// The source prefix.
            std::string m_Prefix;

            /// The line counter name.
            std::string m_LineCounter;

            /// The input filename.
            std::string m_Filename;

            /// Verbose mode.
            const bool m_VerboseMode;

            void SetFormat(std::string &format);
            void SetSyncPoint(std::string &syncPoint);
            void SetTimeUnit(std::string &timeUnit);
            void SetPrefix(std::string &prefix);
            void SetCounterName(std::string &lineCounter);
            void SetFilename(std::string &filename);
            void ParseParameters();
            SourceParametersT GetSourceParameters() const;
    };
}
