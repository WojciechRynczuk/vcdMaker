/// @file CliParser.h
///
/// The base class of the CLI parser.
///
/// @par Full Description
/// The base class of the simple Command Line Interface parser.
///
/// @ingroup CLI
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

#include <algorithm>

#include "CliParser.h"

std::string CLI::CliParser::GetParamValue(const std::string &param) const
{
    auto it = std::find(m_Parameters.cbegin(), m_Parameters.cend(), param);

    if ((it != m_Parameters.end()) && (it != m_Parameters.end() - 1))
    {
        return *(++it);
    }
    else
    {
        return {};
    }
}

bool CLI::CliParser::CheckParam(const std::string &param) const
{
    return (std::find(m_Parameters.cbegin(), m_Parameters.cend(), param) != m_Parameters.end());
}

bool CLI::CliParser::Validate() const
{
    if (m_Parameters.size() < 2)
    {
        OneLineHelp();
        return false;
    }

    if (CheckParam("-h"))
    {
        Help();
        return false;
    }

    return Validator();
}
