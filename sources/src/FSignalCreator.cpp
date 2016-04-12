/// @file FSignalCreator.h
///
/// The real signal creator.
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

#include "stdafx.h"

#include "FSignalCreator.h"
#include "FSignal.h"

SIGNAL::Signal *CONSTRUCTION::FSignalCreator::Create(std::string &logLine)
{
    std::cmatch result;
    SIGNAL::Signal *pSignal = NULL;
    if (true == std::regex_search(logLine.begin(), logLine.end(), m_SignalRegEx))
    {
        //Parse the log line
        std::regex_search(logLine.c_str(), result, m_SignalRegEx);

        //Create the signal object
        pSignal = new SIGNAL::FSignal(result[2].str(), std::stoll(result[1].str()), std::stod(result[3].str(), NULL));
    }
    return pSignal;
}
