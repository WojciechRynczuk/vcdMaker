/// @file common/src/SignalFactory.cpp
///
/// The signal factory class.
///
/// @par Full Description
/// The signal factory object creates the appropriate signal objects.
///
/// @ingroup Parser
///
/// @par Copyright (c) 2020 vcdMaker team
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
#include "EventSignalCreator.h"
#include "ISignalCreator.h"
#include "FSignalCreator.h"
#include "VcdException.h"
#include "EvaluatorExceptions.h"
#include "Logger.h"

PARSER::SignalFactory::SignalFactory() :
    m_vpSignalCreators()
{
}

std::vector<const SIGNAL::Signal*> PARSER::SignalFactory::Create(std::string &logLine,
                                                                 INSTRUMENT::Instrument::LineNumberT lineNumber,
                                                                 SIGNAL::SourceRegistry::HandleT sourceHandle) const
{
    if (m_vpSignalCreators.empty())
    {
        throw EXCEPTION::VcdException(EXCEPTION::Error::NO_SIGNALS_CREATORS,
                                      "No signals creators. Hint: Verify the correctness of the XML file specifying the user log format.");
    }

    std::vector<const SIGNAL::Signal *> vpSignals;

    for (const auto &creator : m_vpSignalCreators)
    {
        const SIGNAL::Signal *pSignal = nullptr;

        try
        {
            // Try to use creator.
            pSignal = creator->Create(logLine, lineNumber, sourceHandle);
        }
        catch (const PARSER::EXCEPTIONS::EvaluatorException &evaluatorError)
        {
            throw EXCEPTION::VcdException(EXCEPTION::Error::EXPRESSION_EVALUATION_ERROR,
                                          GetLogLineInfo(sourceHandle, lineNumber, logLine) +
                                          evaluatorError.what());
        }
        catch (const EXCEPTION::TooSmallVector &smallVector)
        {
            LOGGER::Logger::GetInstance().LogWarning(EXCEPTION::Warning::INSUFFICIENT_VECTOR_SIZE,
                                                     GetLogLineInfo(sourceHandle, lineNumber, logLine) +
                                                     smallVector.what());
        }
        catch (const std::regex_error &regexError)
        {
            throw EXCEPTION::VcdException(EXCEPTION::Error::REGEX_ERROR,
                                          regexError.what() +
                                          std::string("\nRegex: ") + creator->GetRegEx());
        }

        // If successful add created Signal to the returned vector.
        if (pSignal != nullptr)
        {
            vpSignals.push_back(pSignal);
        }
    }

    return vpSignals;
}

std::string PARSER::SignalFactory::GetLogLineInfo(SIGNAL::SourceRegistry::HandleT sourceHandle,
                                                  size_t lineNumber,
                                                  const std::string &logLine) const
{
    return "Evaluating " + SIGNAL::SourceRegistry::GetInstance().GetSourceName(sourceHandle) + ".\n" +
           "Line " + std::to_string(lineNumber) + ": " + logLine + "\n";
}
