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

#include "SourceRegistry.h"
#include "VcdError.h"

/// Logic error. Cannot find source signal name.
class CannotFindSourceSignalName : public EXCEPTION::VcdErrorLogic
{
    public:
        /// The cannot find source signal name exception constructor.
        CannotFindSourceSignalName() :
            VcdErrorLogic(EXCEPTION::Error::CANNOT_FIND_SOURCE_SIGNAL_NAME,
                          "Couldn't find source signal name!")
        {
        }
};

/// Logic error. Too many signal sources.
class TooManySignalSources : public EXCEPTION::VcdErrorLogic
{
    public:
        /// Too many signal sources exception constructor.
        TooManySignalSources() :
            VcdErrorLogic(EXCEPTION::Error::TOO_MANY_SIGNAL_SOURCES,
                          "Too many signal sources!")
        {
        }
};

SIGNAL::SourceRegistry::HandleT SIGNAL::SourceRegistry::Register(const std::string &rSourceName)
{
    const HandleT existing_handle = GetHandleForSource(rSourceName);

    if (existing_handle == BAD_HANDLE)
    {
        const HandleT new_handle = GetNewHandle();
        m_Registry[rSourceName] = new_handle;

        return new_handle;
    }
    else
    {
        return existing_handle;
    }
}

std::string SIGNAL::SourceRegistry::GetSourceName(const HandleT sourceHandle) const
{
    for (const auto &registryItem : m_Registry)
    {
        if (sourceHandle == registryItem.second)
        {
            return registryItem.first;
        }
    }

    throw CannotFindSourceSignalName();
}

SIGNAL::SourceRegistry::HandleT SIGNAL::SourceRegistry::GetHandleForSource(const std::string &rSourceName)
{
    const RegistryT::const_iterator it = m_Registry.find(rSourceName);

    if (it != m_Registry.end())
    {
        return it->second;
    }
    else
    {
        return BAD_HANDLE;
    }
}

SIGNAL::SourceRegistry::HandleT SIGNAL::SourceRegistry::GetNewHandle()
{
    if (m_NextSourceHandle > BAD_HANDLE)
    {
        HandleT nextHandle = m_NextSourceHandle;
        --m_NextSourceHandle;
        return nextHandle;
    }
    else
    {
        throw TooManySignalSources();
    }
}
