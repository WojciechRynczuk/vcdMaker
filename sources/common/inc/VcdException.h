/// @file common/inc/VcdException.h
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
#include <string>

#include "VcdExceptionList.h"

/// The vcdMaker exceptions.
namespace EXCEPTION
{
    /// The base exception class.
    /// The base exception class. The error and warning classes
    /// inherit from it.
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
            /// @param rMessage The exception warning.
            VcdException(uint32_t id, const std::string &rMessage) :
                std::runtime_error(rMessage),
                m_ExceptionId(id)
            {
            }

            /// Returns the ID of the exception.
            uint32_t GetId() const
            {
                return m_ExceptionId;
            }
    };

    /// @brief The logic exception base class.
    /// The logic exception class shall be used
    /// to handle internal logic errors.
    class VcdLogicException : public VcdException
    {
        public:
            /// The logic error constructor.
            ///
            /// @param id The error ID.
            /// @param rMessage The error message.
            VcdLogicException(uint32_t id, const std::string &rMessage) :
                VcdException(id,
                             rMessage +
                             " Please log an issue on https://github.com/WojciechRynczuk/vcdMaker." +
                             " Provide the application version, parameters and input files if possible.")
            {}
    };

    /// @brief The exception for handling 'too small vector' warnings.
    /// It shall be used when too small vector is being created.
    class TooSmallVector : public std::runtime_error
    {
        public:
            /// The exception constructor.
            ///
            /// @param value The value of the signal.
            /// @param size The size of the vector to hold the value.
            TooSmallVector(uint64_t value, uint64_t size)
                : std::runtime_error("Value " +
                                     std::to_string(value) +
                                     " exceeds the " +
                                     std::to_string(size) +
                                     "-bit size of the vector. Dropping the signal.")
            {}
    };
}
