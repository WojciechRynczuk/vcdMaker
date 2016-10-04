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

#include "SignalDb.h"
#include "TxtParser.h"

namespace MERGE
{
    /// The base source class. The objects of this class
    /// describes the source and holds source data.

    /// A base source class.
    class Source
    {
        public:
            /// Source fields delimiter.
            static const char SOURCE_PARAM_DELIM = ';';

            /// Source parameters.
            class Parameters
            {
                public:

                    static constexpr size_t LOG_FORMAT = 0;
                    static constexpr size_t SYNC_POINT = 1;
                    static constexpr size_t TIME_UNIT= 2;
                    static constexpr size_t PREFIX = 3;
                    static constexpr size_t LINE_COUNTER = 4;
                    static constexpr size_t FILENAME = 5;

                    static constexpr size_t SOURCE_PARAM_N = 6;
            };

            /// The source constructor.
            ///
            /// It is ONLY configuring the source. Before all source data
            /// is created (all log files read in and processed) the configurations
            /// shall be validated to return any syntax errors as quickly as possible.
            ///
            /// @param description The description of the source.
            /// @param signalRegistry The reference to the signal registry common for all sources.
            /// @param verboseMode 'true' enables the verbose mode.
            Source(const std::string &description,
                   SIGNAL::SourceRegistry &signalRegistry,
                   bool verboseMode);

            /// Returns a pointer to the source signals.
            const SIGNAL::SignalDb *Get() const
            {
                return m_pSignalDb.get();
            }

        private:
            /// A type for split source parameters.
            using SourceParametersT = std::vector<std::string>;

            /// The source description.
            const std::string m_SourceDescription;

            /// The signal registry.
            SIGNAL::SourceRegistry &m_rSignalRegistry;

            /// The signals database.
            std::unique_ptr<SIGNAL::SignalDb> m_pSignalDb;

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

            /// Sets the format of the source log file.
            void SetFormat(const std::string &format);

            /// Sets the synchronization point of the source.
            void SetSyncPoint(const std::string &syncPoint);

            /// Sets the time unit of the source.
            void SetTimeUnit(const std::string &timeUnit);

            /// Sets the prefix added to the source signals.
            void SetPrefix(const std::string &prefix);

            /// Sets the source line counter name.
            void SetCounterName(const std::string &lineCounter);

            /// Sets the source log filename.
            void SetFilename(const std::string &filename);

            /// Parses user provided parameters.
            void ParseParameters();

            /// Divides the aggregated user parameter into fields.
            SourceParametersT GetSourceParameters() const;
    };
}
