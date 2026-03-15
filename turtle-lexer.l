%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
LETTER [A-Z]
WORD [LETTER][LETTER|DIGIT]*

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
"proc"                { return KW_PROC; }
"call"                { return KW_CALL; }
"set"                 { return KW_SET; }
"repeat"              { return KW_REPEAT; }

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
","                 { return ','; }

[-]*{DIGIT}+          { yylval.value = strtod(yytext, NULL); return VALUE; }
{WORD}                { yylval.name = strdup(yytext); return NAME; }

[A-Z]+[A-Z0-9]        { yylval.name = strdup(yytext); return NAME; }

"#".*                 /* comment */
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
