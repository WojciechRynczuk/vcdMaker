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

#include <map>
#include <limits>

namespace SIGNAL
{
    /// The signal source registry class.
    class SourceRegistry
    {
        public:
            /// A signal source handle (integral type).
            using HandleT = unsigned int;

            /// Bad handle constant.
            static constexpr HandleT BAD_HANDLE =
                std::numeric_limits<HandleT>::min();

            /// Source registry is unique. Let it be a singleton.
            static SourceRegistry &GetInstance()
            {
                static SourceRegistry instance;
                return instance;
            }

            /// Registers a signal source.
            ///
            /// @param rSourceName The name of the signal source.
            /// @return The handle of the registered signal source.
            ///         BAD_HANDLE if operation failed.
            ///
            /// @note C++17 std::optional should be used here.
            HandleT Register(const std::string &rSourceName);

            /// Returns the name of the signal source.
            ///
            /// @throws VcdError if cannot find the source name.
            /// @param sourceHandle The source handle.
            std::string GetSourceName(HandleT sourceHandle) const;

        private:
            /// The default constructor.
            SourceRegistry();

            /// A registry type.
            using RegistryT = std::map<std::string, HandleT>;

            /// The sources registry.
            RegistryT m_Registry;

            /// The next available registry handle.
            HandleT m_NextSourceHandle =
                std::numeric_limits<HandleT>::max();

            /// Returns a handle of the given signal source.
            ///
            /// @param rSourceName The name of the signal source.
            /// @return The handle of the registered signal source.
            ///         BAD_HANDLE if operation failed.
            ///
            /// @note C++17 std::optional should be used here.
            HandleT GetHandleForSource(const std::string &rSourceName);

            /// Returns new handle.
            ///
            /// @throws VcdError if no handles available.
            HandleT GetNewHandle();
    };
    inline SourceRegistry::SourceRegistry() = default;
}
