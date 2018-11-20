/** Define the decimal expression Flex lexical scanner.

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

#include "DecimalNode.h"
#include "DecimalScanner.h"

/* Import the parser's token type into a local typedef. */
typedef PARSER::DecimalParser::token token;
typedef PARSER::DecimalParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* Enable c++ scanner class generation. */
%option c++

/* Change the name of the scanner class. Results in "DecimalFlexLexer". */
%option prefix="Decimal"

/* The manual says "somewhat more optimized". */
%option batch

/* Enable scanner to generate debug output. disable this for release versions. */
/* %option debug */

/* No support for include files is planned. */
%option yywrap nounput 

/* Let the scanner be fast. */
%option full

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

 /* Code to place at the beginning of yylex(). */
%{
    // reset location
    yylloc->step();
%}

 /*** Lexer rules ***/

[0-9]+ {
    yylval->integer = atoi(yytext);
    return token::INTEGER;
}

hex\([ ]*[0-9]+[ ]*\) {
    yylval->pString = new std::string(yytext, yyleng);
    return token::HEX;
}

dec\([ ]*[0-9]+[ ]*\) {
    yylval->pString = new std::string(yytext, yyleng);
    return token::DEC;
}

line\([ ]*\) {
    yylval->pString = new std::string(yytext, yyleng);
    return token::LINE;
}

 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

 /*** End of lexer rules ***/

%% /*** Additional Code ***/

namespace PARSER {

DecimalScanner::DecimalScanner(std::istream* in,
                               std::ostream* out)
    : DecimalFlexLexer(in, out)
{
}

DecimalScanner::~DecimalScanner()
{
}

/*
void DecimalScanner::set_debug(bool b)
{
    yy_flex_debug = b;
}
*/

}

/* This implementation of DecimalFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int DecimalFlexLexer::yylex()
{
    std::cerr << "in DecimalFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int DecimalFlexLexer::yywrap()
{
    return 1;
}
