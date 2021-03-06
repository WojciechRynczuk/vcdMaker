/// @file parsers/inc/StringScanner.h
///
/// A user defined string scanner class.
///
/// @par Full Description
/// A user defined string scanner class.
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

#pragma once

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL
/// YY_DECL parser macro.
#define    YY_DECL                               \
    PARSER::StringParser::token_type            \
    PARSER::StringScanner::lex(                 \
    PARSER::StringParser::semantic_type* yylval,\
    PARSER::StringParser::location_type* yylloc \
                              )
#endif

#ifndef yyFlexLexer
/// String lexer type.
#define yyFlexLexer StringFlexLexer
#include <FlexLexer.h>
#endif

#include "StringParser.hpp"

namespace PARSER
{

    /** StringScanner is a derived class to add some extra function to the scanner
     * class. Flex itself creates a class named yyFlexLexer, which is renamed using
     * macros to StringFlexLexer. However we change the context of the generated
     * yylex() function to be contained within the StringScanner class. This is required
     * because the yylex() defined in StringFlexLexer has no parameters. */
    class StringScanner : public StringFlexLexer
    {
        public:
            /** Create a new scanner object. The streams arg_yyin and arg_yyout default
             * to cin and cout, but that assignment is only made when initializing in
             * yylex(). */
            StringScanner(std::istream *arg_yyin = 0,
                          std::ostream *arg_yyout = 0);

            /** Required for virtual functions */
            virtual ~StringScanner();

            /** This is the main lexing function. It is generated by flex according to
             * the macro declaration YY_DECL above. The generated bison parser then
             * calls this virtual function to fetch new tokens. */
            virtual StringParser::token_type lex(
                StringParser::semantic_type *yylval,
                StringParser::location_type *yylloc
            );

            #if defined(PARSER_DEBUG)
            /** Enable debug output (via arg_yyout) if compiled into the scanner. */
            void set_debug(bool b);
            #endif
    };

}
