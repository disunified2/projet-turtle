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

%token            KW_UP  "up"
%token            KW_DOWN  "down"
%token            KW_RIGHT  "right"
%token            KW_LEFT  "left"
%token            KW_HEADING  "heading"
%token            KW_FORWARD  "forward"
/* TODO: add other tokens */

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP expr        { $$ = make_cmd_up($2); }
  | KW_DOWN expr   { $$ = make_cmd_down($2); }
  | KW_RIGHT expr   { $$ = make_cmd_right($2); }
  | KW_LEFT expr   { $$ = make_cmd_left($2); }
  | KW_HEADING expr   { $$ = make_cmd_heading($2); }
  | KW_FORWARD expr   { $$ = make_cmd_forward($2); }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
