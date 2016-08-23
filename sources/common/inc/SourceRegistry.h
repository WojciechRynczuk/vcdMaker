/// @file SourceRegistry.h
///
/// The signal source registry.
///
/// @par Full Description
/// The object of this class will keep a track of the registered source
/// signals. It allows for detecting their duplicated names.
///
/// @ingroup Signal
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

#include <map>
#include <limits>

namespace SIGNAL
{
    /// The signal source registry class.
    class SourceRegistry
    {
        public:
            /// A signal source handle.
            using SignalSourceT = unsigned int;

            /// The source registry constructor.
            SourceRegistry() : m_SourceHandle(std::numeric_limits<SignalSourceT>::max())
            {}

            /// The destructor.
            ~SourceRegistry()
            {}

            /// Registers a signal source.
            ///
            /// @param sourceName The name of the signal source.
            /// @return The handle of the registered signal source.
            ///         Positive integer value for the successful operation.
            ///         0 when operation failed.
            SignalSourceT Register(const std::string sourceName);

            /// Returns the name of the signal source.
            const std::string *GetName(const SignalSourceT sourceHandle);

        private:
            /// A registry.
            using RegistryT = std::map<std::string, SignalSourceT>;

            /// The sources registry.
            RegistryT m_Registry;

            /// The current registry index.
            SignalSourceT m_SourceHandle;

            /// Returns a handle of the given signal source.
            ///
            /// @param sourceName The name of the signal source.
            /// @return The handle of the registered signal source.
            ///         Positive integer value for the successful operation.
            ///         0 when operation failed.
            SignalSourceT GetHandle(const std::string &sourceName);
    };

}
