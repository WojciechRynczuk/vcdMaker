/// @file common/src/DefaultSignalFactory.cpp
///
/// The default signal factory class.
///
/// @par Full Description
/// The standard vcdMaker signal factory.
///
/// @ingroup Parser
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

#include "DefaultSignalFactory.h"
#include "EventSignalCreator.h"
#include "FSignalCreator.h"
#include "ISignalCreator.h"

PARSER::DefaultSignalFactory::DefaultSignalFactory() :
    SignalFactory()
{
    m_vpSignalCreators.push_back(std::make_unique<ISignalCreator>());
    m_vpSignalCreators.push_back(std::make_unique<FSignalCreator>());
    m_vpSignalCreators.push_back(std::make_unique<EventSignalCreator>());
}

