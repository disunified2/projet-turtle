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
"fw"                  { return KW_FORWARD; }
"backward"            { return KW_BACKWARD; }
"bw"                  { return KW_BACKWARD; }
"position"            { return KW_POSITION; }
"pos"                 { return KW_POSITION; }
"home"                { return KW_HOME; }
"color"               { return KW_COLOR; }
"print"               { return KW_PRINT; }

"red"               { return KW_RED; }
"green"             { return KW_GREEN; }
"blue"              { return KW_BLUE; }
"cyan"              { return KW_CYAN; }
"magenta"           { return KW_MAGENTA; }
"yellow"            { return KW_YELLOW; }
"black"             { return KW_BLACK; }
"gray"              { return KW_GRAY; }
"white"             { return KW_WHITE; }

"{"                 { return '{'; }
"}"                 { return '}'; }

{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }

"#".*                 /* comment */
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
