/** Contains the float expression Bison parser source.
    
    Copyright (c) 2018 vcdMaker team
    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

%{ /*** C/C++ Declarations ***/

#include "ExpressionNode.h"
#include "FloatNode.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* Add debug output code to generated parser. disable this for release versions. */
/* %debug */

/* Start symbol is named "start". */
%start start

/* Write out a header file containing the token defines. */
%defines

/* Use newer C++ skeleton file. */
%skeleton "lalr1.cc"

/* Namespace to enclose parser in. */
%name-prefix="PARSER"

/* Set the parser's class identifier. */
%define "parser_class_name" "FloatParser"

/* Keep track of the current position within the input. */
%locations

/* The evaluator is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Evaluator& evaluator }

/* Verbose error messages. */
%error-verbose

 /*** START - Specify the grammar's tokens ***/

%union {
    double                        doubleValue;
    std::string*                  pString;
    class PARSER::ExpressionNode* pExprNode;
}

%token               END 0   "end of stream"
%token <doubleValue> DOUBLE  "Double"
%token <pString>     FLT     "flt"

%type <pExprNode>   constant variable atomexpr unaryexpr mulexpr addexpr expr

%destructor { delete $$; } FLT
%destructor { delete $$; } constant
%destructor { delete $$; } variable
%destructor { delete $$; } atomexpr
%destructor { delete $$; } unaryexpr
%destructor { delete $$; } mulexpr
%destructor { delete $$; } addexpr
%destructor { delete $$; } expr

 /*** END - Specify the grammar's tokens ***/

%{

#include "Evaluator.h"
#include "FloatScanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex evaluator.m_pFloatLexer->lex

%}

%% /*** Grammar Rules ***/

constant    :   DOUBLE
            {
                $$ = new FNConstant(evaluator.GetContext(), $1);
            }

variable    :   FLT
            {
                $$ = new FNFlt(evaluator.GetContext(), *$1);
                delete $1;
            }
            
atomexpr    :   constant
            {
                $$ = $1;
            }
            |   variable
            {
                $$ = $1;
            }
            |   '(' expr ')'
            {
                $$ = $2;
            }

unaryexpr   :   atomexpr
            {
                $$ = $1;
            }
            |   '+' atomexpr
            {
                $$ = $2;
            }
            |   '-' atomexpr
            {
                $$ = new FNNegate(evaluator.GetContext(), $2);
            }

mulexpr     :   unaryexpr
            {
                $$ = $1;
            }
            |   mulexpr '*' unaryexpr
            {
                $$ = new FNMultiply(evaluator.GetContext(), $1, $3);
            }
            |   mulexpr '/' unaryexpr
            {
                $$ = new FNDivide(evaluator.GetContext(), $1, $3);
            }

addexpr     :   mulexpr
            {
                $$ = $1;
            }
            |   addexpr '+' mulexpr
            {
                $$ = new FNAdd(evaluator.GetContext(), $1, $3);
            }
            | addexpr '-' mulexpr
            {
                $$ = new FNSubtract(evaluator.GetContext(), $1, $3);
            }

expr        :   addexpr
            {
                $$ = $1;
            }


start       : /* empty */
            | start expr END
            {
                evaluator.GetContext().SetExpression($2);
            }

%% /*** Additional Code ***/

void PARSER::FloatParser::error(const FloatParser::location_type& l,
                                const std::string& m)
{
    evaluator.SetSyntaxErrorIndex(l.begin.column);
}
