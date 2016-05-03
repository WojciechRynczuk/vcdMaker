/// @file SignalCreator.h
///
/// The signal creator interface class.
///
/// @par Full Description
/// Every signal can be created differently. The class provides the
/// universal interface to create them.
///
/// @ingroup Construction
///
/// @par Copyright (c) 2016 Wojciech Rynczuk
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
#include <regex>

#include "Signal.h"

namespace CONSTRUCTION
{

    /// A base signal creator class.
    ///
    /// The class provides the interface to create the signal object.
    class SignalCreator
    {
        public:

            /// The signal creator constructor.
            ///
            /// The constructor initializes the regular expression member variable
            /// which will be matched against the log line.
            SignalCreator(char *signalRegEx) :
                m_SignalRegEx(signalRegEx)
            {
            }

            /// The destructor.
            virtual ~SignalCreator() = 0;

            /// Return the pointer to the newly created object or nullptr.
            ///
            /// It creates the integer signal object if the log line is valid and returns
            /// the pointer to the newly created object.
            /// If the log line is not matching the integer object specification
            /// then nullptr is returned.
            ///
            /// @param logLine The log line serving as the creation specification.
            /// @return Signal pointer if the object has been created or nullptr.
            virtual SIGNAL::Signal *Create(std::string &logLine) const = 0;

        protected:

            /// The RegEx matching the signal description.
            std::regex m_SignalRegEx;
    };

    inline SignalCreator::~SignalCreator() = default;

}
