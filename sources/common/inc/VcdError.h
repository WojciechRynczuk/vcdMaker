/// @file VcdError.h
///
/// The error exception class.
///
/// @par Full Description
/// The module defines the error exception class.
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

#include "VcdException.h"
#include "VcdExceptionList.h"

namespace EXCEPTION
{
    /// To error shall be thrown when an unrecoverable condition occurs.
    /// The class shall not be used directly.
    /// Use VcdExceptionGeneric or VcdErrorLogic.

    /// The error exception base class.
    class VcdError : public VcdException
    {
    public:
        /// @copydoc VcdException::VcdException
        VcdError(uint32_t id) : 
            VcdException(id)
        {}

        /// @copydoc VcdException::GetType
        const std::string GetType() const
        {
            return "Error";
        }

        /// The default VcdError destructor.
        ~VcdError()
        {
            // All errors shall terminate the application execution.
            exit(-1);
        }
    };

    /// The generic error exception class shall be
    /// used by runtime errors.

    /// The generic error exception base class.
    class VcdErrorGeneric : public VcdError
    {
        /// The error message.
        const std::string m_Message;
    public:
        /// The generic error constructor.
        ///
        /// @param id The error ID.
        /// @param rMessage The error message.
        VcdErrorGeneric(uint32_t id, const std::string& rMessage) : 
            VcdError(id), 
            m_Message(rMessage)
        {}

        /// @copydoc VcdException::GetInfo
        const std::string GetInfo() const
        {
            return std::string(m_Message);
        }
    };

    /// The logic error exception class shall
    /// be used to handle internal logic errors.

    /// The logic error exception base class.
    class VcdErrorLogic : public VcdError
    {
        /// The error message.
        const std::string m_Message;
    public:
        /// The logic error constructor.
        ///
        /// @param id The error ID.
        /// @param rMessage The error message.
        VcdErrorLogic(uint32_t id, const std::string &rMessage) : 
            VcdError(id),
            m_Message(rMessage)
        {}

        /// @copydoc VcdException::GetInfo
        const std::string GetInfo() const
        {
            return std::string(m_Message + " Please e-mail your application version, parameters and input files to vcdmaker@mail.com for analysis.");
        }
    };
}