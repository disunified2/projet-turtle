#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_RANDOM,
  FUNC_SIN,
  FUNC_SQRT,
  FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};



struct ast_node *make_expr_value(double value);

struct ast_node *make_expr_name(char *name);

struct ast_node *make_cmd_up();

struct ast_node *make_cmd_down();

struct ast_node *make_cmd_right(struct ast_node *expr);

struct ast_node *make_cmd_left(struct ast_node *expr);

struct ast_node *make_cmd_heading(struct ast_node *expr);

struct ast_node *make_cmd_forward(struct ast_node *expr);

struct ast_node *make_cmd_backward(struct ast_node *expr);

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2);

struct ast_node *make_cmd_home();

struct ast_node *make_cmd_print(struct ast_node *expr);

struct ast_node *make_cmd_block(struct ast_node *cmd);

struct ast_node *make_cmd_set(struct ast_node *var, struct ast_node *value);

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *cmd);

struct ast_node *make_cmd_call(struct ast_node *name);

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd);

// Internal functions
struct ast_node *make_func_sin(struct ast_node *expr);

struct ast_node *make_func_cos(struct ast_node *expr);

struct ast_node *make_func_tan(struct ast_node *expr);

struct ast_node *make_func_sqrt(struct ast_node *expr);

struct ast_node *make_func_random(struct ast_node *expr1, struct ast_node *expr2);

// Color nodes
struct ast_node *make_cmd_color(struct ast_node *expr);

struct ast_node *make_color_rgb(struct ast_node *r, struct ast_node *g, struct ast_node *b);

struct ast_node *make_color_word(char *word);


// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_node_destroy(struct ast_node *self);

void ast_destroy(struct ast *self);

struct proc {
  int nb_reps;
  int nb_blocks;
  struct ast_node **instructions;
};

struct proc_list {
  struct proc *procs;
  size_t size;
  size_t capacity;
};

//variable structure
struct var {
  char *name;
  double value;
};

//variable list structure
struct var_list {
  struct var *variables;
  size_t size;
  size_t capacity;
};

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;

  struct proc_list proc_list;
  struct var_list variable_list;
};

// create a procedure list
void proc_list_create(struct proc_list *self);

//destroy a procedure_list
void proc_list_destroy(struct proc_list *self);

// add a procedure to the list
void add_procedure(struct context *ctx/*, procedure*/);

// create a variable list
void var_list_create(struct var_list *self);

//destroy a variable_list
void var_list_destroy(struct var_list *self);

// add a variable to the list
void add_variable(struct context *ctx, char *name, double value);

// create an initial context
void context_create(struct context *self);

//destroy a context
void context_destroy(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);

#endif /* TURTLE_AST_H */
