%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_UP       "up"
%token            KW_DOWN     "down"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"
%token            KW_HEADING  "heading"
%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_POSITION "position"

%token            KW_HOME     "home"
%token            KW_COLOR    "color"
%token            KW_PRINT    "print"
%token            KW_REPEAT   "repeat"
%token            KW_BLOCK    "block"
%token            KW_PROC     "proc"
%token            KW_CALL     "call"

%token            KW_RED      "red"
%token            KW_GREEN    "green"
%token            KW_BLUE     "blue"
%token            KW_CYAN     "cyan"
%token            KW_MAGENTA  "magenta"
%token            KW_YELLOW   "yellow"
%token            KW_BLACK    "black"
%token            KW_GRAY     "gray"
%token            KW_WHITE    "white"

/* TODO: add other tokens */

%type <node> unit cmds cmd expr color block

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP expr                  { $$ = make_cmd_up($2); }
  | KW_DOWN expr                { $$ = make_cmd_down($2); }
  | KW_RIGHT expr               { $$ = make_cmd_right($2); }
  | KW_LEFT expr                { $$ = make_cmd_left($2); }
  | KW_HEADING expr             { $$ = make_cmd_heading($2); }
  | KW_FORWARD expr             { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr            { $$ = make_cmd_backward($2); }
  | KW_POSITION expr ',' expr   { $$ = make_cmd_position($2, $4); }
  | KW_HOME                     { $$ = make_cmd_home(); }
  | KW_COLOR expr               { $$ = make_cmd_color($2); } /* Can be subject to change */
  | KW_PRINT expr               { $$ = make_cmd_print($2); }
  | color
  | block
;

expr:
    VALUE             { $$ = make_expr_value($1); }
  | NAME              { $$ = make_expr_name($1); }
    /* TODO: add identifier */
;

block:
    '{' cmds '}'      { $$ = make_cmd_block($2); }
;

color:
    KW_COLOR expr ',' expr ',' expr     { $$ = make_color_rgb($2, $4, $6); }
  | KW_COLOR KW_RED                     { $$ = make_color_word("red"); }
  | KW_COLOR KW_GREEN                   { $$ = make_color_word("green"); }
  | KW_COLOR KW_BLUE                    { $$ = make_color_word("blue"); }
  | KW_COLOR KW_CYAN                    { $$ = make_color_word("cyan"); }
  | KW_COLOR KW_MAGENTA                 { $$ = make_color_word("magenta"); }
  | KW_COLOR KW_YELLOW                  { $$ = make_color_word("yellow"); }
  | KW_COLOR KW_GRAY                    { $$ = make_color_word("gray"); }
  | KW_COLOR KW_WHITE                   { $$ = make_color_word("white"); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
