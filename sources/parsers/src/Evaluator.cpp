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
    m_Context(NULL, 0),
    m_rSourceName(rSourceName)
{
}

bool PARSER::Evaluator::ParseDecimalString(const std::string &input)
{
    std::istringstream iss(input);
    return ParseDecimalStream(iss);
}

bool PARSER::Evaluator::ParseFloatString(const std::string &input)
{
    std::istringstream iss(input);
    return ParseFloatStream(iss);
}

bool PARSER::Evaluator::ParseStringString(const std::string &input)
{
    std::istringstream iss(input);
    return ParseStringStream(iss);
}

void PARSER::Evaluator::SetContext(const std::smatch *pGroups, uint64_t lineNo) const
{
    m_Context.Set(pGroups, lineNo);
}

PARSER::ExpressionContext &PARSER::Evaluator::GetContext() const
{
    return m_Context;
}

double PARSER::Evaluator::EvaluateDouble() const
{
    return m_Context.GetExpression()->EvaluateDouble();
}

uint64_t PARSER::Evaluator::EvaluateUint() const
{
    return m_Context.GetExpression()->EvaluateUint().GetValue();
}

std::string PARSER::Evaluator::EvaluateString() const
{
    return m_Context.GetExpression()->EvaluateString();
}

bool PARSER::Evaluator::ParseDecimalStream(std::istream &in)
{
    DecimalScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(false);
    #endif
    m_pDecimalLexer = &scanner;

    DecimalParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(false);
    #endif
    return (parser.parse() == 0);
}

bool PARSER::Evaluator::ParseFloatStream(std::istream &in)
{
    FloatScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(false);
    #endif
    m_pFloatLexer = &scanner;

    FloatParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(false);
    #endif
    return (parser.parse() == 0);
}

bool PARSER::Evaluator::ParseStringStream(std::istream &in)
{
    StringScanner scanner(&in);
    #if defined(PARSER_DEBUG)
    scanner.set_debug(false);
    #endif
    m_pStringLexer = &scanner;

    StringParser parser(*this);
    #if defined(PARSER_DEBUG)
    parser.set_debug_level(false);
    #endif
    return (parser.parse() == 0);
}
