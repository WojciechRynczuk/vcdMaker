/// @file common/src/XmlSignalFactory.cpp
///
/// The user defined signal factory class.
///
/// @par Full Description
/// The signal factory object to create the appropriate signal objects upon
/// the XML description.
///
/// @ingroup Parser
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

#include "XmlSignalFactory.h"
#include "XmlEventSignalCreator.h"
#include "XmlFSignalCreator.h"
#include "XmlISignalCreator.h"
#include "VcdException.h"

PARSER::XmlDescription::XmlDescription(const pugi::xml_node &rNode) :
    m_RegexLine(),
    m_Timestamp(),
    m_Name(),
    m_Value(),
    m_Size()
{
    for (const pugi::xml_node &tag : rNode.children())
    {
        if (!std::strcmp("line", tag.name()))
        {
            m_RegexLine = tag.child_value();
        }

        if (!std::strcmp("timestamp", tag.name()))
        {
            m_Timestamp = tag.child_value();
        }

        if (!std::strcmp("name", tag.name()))
        {
            m_Name = tag.child_value();
        }

        if (!std::strcmp("value", tag.name()))
        {
            m_Value = tag.child_value();
        }

        if (!std::strcmp("size", tag.name()))
        {
            m_Size = tag.child_value();
        }
    }
}

const std::string &PARSER::XmlDescription::GetRegex() const
{
    if (!m_RegexLine.empty())
    {
        return m_RegexLine;
    }
    throw EXCEPTION::VcdException(EXCEPTION::Error::NO_REGEX_EXPRESSION,
                                  "XML - No parsing regular expression.");
}

const std::string &PARSER::XmlDescription::GetTimestamp() const
{
    if (!m_Timestamp.empty())
    {
        return m_Timestamp;
    }
    throw EXCEPTION::VcdException(EXCEPTION::Error::NO_TIMESTAMP_EXPRESSION,
                                  "XML - No timestamp expression.");
}

const std::string &PARSER::XmlDescription::GetName() const
{
    if (!m_Name.empty())
    {
        return m_Name;
    }
    throw EXCEPTION::VcdException(EXCEPTION::Error::NO_NAME_EXPRESSION,
                                  "XML - No name expression.");
}

const std::string &PARSER::XmlDescription::GetValue() const
{
    if (!m_Value.empty())
    {
        return m_Value;
    }
    throw EXCEPTION::VcdException(EXCEPTION::Error::NO_VALUE_EXPRESSION,
                                  "XML - No value expression.");
}

const std::string &PARSER::XmlDescription::GetSize() const
{
    if (!m_Size.empty())
    {
        return m_Size;
    }
    throw EXCEPTION::VcdException(EXCEPTION::Error::NO_SIZE_EXPRESSION,
                                  "XML - No size expression.");
}

PARSER::XmlSignalFactory::XmlSignalFactory(const std::string &rXmlFileName) :
    SignalFactory()
{
    // Parse the XML and add signal creators.
    pugi::xml_document doc;
    if (!doc.load_file(rXmlFileName.c_str()))
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::XML_READ_ERROR,
                                      "Opening XML file '" + rXmlFileName + "' failed. The XML file might be incorrect.");
    }

    pugi::xml_node signals = doc.child("signals");

    // Traverse the XML.
    for (const pugi::xml_node &signal : signals.children())
    {
        if (!std::strcmp("vector", signal.name()))
        {
            std::unique_ptr<XmlDescription> description = std::make_unique<XmlDescription>(signal);
            m_vpSignalCreators.push_back(std::make_unique<XmlISignalCreator>(description->GetRegex(),
                                                                             description->GetTimestamp(),
                                                                             description->GetName(),
                                                                             description->GetValue(),
                                                                             description->GetSize()));
        }
        else if (!std::strcmp("real", signal.name()))
        {
            std::unique_ptr<XmlDescription> description = std::make_unique<XmlDescription>(signal);
            m_vpSignalCreators.push_back(std::make_unique<XmlFSignalCreator>(description->GetRegex(),
                                                                             description->GetTimestamp(),
                                                                             description->GetName(),
                                                                             description->GetValue()));
        }
        else if (!std::strcmp("event", signal.name()))
        {
            std::unique_ptr<XmlDescription> description = std::make_unique<XmlDescription>(signal);
            m_vpSignalCreators.push_back(std::make_unique<XmlEventSignalCreator>(description->GetRegex(),
                                                                                 description->GetTimestamp(),
                                                                                 description->GetName()));
        }
        else
        {
            throw EXCEPTION::VcdException(EXCEPTION::Error::UNEXPECTED_TAG,
                                          "XML - Unexpected tag: " + std::string(signal.name()));
        }
    }
}
