/// @file vcdMerge/inc/SignalSource.h
///
/// The signal source class.
///
/// @par Full Description
/// The class defines a signal source entity which can be merged
/// with other sources.
///
/// @ingroup Merge
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

#include "TxtParser.h"

namespace MERGE
{
    /// The signal source base class.
    /// The objects of this class describe the source and holds source data.
    class SignalSource
    {
        public:
            /// Source fields delimiter.
            static const char SOURCE_PARAM_DELIM = ',';

            /// Source parameters.
            class Parameters
            {
                public:

                    /// Log format position in the source description.
                    static constexpr size_t LOG_FORMAT = 0;

                    /// Synchronization point position in the source description.
                    static constexpr size_t SYNC_POINT = 1;

                    /// Time unit position in the source description.
                    static constexpr size_t TIME_UNIT = 2;

                    /// Prefix position in the source description.
                    static constexpr size_t PREFIX = 3;

                    /// Line counter position in the source description.
                    static constexpr size_t LINE_COUNTER = 4;

                    /// Filename position in the source description.
                    static constexpr size_t FILENAME = 5;

                    /// Number of a source description's elements.
                    static constexpr size_t SOURCE_PARAM_N = 6;
            };

            /// Source formats.
            class Formats
            {
                public:

                    /// Original vcdMaker text format.
                    static const char VCD_TEXT_FORMAT;

                    /// The user provided XML format.
                    static const char USER_XML_FORMAT;
            };

            /// The source constructor.
            ///
            /// It is only configuring the source. Before all source data
            /// is created (all log files read in and processed) the configurations
            /// shall be validated to return any syntax errors as quickly as possible.
            ///
            /// @param rDescription The description of the source.
            /// @param rSignalRegistry The reference to the signal registry common for all sources.
            /// @param verboseMode 'true' enables the verbose mode.
            SignalSource(const std::string &rDescription,
                         SIGNAL::SourceRegistry &rSignalRegistry,
                         bool verboseMode);

            /// Creates the source data.
            void Create();

            /// Returns a pointer to the source signals.
            const SIGNAL::SignalDb *Get() const
            {
                return m_pSignalDb.get();
            }

            /// Returns the source description.
            const std::string &GetDescription() const
            {
                return m_SourceDescription;
            }

            /// Returns the source prefix.
            const std::string &GetPrefix() const
            {
                return m_Prefix;
            }

            /// Returns the time unit.
            const std::string &GetTimeUnit() const
            {
                return m_TimeUnit;
            }

            /// Returns the source synchronization point.
            uint64_t GetSyncPoint() const
            {
                return m_SyncPoint;
            }

            /// Returns the distance between the first logged signal and
            /// the synchronization point.
            ///
            /// @throws VcdException if the first source timestamp is greater than the synchronization point.
            uint64_t GetLeadingTime() const;

        private:
            /// A type for split source parameters.
            using SourceParametersT = std::vector<std::string>;

            /// The source description.
            const std::string m_SourceDescription;

            /// The signal registry.
            SIGNAL::SourceRegistry &m_rSignalRegistry;

            /// The signals database.
            std::unique_ptr<SIGNAL::SignalDb> m_pSignalDb;

            /// The signal factory.
            std::unique_ptr<PARSER::SignalFactory> m_pSignalFactory;

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
            ///
            /// @throws VcdException for a invalid format.
            void SetFormat(const std::string &rFormat);

            /// Sets the synchronization point of the source.
            ///
            /// @throws VcdException if the format of the synchronization point is invalid.
            void SetSyncPoint(const std::string &rSyncPoint);

            /// Sets the time unit of the source.
            ///
            /// @throws VcdException for an invalid time unit.
            void SetTimeUnit(const std::string &rTimeUnit);

            /// Sets the prefix added to the source signals.
            void SetPrefix(const std::string &rPrefix);

            /// Sets the source line counter name.
            void SetCounterName(const std::string &rLineCounter);

            /// Sets the source log filename.
            ///
            /// @throws VcdException if the file does not exist.
            void SetFilename(const std::string &rFilename);

            /// Parses user provided parameters.
            ///
            /// @throws VcdException for an invalid number of source parameters.
            void ParseParameters();

            /// Divides the aggregated user parameter into fields.
            SourceParametersT GetSourceParameters() const;

            /// Throws the exception.
            ///
            /// @param rFilename The name of the inaccessible file.
            /// @throws VcdException
            void ThrowFileInaccessibleException(const std::string &rFilename) const;

            /// Checks if the format of the given source is the original VCD format.
            bool IsVcdFormat(const std::string &rFormat) const;

            /// Checks if the format of the given source is the user XML format.
            bool IsUserXmlFormat(const std::string &rFormat) const;
    };
}
