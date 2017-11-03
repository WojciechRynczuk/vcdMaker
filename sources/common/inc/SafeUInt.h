/// @file common/inc/SafeUInt.h
///
/// Safe integer class template.
///
/// @par Full Description
/// Safe integer class overrides arthmetic operators throwing
/// exceptions on the overflow.
///
/// @ingroup Generic
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

/// @defgroup Generic Generic
///
/// @brief Generic classes.
///
/// @par Full Description
/// The group contains classes which could be used anywhere else.

#include <cstdint>
#include <limits>
#include <iostream>
#include <stdexcept>

/// A safe unsigned integer class.
/// The overridden arthmetic operators throw exceptions on the overflow.
template<class T> class SafeUInt
{
    public:
        /// The safe integer constructor.
        ///
        /// @param value The value of the integer.
        SafeUInt(T value) :
            m_Value(value)
        {
        }

        /// The default constructor.
        ///
        /// By default the integer is set to 0.
        SafeUInt() :
            m_Value(0)
        {
        }

        /// Returns the integer value.
        T GetValue() const
        {
            return m_Value;
        }

        /// Overrides 'equal to' operator.
        bool operator==(const SafeUInt<T> &rhs) const
        {
            return m_Value == rhs.GetValue();
        }

        /// Overrides 'not equal to' operator.
        bool operator!=(const SafeUInt<T> &rhs) const
        {
            return !(*this == rhs);
        }

        /// Overrides 'greater than' operator.
        bool operator>(const SafeUInt<T> &rhs) const
        {
            return (m_Value > rhs.GetValue());
        }

        /// Overrides 'less than' operator.
        bool operator<(const SafeUInt<T> &rhs) const
        {
            return (m_Value < rhs.GetValue());
        }

        /// Overrides the addition operator '+'.
        SafeUInt<T> operator+(const SafeUInt<T> &rhs) const
        {
            if ( (std::numeric_limits<T>::max() - m_Value) < rhs.GetValue())
            {
                throw std::out_of_range("");
            }
            return SafeUInt<T>(m_Value + rhs.GetValue());
        }

        /// Overrides the addition operator '+='.
        SafeUInt<T> &operator+=(const SafeUInt<T> &rhs)
        {
            if ((std::numeric_limits<T>::max() - m_Value) < rhs.GetValue())
            {
                throw std::out_of_range("");
            }
            m_Value += rhs.GetValue();
            return *this;
        }

        /// Overrides the substraction operator '-'.
        SafeUInt<T> operator-(const SafeUInt<T> &rhs) const
        {
            if (m_Value < rhs.GetValue())
            {
                throw std::out_of_range("");
            }
            return SafeUInt<T>(m_Value - rhs.GetValue());
        }

        /// Overrides the substraction operator '-='.
        SafeUInt<T> &operator-=(const SafeUInt<T> &rhs)
        {
            if (m_Value < rhs.GetValue())
            {
                throw std::out_of_range("");
            }
            m_Value -= rhs.GetValue();
            return *this;
        }

        /// Overrides the multiplication operator '*'.
        SafeUInt<T> operator*(uint64_t rhs) const
        {
            if (m_Value)
            {
                if ((std::numeric_limits<T>::max() / m_Value) < rhs)
                {
                    throw std::out_of_range("");
                }
            }
            return SafeUInt<T>(m_Value * rhs);
        }

        /// Overrides the multiplication operator '*= uint64_t'.
        SafeUInt<T> &operator*=(uint64_t rhs)
        {
            if (m_Value)
            {
                if ((std::numeric_limits<T>::max() / m_Value) < rhs)
                {
                    throw std::out_of_range("");
                }
            }
            m_Value *= rhs;
            return *this;
        }

        /// Overrides the multiplication operator '* double'.
        SafeUInt<T> operator*(double rhs) const
        {
            if (m_Value)
            {
                if ((std::numeric_limits<T>::max() / m_Value) < rhs)
                {
                    throw std::out_of_range("");
                }
            }
            return SafeUInt<T>(static_cast<T>(m_Value * rhs));
        }

        /// Overrides the multiplication operator '*= double'.
        SafeUInt<T> &operator*=(double rhs)
        {
            if (m_Value)
            {
                if ((std::numeric_limits<T>::max() / m_Value) < rhs)
                {
                    throw std::out_of_range("");
                }
            }
            m_Value *= rhs;
            return *this;
        }

        /// Overrides the division operator '/'.
        SafeUInt<T> operator/(uint64_t rhs) const
        {
            return SafeUInt<T>(m_Value / rhs);
        }

        /// Overrides the division operator '=/'.
        SafeUInt<T> &operator/=(uint64_t rhs)
        {
            m_Value /= rhs;
            return *this;
        }

        /// Returns the maximum type value.
        static SafeUInt<T> max()
        {
            return SafeUInt<T>(std::numeric_limits<T>::max());
        }

        /// Overrides the output stream operator.
        template<T> friend std::ostream &operator<<(std::ostream &out, SafeUInt<T> &ts);

        /// Overrides the multiplication operator.
        template<T> friend SafeUInt<T> operator*(uint64_t lhs, const SafeUInt<T> &rhs);

    private:

        /// The unsigned integer value.
        T m_Value;
};
