/// @file common/src/SignalDescriptorRegistry.cpp
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

#include "SignalDescriptorRegistry.h"
#include "VcdException.h"

const SIGNAL::SignalDescriptor * const SIGNAL::SignalDescriptorRegistry::Register(
    const std::string &rName,
    const std::string &rType,
    size_t size,
    SourceRegistry::HandleT sourceHandle)
{
    const auto it = m_SignalDescriptors.find(rName);

    // Is this a new signal to be registered?
    if (it == m_SignalDescriptors.end())
    {
        auto signalDescriptor = std::make_shared<const SignalDescriptor>(rName, size, rType, sourceHandle);
        m_SignalDescriptors[rName] = signalDescriptor;
        return signalDescriptor.get();
    }

    // Check signal consistency.
    if (!it->second->SimilarTo(rType, size, sourceHandle))
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::INCONSISTENT_SIGNAL,
                                      "Inconsistent signal: " +
                                      rName +
                                      ". Types: " +
                                      it->second->GetType() + " / " + rType +
                                      ". Sizes: " +
                                      std::to_string(it->second->GetSize()) + " / " + std::to_string(size) +
                                      ". Sources: " +
                                      SIGNAL::SourceRegistry::GetInstance().GetSourceName(it->second->GetSource()) +
                                      " and " +
                                      SIGNAL::SourceRegistry::GetInstance().GetSourceName(sourceHandle) + ".");
    }

    return it->second.get();
}
