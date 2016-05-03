/// @file SignalFactory.h
///
/// The signal factory class.
///
/// @par Full Description
/// The signal factory object creates the appropriate signal objects.
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

#include "SignalFactory.h"
#include "ISignalCreator.h"
#include "FSignalCreator.h"

CONSTRUCTION::SignalFactory::SignalFactory()
{
    // Create creators objects
    ISignalCreator *iMaker = new ISignalCreator();
    FSignalCreator *fMaker = new FSignalCreator();

    // Register creators
    m_vpSignalCreators.push_back(iMaker);
    m_vpSignalCreators.push_back(fMaker);
};

CONSTRUCTION::SignalFactory::~SignalFactory()
{
    // Creators iterator
    std::vector<SignalCreator *>::const_reverse_iterator it;

    //Destroy signal creators
    for (it = m_vpSignalCreators.crbegin(); it != m_vpSignalCreators.crend(); ++it)
    {
        delete *it;
    }
};

SIGNAL::Signal *CONSTRUCTION::SignalFactory::Create(std::string &logLine)
{
    // Creators iterator
    std::vector<SignalCreator *>::const_reverse_iterator rit;

    // Signal object pointer
    SIGNAL::Signal *pSignal = nullptr;

    // Try to use any of the available constructors
    for (rit = m_vpSignalCreators.crbegin(); (rit != m_vpSignalCreators.crend()) && (pSignal == nullptr); ++rit)
    {
        pSignal = (*rit)->Create(logLine);
    }
    return pSignal;
}
