/// @file SourceRegistry.cpp
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

#include "SourceRegistry.h"

SIGNAL::SourceRegistry::SignalSourceT SIGNAL::SourceRegistry::Register(const std::string sourceName)
{
    // Check if the source has been already registered.
    SignalSourceT handle = GetHandle(sourceName);
    if (handle > 0)
    {
        return handle;
    }

    // Assign a new handle.
    if (m_SourceHandle > 0)
    {
        handle = m_SourceHandle;
        m_Registry[sourceName] = m_SourceHandle;
        --m_SourceHandle;
    }
    else
    {
        throw std::runtime_error("Too many signal sources!");
    }

    return handle;
}

const std::string *SIGNAL::SourceRegistry::GetName(const SignalSourceT sourceHandle)
{
    for (RegistryT::iterator it = m_Registry.begin(); it != m_Registry.end(); ++it)
    {
        if (sourceHandle == it->second)
        {
            // If the source has been registered return its handle.
            return &it->first;
        }
    }

    return nullptr;
}

SIGNAL::SourceRegistry::SignalSourceT SIGNAL::SourceRegistry::GetHandle(const std::string &sourceName)
{
    RegistryT::iterator it;

    // Check if the source has been already registered.
    it = m_Registry.find(sourceName);
    if (it != m_Registry.end())
    {
        return m_Registry[sourceName];
    }
    else
    {
        return 0;
    }
}
