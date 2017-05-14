/// @file VcdWarning.h
///
/// The warning exception class.
///
/// @par Full Description
/// The module defines the warning exception class.
///
/// @ingroup Exception
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

#include <iostream>

#include "VcdException.h"
#include "VcdExceptionList.h"

namespace EXCEPTION
{
    /// The base warning exception class.
    /// To be thrown when a problematic but recoverable condition occurs.

    /// The warning exception base class.
    class VcdWarning : public VcdException
    {
        /// The warning message.
        const std::string m_Message;
        public:
            /// The warning constructor.
            ///
            /// @param id The warning ID.
            /// @param rMessage The warning message.
            VcdWarning(uint32_t id, const std::string& rMessage) : 
                VcdException(id),
                m_Message(rMessage)
            {}

            /// @copydoc VcdException::GetType
            const std::string GetType() const
            {
                return "Warning";
            }

            /// The default warning destructor.
            ///
            /// It just returns the warning.
            ~VcdWarning()
            {
                std::cout << this->GetMessage();
            }

            /// @copydoc VcdException::GetInfo
            const std::string GetInfo() const
            {
                return std::string(m_Message);
            }
    };
}


