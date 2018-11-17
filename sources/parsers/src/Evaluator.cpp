/// @file parsers/src/Evaluator.cpp
///
/// The class provides means for evaluating user format expressions.
///
/// @par Full Description
/// The class provides means for evaluating user format expressions.
/// It is a facade to Flex/Bison generated expression evaluators.
///
/// @ingroup Parser
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

#include <sstream>

#include "Evaluator.h"

#undef yyFlexLexer
/// Decimal lexer definition.
#define yyFlexLexer DecimalFlexLexer
#include <FlexLexer.h>
#include "DecimalScanner.h"

#undef yyFlexLexer
/// Float lexer definition.
#define yyFlexLexer FloatFlexLexer
#include <FlexLexer.h>
#include "FloatScanner.h"

#undef yyFlexLexer
/// String lexer definition.
#define yyFlexLexer StringFlexLexer
#include <FlexLexer.h>
#include "StringScanner.h"

PARSER::Evaluator::Evaluator(const std::string &rSourceName) :
    m_rSourceName(rSourceName),
    m_Context(nullptr, 0)
{
}

void PARSER::Evaluator::ParseDecimalString(const std::string &input)
{
    std::istringstream iss(input);
    if (!ParseDecimalStream(iss))
    {
        throw PARSER::EXCEPTIONS::ParsingError(ParsingErrorMessage(input));
    }
    m_Expression = input;
}

void PARSER::Evaluator::ParseFloatString(const std::string &input)
{
    std::istringstream iss(input);
    if (!ParseFloatStream(iss))
    {
        throw PARSER::EXCEPTIONS::ParsingError(ParsingErrorMessage(input));
    }
    m_Expression = input;
}

void PARSER::Evaluator::ParseStringString(const std::string &input)
{
    std::istringstream iss(input);
    if (!ParseStringStream(iss))
    {
        throw PARSER::EXCEPTIONS::ParsingError(ParsingErrorMessage(input));
    }
    m_Expression = input;
}

void PARSER::Evaluator::SetContext(std::smatch *pGroups, uint64_t lineNo)
{
    m_Context.Set(pGroups, lineNo);
}

PARSER::ExpressionContext &PARSER::Evaluator::GetContext() const
{
    return m_Context;
}

std::string PARSER::Evaluator::EvaluateDouble() const
{
    std::string stringValue;
    try
    {
        stringValue = m_Context.GetExpression()->EvaluateDouble().GetFloatString();
    }
    catch (const EXCEPTIONS::EvaluatorException &evaluatorError)
    {
        throw PARSER::EXCEPTIONS::EvaluatorException(EvaluationErrorMessage(evaluatorError.what()));
    }

    return stringValue;
}

uint64_t PARSER::Evaluator::EvaluateUint() const
{
    try
    {
        return m_Context.GetExpression()->EvaluateUint().GetValue();
    }
    catch (const PARSER::EXCEPTIONS::EvaluatorException &evaluatorError)
    {
        throw PARSER::EXCEPTIONS::EvaluatorException(EvaluationErrorMessage(evaluatorError.what()));
    }
}

std::string PARSER::Evaluator::EvaluateString() const
{
    try
    {
        return m_Context.GetExpression()->EvaluateString();
    }
    catch (const PARSER::EXCEPTIONS::EvaluatorException &evaluatorError)
    {
        throw PARSER::EXCEPTIONS::EvaluatorException(EvaluationErrorMessage(evaluatorError.what()));
    }
}

bool PARSER::Evaluator::ParseDecimalStream(std::istream &in)
{
    DecimalScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(true);
    #endif
    m_pDecimalLexer = &scanner;

    DecimalParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(1);
    #endif
    return (parser.parse() == 0);
}

bool PARSER::Evaluator::ParseFloatStream(std::istream &in)
{
    FloatScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(true);
    #endif
    m_pFloatLexer = &scanner;

    FloatParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(1);
    #endif
    return (parser.parse() == 0);
}

bool PARSER::Evaluator::ParseStringStream(std::istream &in)
{
    StringScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(true);
    #endif
    m_pStringLexer = &scanner;

    StringParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(1);
    #endif
    return (parser.parse() == 0);
}

std::string PARSER::Evaluator::ParsingErrorMessage(const std::string &parsedExpression) const
{
    std::string arrows(m_SyntaxErrorIndex  - 1, '-');
    arrows += '^';
    std::string errorMessage(parsedExpression + '\n' + arrows + '\n');
    return errorMessage;
}

std::string PARSER::Evaluator::EvaluationErrorMessage(const std::string &evaluationError) const
{
    return std::string ("Expression: " + m_Expression + "\n" + evaluationError);
}
