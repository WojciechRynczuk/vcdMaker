/// @file common/inc/XmlSignalFactory.h
///
/// The user defined signal factory class.
///
/// @par Full Description
/// The signal factory object to create the appropriate signal objects upon
/// the XML description.
///
/// @ingroup Parser
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

#include <pugixml.hpp>

#include "SignalFactory.h"

namespace PARSER
{
    /// The class stores XML signal creation parameters.

    /// The XML description class.
    class XmlDescription
    {
        public:
            /// The XML signal class constructor.
            ///
            /// Creates the XML signal.
            ///
            /// @param rNode The main XML node.
            XmlDescription(const pugi::xml_node &rNode);

            /// Returns the regular expression used to create the signal.
            const std::string &GetRegex() const;

            /// Returns the timestamp tag value.
            const std::string &GetTimestamp() const;

            /// Returns the name tag value.
            const std::string &GetName() const;

            /// Returns the value tag value.
            const std::string &GetValue() const;

            /// Returns the size tag value.
            const std::string &GetSize() const;

        private:
            /// Stores the regular expression needed to create the signal.
            /// The XML line tag value.
            std::string m_RegexLine;

            /// Stores the XML timestamp tag value.
            std::string m_Timestamp;

            /// Stores the XML name tag value.
            std::string m_Name;

            /// Stores the XML value tag value.
            std::string m_Value;

            /// Stores the XML size tag value.
            std::string m_Size;
    };

    /// The class implements the factory method design pattern to build
    /// different types of signals based on the provided XML description.

    /// The XML factory class.
    class XmlSignalFactory : public SignalFactory
    {
        public:

            /// The XML signal factory constructor.
            ///
            /// @param rSignalDescriptorRegistry The signal descriptors registry.
            /// @param rXmlFileName The name of the XML file specifying the user log syntax.
            XmlSignalFactory(SIGNAL::SignalDescriptorRegistry &rSignalDescriptorRegistry,
                             const std::string &rXmlFileName);
    };
}
