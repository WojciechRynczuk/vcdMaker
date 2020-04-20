/// @file common/inc/SignalDescriptorRegistry.h
///
/// The signal descriptor registry.
///
/// @par Full Description
/// The signal descriptor registry. It is supposed to create unique signal 
/// descriptors and maintain its collection during the whole application lifetime.
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

#include "SignalDescriptor.h"

namespace SIGNAL
{
    /// A signal descriptor database class.
    /// The database keep a record of unique signal descriptors.
    class SignalDescriptorRegistry
    {
    public:
        /// The signal descriptor databse constructor.
        ///
        /// Initializes the database.
        ///
        SignalDescriptorRegistry() : m_SignalDescriptors()
        {
        }

        /// The default destructor.
        ~SignalDescriptorRegistry() = default;

        /// Creates the descriptor and adds it to the database.
        ///
        /// @param rName Signal name.
        /// @param rType Signal type.
        /// @param size Signal size. 
        /// @param sourceHandle Signal source.
        /// @return The created signal descriptor.
        const std::shared_ptr<const SignalDescriptor> Register(const std::string& rName,
                                                               const std::string& rType,
                                                               size_t size,
                                                               SourceRegistry::HandleT sourceHandle);

    private:

        /// The set of pointers to signal descriptors indexed by names.
        std::map<const std::string, std::shared_ptr<const SignalDescriptor>> m_SignalDescriptors{};
    };
}
