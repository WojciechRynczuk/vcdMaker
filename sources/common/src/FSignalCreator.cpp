/// @file FSignalCreator.h
///
/// The real signal creator.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2016 vcdMaker team
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

#include "FSignalCreator.h"
#include "FSignal.h"

SIGNAL::Signal *PARSER::FSignalCreator::Create(const std::string &logLine,
                                               SIGNAL::SourceRegistry::HandleT sourceHandle) const
{
    std::smatch result;

    if (true == std::regex_search(logLine, result, m_SignalRegEx))
    {
        return new SIGNAL::FSignal(result[2].str(),
                                   std::stoll(result[1].str()),
                                   std::stod(result[3].str()),
                                   sourceHandle);
    }
    else
    {
        return nullptr;
    }
}
