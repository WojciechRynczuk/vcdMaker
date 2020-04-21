/// @file common/inc/SignalDescriptor.h
///
/// The signal descriptor.
///
/// @par Full Description
/// The signal descriptor defines a signal's constant properties such as
/// name, size, type and source.
///
/// @ingroup Signal
///
/// @par Copyright (c) 2020 vcdMaker team
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

#include <string>

#include "SourceRegistry.h"

namespace SIGNAL
{
    /// A signal descriptor class.
    /// The class collects constant signal properties such as its name, size,
    /// type and the source.
    class SignalDescriptor
    {
        public:
            /// The signal descriptor constructor.
            ///
            /// It initializes the constant signal properties: the name, the size
            /// the type and its source handle.
            ///
            /// The name shall consist of any alphanumeric string in which the module's
            /// levels are separated with '.'.
            /// E.g. Module1.Level3.Variable6
            ///
            /// The size usually corresponds to any of the integral data type
            /// sizes: 8, 16, 32 or 64.
            ///
            /// The type string is used to produce the VCD header. It describes
            /// the type of the signal and shall equal to "wire" or "real".
            ///
            /// The source handle identifies the origin of the source.
            ///
            /// @param rName Signal name.
            /// @param size Signal size.
            /// @param rType Signal type.
            /// @param sourceHandle Signal source handle.
            SignalDescriptor(const std::string &rName,
                             size_t size,
                             const std::string &rType,
                             SourceRegistry::HandleT sourceHandle) :
                m_Name(rName),
                m_Type(rType),
                m_Size(size),
                m_SourceHandle(sourceHandle)
            {
            }

            /// Returns the signal's name.
            const std::string &GetName() const;

            /// Returns the signal's size in bits.
            size_t GetSize() const;

            /// Returns the signal's type.
            const std::string &GetType() const;

            /// Returns the source handle of the signal.
            SourceRegistry::HandleT GetSource() const;

            /// Check signal consistency.
            ///
            /// To be invoked for the signals having the same name. It verifies the consistency of other
            /// signal properties.
            /// @param rType Signal type.
            /// @param size Signal size.
            /// @param sourceHandle Signal source.
            bool SimilarTo(const std::string &rType, size_t size, SourceRegistry::HandleT sourceHandle) const;

        private:

            /// The signal's name.
            const std::string m_Name {};

            /// The signal's type.
            const std::string m_Type {};

            /// The signal's size.
            const size_t m_Size = 0;

            /// The signal's source.
            const SourceRegistry::HandleT m_SourceHandle =
                SIGNAL::SourceRegistry::BAD_HANDLE;

            /// Checks if two descriptors match.
            bool EqualTo(SignalDescriptor const &other) const;

            /// The overloaded == operator.
            ///
            /// Checks if two signal descriptors are equal. EqualTo is used.
            friend bool operator == (const SignalDescriptor &lSignalDesc, const SignalDescriptor &rSignalDesc)
            {
                return lSignalDesc.EqualTo(rSignalDesc);
            }

            /// The overloaded != operator.
            ///
            /// Checks if two signal descriptors are not equal. EqualTo is used.
            friend bool operator != (const SignalDescriptor &lSignalDesc, const SignalDescriptor &rSignalDesc)
            {
                return !lSignalDesc.EqualTo(rSignalDesc);
            }
    };
}
