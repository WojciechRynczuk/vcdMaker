/// @file VcdException.h
///
/// The VCD exception base class.
///
/// @par Full Description
/// The base class for VCD errors and warnings.
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

/// @defgroup Exception Exception
///
/// @brief Errors and warnings handling.
///
/// @par Full Description
/// The module provides means for handling errors and warnings.

#include <stdexcept>
#include <sstream>
#include <iomanip>

/// The vcdMaker exceptions.
namespace EXCEPTION
{
    /// The base exception class. The error and warning classes
    /// inherit from it.

    /// The base exception class.
    class VcdException : public std::runtime_error
    {
            /// The exception ID to identify the error or warning.
            /// The ID is referenced by the user manual.
            const uint32_t m_ExceptionId;

        public:
            /// The exception constructor.
            /// It initializes the ID of the exception.
            ///
            /// @param id The ID of the exception.
            VcdException(uint32_t id) :
                std::runtime_error("vcdException"),
                m_ExceptionId(id)
            {
            }

            /// The destructor.
            virtual ~VcdException();

            /// Returns the formatted exception description.
            const std::string GetMessage() const
            {
                return "[" + GetType() + " " + GetExceptionNumber() + "]: " + GetInfo() + '\n';
            }

        protected:
            /// Returns the description of the exception.
            virtual const std::string GetType() const = 0;

            /// Returns the exception specific description.
            virtual const std::string GetInfo() const = 0;

        private:
            /// Returns the formatted exception number.
            const std::string GetExceptionNumber() const
            {
                std::ostringstream exceptionValue;

                exceptionValue << std::setfill('0') << std::setw(4) << m_ExceptionId;
                return exceptionValue.str();
            }
    };

    inline VcdException::~VcdException() = default;
}
