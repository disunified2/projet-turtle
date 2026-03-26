#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793
#define SQRT2 1.41421356237309504880;
#define SQRT3 1.7320508075688772935;

struct ast_node *make_expr_value(const double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  node->children_count = 0;
  node->children[0] = NULL;
  node->next = NULL;

  return node;
}

struct ast_node *make_expr_name(char* name) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_NAME;
    node->u.name = name;
    node->children_count = 0;
    node->children[0] = NULL;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_up() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    node->children_count = 0;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_down() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    node->children_count = 0;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_home() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    node->children_count = 0;
    node->children[0] = NULL;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_set(struct ast_node *var, struct ast_node *value) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SET;
    node->children_count = 2;
    node->u.name = var->u.name;
    node->children[0] = var;
    node->children[1] = value;
    node->next = NULL;
    
    return node;    
}

struct ast_node *make_cmd_block(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_BLOCK;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *cmd) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_PROC;
    node->u.name = name->u.name;
    node->children_count = 2;
    node->children[0] = name;
    node->children[1] = cmd;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_call(struct ast_node *name) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_CALL;
    node->u.name = name->u.name;
    node->children_count = 1;
    node->children[0] = name;
    node->next = NULL;

    return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_REPEAT;
    node->children_count = 2;
    node->children[0] = expr;
    node->children[1] = cmd;
    node->next = NULL;

    return node;
}

/* Creators for internal functions */

struct ast_node *make_func_sin(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_func_cos(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_func_tan(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_func_sqrt(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_func_random(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_RANDOM;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    node->next = NULL;

    return node;
}

/* Creators for colours */

struct ast_node *make_cmd_color(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 1;
    node->children[0] = expr;
    node->next = NULL;

    return node;
}

struct ast_node *make_color_rgb(struct ast_node *r, struct ast_node *g, struct ast_node *b) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 3;
    node->children[0] = r;
    node->children[1] = g;
    node->children[2] = b;
    node->next = NULL;

    return node;
}

struct ast_node *make_color_word(char* word) {
    double r, g, b;
    if (strcmp(word, "white") == 0) {
        r = g = b = 1.0;
    } else if (strcmp(word, "gray") == 0) {
        r = g = b = 0.5;
    } else if (strcmp(word, "red") == 0) {
        r = 1.0;
        g = 0.0;
        b = 0.0;
    } else if (strcmp(word, "green") == 0) {
        r = 0.0;
        g = 1.0;
        b = 0.0;
    } else if (strcmp(word, "blue") == 0) {
        r = 0.0;
        g = 0.0;
        b = 1.0;
    } else if (strcmp(word, "yellow") == 0) {
        r = 1.0;
        g = 1.0;
        b = 0.0;
    } else if (strcmp(word, "cyan") == 0) {
        r = 0.0;
        g = 1.0;
        b = 1.0;
    } else if (strcmp(word, "magenta") == 0) {
        r = 1.0;
        g = 0.0;
        b = 1.0;
    } else {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

    struct ast_node *red = calloc(1, sizeof(struct ast_node));
    red->kind = KIND_EXPR_VALUE;
    red->u.value = r;
    red->children_count = 0;
    red->next = NULL;

    struct ast_node *green = calloc(1, sizeof(struct ast_node));
    green->kind = KIND_EXPR_VALUE;
    green->u.value = g;
    green->children_count = 0;
    green->next = NULL;

    struct ast_node *blue = calloc(1, sizeof(struct ast_node));
    blue->kind = KIND_EXPR_VALUE;
    blue->u.value = b;
    blue->children_count = 0;
    blue->next = NULL;

    return make_color_rgb(red, green, blue);
}



void ast_node_destroy(struct ast_node *self) {
    for (size_t i = 0; i < self->children_count; i++) {
        ast_node_destroy(self->children[i]);
    }
    if (self->next != NULL) {
        ast_node_destroy(self->next);
    }

    if (self->kind == KIND_EXPR_NAME && self->u.name != NULL) {
        free( self->u.name);
    }
    free(self);
}

void ast_destroy(struct ast *self) {
    ast_node_destroy(self->unit);
}

/*
 * context
 */

void context_create(struct context *self) {
    self->x = 0;
    self->y = 0;
    self->angle = 0;
    self->up = false;

    // Need to add procedures handling
    // Need to add variable handling
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void print_ast_node_cmd(const struct ast_node *node) {
    switch (node->u.cmd) {
        case CMD_UP:
            printf("up ");
            break;
        case CMD_DOWN:
            printf("down ");
            break;
        case CMD_RIGHT:
            printf("right ");
            break;
        case CMD_LEFT:
            printf("left ");
            break;
        case CMD_HEADING:
            printf("heading ");
            break;
        case CMD_FORWARD:
            printf("forward ");
            break;
        case CMD_BACKWARD:
            printf("backward ");
            break;
        case CMD_POSITION:
            printf("position ");
            break;
        case CMD_HOME:
            printf("home ");
            break;
        case CMD_COLOR:
            printf("color ");
            break;
        case CMD_PRINT:
            printf("print ");
            break;
        default:
            printf("unknown command");
            break;
    }
}

void print_ast_node(const struct ast_node *node, int indent) {
    if (node == NULL) { return; }

    for (int i = 0; i < indent; i++) {
        printf("\t");
    }

    switch (node->kind) {
        case KIND_CMD_SIMPLE:
            print_ast_node_cmd(node);
            break;
        case KIND_CMD_REPEAT:
            printf("repeat ");
            break;
        case KIND_CMD_BLOCK:
            printf("{\n");
            indent++;
            break;
        case KIND_CMD_PROC:
            printf("proc ");
            break;
        case KIND_CMD_CALL:
            printf("call ");
            break;
        case KIND_CMD_SET:
            printf("set ");
            break;

        case KIND_EXPR_VALUE:
            printf("%f ", node->u.value);
            break;
        case KIND_EXPR_UNOP:
        case KIND_EXPR_BINOP:
            printf("%c ", node->u.op);
            break;
        case KIND_EXPR_BLOCK:
            printf("%s {", node->u.name);
            break;
        case KIND_EXPR_NAME:
            printf("%s ", node->u.name);
            break;

        default: break;
    }

    for (size_t i = 0; i < node->children_count; i++) {
        print_ast_node(node->children[i], indent);
    }

    if (node->kind == KIND_CMD_BLOCK) {
        printf("\n}");
    }

    if (node->next != NULL) {
        printf("\n");
        print_ast_node(node->next, indent);
    }
}

void ast_print(const struct ast *self) {
    print_ast_node(self->unit, 0);
}
