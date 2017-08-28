/// @file common/inc/XmlFSignalCreator.h
///
/// The XML real signal creator.
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

#pragma once

#include "XmlSignalCreator.h"

namespace PARSER
{

    /// The class provides means to create XML real signal objects.

    /// The XML real signal creator class.
    class XmlFSignalCreator : public XmlSignalCreator
    {
        public:

            /// @copydoc XmlSignalCreator::XmlSignalCreator()
            XmlFSignalCreator(const std::string &rRegEx,
                const std::string &rTimestamp,
                const std::string &rName,
                const std::string &rValue,
                const std::string &rSize) :
                XmlSignalCreator(rRegEx, rTimestamp, rName, rValue, rSize)
            {
            }

            /// @copydoc SignalCreator::Create()
            virtual SIGNAL::Signal *Create(const std::string &rLogLine,
                                           SIGNAL::SourceRegistry::HandleT sourceHandle) const;

    };

}
