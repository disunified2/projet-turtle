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

%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_POSITION "position"

%token            KW_HOME     "home"
%token            KW_COLOR    "color"
%token            KW_PRINT    "print"

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
    KW_FORWARD expr             { $$ = make_cmd_forward($2); }
  | KW_BACKWORD expr            { $$ = make_cmd_backward($2); }
  | KW_POSITION expr ',' expr   { $$ = make_cmd_position($2, $4); }
  | KW_HOME                     { $$ = make_cmd_home(); }
  | KW_COLOR expr               { $$ = make_cmd_color($2); } /* Can be subject to change */
  | KW_PRINT expr               { $$ = make_cmd_print($2); }
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
