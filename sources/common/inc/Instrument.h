/// @file common/inc/Instrument.h
///
/// The instrument interface class.
///
/// @par Full Description
/// The instrument interface class.
///
/// @ingroup Instrument
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

/// @defgroup Instrument Instrument
///
/// @brief The instrument group.
///
/// @par Full Description
/// The group is designed to provide instruments (observers) which can
/// be hooked into log parsers.

#include "SignalDb.h"

/// Instrumentation.
namespace INSTRUMENT
{
    /// The instrument interface class.
    class Instrument
    {
        public:
            /// A line number type (integral type).
            using LineNumberT = size_t;

            /// The instrument notification method.
            ///
            /// It is to be invoked by a parser.
            ///
            /// @param lineNumber The line number.
            /// @param rSignal The signal.
            virtual void Notify(LineNumberT lineNumber, const SIGNAL::Signal &rSignal) = 0;

            /// Signalize the instrument the end of the parsing process.
            virtual void Terminate() const = 0;

        protected:

            /// The instrument constructor.
            ///
            /// This constructor shall be used by the inheriting classes.
            ///
            /// @param rSourceRegistry A signal sources registry.
            /// @param rSignalDb A signal database.
            /// @param rSourceName A source name.
            Instrument(SIGNAL::SourceRegistry &rSourceRegistry,
                       SIGNAL::SignalDb &rSignalDb,
                       const std::string &rSourceName) :
                m_rSignalDb(rSignalDb),
                m_InstrumentHandle(rSourceRegistry.Register(rSourceName))
            {
            }

            /// The instrument destructor.
            virtual ~Instrument() = 0;

            /// The signal database.
            SIGNAL::SignalDb &m_rSignalDb;

            /// The instrument handle.
            SIGNAL::SourceRegistry::HandleT m_InstrumentHandle;
    };

    inline Instrument::~Instrument() = default;

}
