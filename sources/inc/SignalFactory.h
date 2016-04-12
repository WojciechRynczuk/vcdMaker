/// @file SignalFactory.h
///
/// The signal factory class.
///
/// @par Full Description
/// The signal factory object creates the appropriate signal objects.
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

/// @defgroup Construction Construction
///
/// @brief The group provides means for creating different signal objects.
///
/// @par Full Description
/// The subsystem is responsible for building the appropraite signal
/// objects. It deploys the factory method design pattern.

#include <string>
#include <vector>

#include "Signal.h"
#include "SignalCreator.h"

namespace CONSTRUCTION
{

    /// The signal factory base class.
    ///
    /// The class implements the factory method design pattern so as to handle
    /// building different types of signals.
    class SignalFactory
    {
        public:

            /// The signal factory default constructor.
            ///
            /// The constructor initializes the basic signal's properties like the name,
            /// the size and the type.
            SignalFactory();

            /// The destructor.
            ~SignalFactory();

            /// Creates the appropriate signal object.
            ///
            /// Returns the pointer to the appropriate signal object.
            /// Or NULL if it couldn't be created.
            SIGNAL::Signal *Create(std::string &logLine);

        private:

            /// The table of pointers to signal creators.
            std::vector<SignalCreator *> m_vpSignalCreators;
    };

}
