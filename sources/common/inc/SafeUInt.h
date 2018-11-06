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
/// @par Copyright (c) 2018 vcdMaker team
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
        SafeUInt() = default;

        /// Returns the integer value.
        T GetValue() const
        {
            return m_Value;
        }

        /// Overrides the addition operator '+='.
        SafeUInt<T> &operator+=(const SafeUInt<T> &rhs)
        {
            if ((std::numeric_limits<T>::max() - m_Value) < rhs.GetValue())
            {
                throw std::out_of_range("Arthmetic overflow");
            }
            m_Value += rhs.GetValue();
            return *this;
        }

        /// Overrides the substraction operator '-='.
        SafeUInt<T> &operator-=(const SafeUInt<T> &rhs)
        {
            if (m_Value < rhs.GetValue())
            {
                throw std::out_of_range("Arthmetic underflow");
            }
            m_Value -= rhs.GetValue();
            return *this;
        }

        /// Overrides the multiplication operator '*='.
        SafeUInt<T> &operator*=(const SafeUInt<T> &rhs)
        {
            auto [smaller, larger] = std::minmax(m_Value, rhs.m_Value);

            if (larger > 0)
            {
                if ((std::numeric_limits<T>::max() / larger) < smaller)
                {
                    throw std::out_of_range("Arthmetic overflow");
                }
            }
            m_Value *= rhs.m_Value;
            return *this;
        }

        /// Overrides the division operator '=/'.
        SafeUInt<T> &operator/=(const SafeUInt<T> &rhs)
        {
            m_Value /= rhs.m_Value;
            return *this;
        }

        /// Returns the maximum type value.
        static constexpr SafeUInt<T> max()
        {
            return SafeUInt<T>(std::numeric_limits<T>::max());
        }

        /// Overrides the output stream operator.
        template<class Y> friend std::ostream &operator<<(std::ostream &out, SafeUInt<Y> &ts);

    private:

        /// The unsigned integer value.
        T m_Value = 0;
};

/// Overrides 'equal to' operator.
template<class T>  bool operator==(const SafeUInt<T> &lhs, const SafeUInt<T> &rhs)
{
    return lhs.GetValue() == rhs.GetValue();
}

/// Overrides 'not equal to' operator.
template<class T>  bool operator!=(const SafeUInt<T> &lhs, const SafeUInt<T> &rhs)
{
    return !(lhs == rhs);
}

/// Overrides 'greater than' operator.
template<class T>  bool operator>(const SafeUInt<T> &lhs, const SafeUInt<T> &rhs)
{
    return (lhs.GetValue() > rhs.GetValue());
}

/// Overrides 'less than' operator.
template<class T>  bool operator<(const SafeUInt<T> &lhs, const SafeUInt<T> &rhs)
{
    return (lhs.GetValue() < rhs.GetValue());
}

/// Overrides the addition operator '+'.
template<class T>  SafeUInt<T> operator+(SafeUInt<T> lhs, const SafeUInt<T> &rhs)
{
    lhs += rhs;
    return lhs;
}

/// Overrides the substraction operator '-'.
template<class T>  SafeUInt<T> operator-(SafeUInt<T> lhs, const SafeUInt<T> &rhs)
{
    lhs -= rhs;
    return lhs;
}

/// Overrides the multiplication operator '*'.
template<class T>  SafeUInt<T> operator*(SafeUInt<T> lhs, const SafeUInt<T> &rhs)
{
    lhs *= rhs;
    return lhs;
}

/// Overrides the multiplication operator '/'.
template<class T>  SafeUInt<T> operator/(SafeUInt<T> lhs, const SafeUInt<T> &rhs)
{
    lhs /= rhs;
    return lhs;
}

/// Overrides the output stream operator.
template<class Y> std::ostream &operator<<(std::ostream &out, const SafeUInt<Y> &ts)
{
    out << ts.GetValue();
    return out;
}
