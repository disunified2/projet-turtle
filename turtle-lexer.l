%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]

%%

"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"right"               { return KW_RIGHT; }
"rt"                  { return KW_RIGHT; }
"left"                { return KW_LEFT; }
"lt"                  { return KW_LEFT; }
"heading"             { return KW_HEADING; }
"hd"                  { return KW_HEADING; }
"forward"             { return KW_FORWARD; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
