/// @file SignalStructureBuilder.h
///
/// VCD signal structure builder class.
///
/// @ingroup Tracer
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

#include <map>
#include <string>
#include <ostream>
#include <tuple>

#include "Signal.h"

namespace TRACER
{
    /// VCD signal structure builder.
    class SignalStructureBuilder
    {
        public:

            /// Type used for unique signals map: name => signal.
            ///
            /// Signal values doesn't matter, this map is only used to generate strucutre.
            using UniqueSignalsCollectionT = std::map<std::string, const SIGNAL::Signal *>;

            /// Constructor.
            ///
            /// @param uniqueSignals Structure will be generated from this signals.
            /// @param output Structure will be written to this stream.
            SignalStructureBuilder(const UniqueSignalsCollectionT &uniqueSignals,
                                   std::ostream &output) :
                m_UniqueSignals(uniqueSignals),
                m_Output(output)
            {
            }

            /// Dump generated structure to assigned stream.
            void Dump();

        private:

            /// Dump generated line to assigned stream with indent.
            void DumpIndented(const std::string &value, std::size_t indentLevel)
            {
                m_Output << std::string(indentLevel, '\t') << value << '\n';
            }

            /// Checks if scopes should be ended or continued.
            ///
            /// If no mismatch was found current scope should be continued from
            /// returned index. If mismatch was found, scopes should be ended
            /// down to returned index and new should be started from it.
            /// @param currentFields Fields from current iteration.
            /// @param previousFields Fields from previous iteration.
            /// @return Continuation index.
            std::tuple<bool, std::size_t> FindContinuation(const SIGNAL::Signal::SignalNameFieldsT &currentFields,
                                                           const SIGNAL::Signal::SignalNameFieldsT &previousFields);

            /// Ends scopes from the end of fields to lowerLimit.
            ///
            /// If lowerLimit is 0 all scopes are ended.
            void EndScopesDownTo(const SIGNAL::Signal::SignalNameFieldsT &fields,
                                 std::size_t lowerLimit);

            /// Continues current scope (possibly after mismatch)
            /// 
            /// @param continueFrom Continuation index obtained from FindContinuation.
            /// @param fields Fields from current iteration.
            /// @param signal Signal in current iteration.
            void ContinueScopes(std::size_t continueFrom,
                                const SIGNAL::Signal::SignalNameFieldsT &fields,
                                const SIGNAL::Signal *signal);

            /// Unique signals map.
            const UniqueSignalsCollectionT m_UniqueSignals;

            /// Assigned output stream.
            std::ostream &m_Output;
    };

}

