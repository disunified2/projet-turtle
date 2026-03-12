#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  node->children_count = 0;
  node->children[0] = NULL;
  return node;
}

struct ast_node *make_cmd_up(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_down(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    return node;
}

struct ast_node *make_cmd_home() {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    node->children_count = 0;
    node->children[0] = NULL;
    return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

/* Creators for colours */
struct ast_node *make_cmd_color(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}



void ast_node_destroy(struct ast_node *self) {
    for (size_t i = 0; i < self->children_count; i++) {
        ast_node_destroy(self->children[i]);
    }
    if (self->next != NULL) {
        ast_node_destroy(self->next);
    }
    free(self);
}

void ast_destroy(struct ast *self) {
    ast_node_destroy(self->unit);
    free(self);
}
// Need to check if destroy actually works correctly with no memory leaks

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

void print_ast_node(const struct ast_node *node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf(" ");
    }

    switch (node->kind) {
        case KIND_CMD_SIMPLE:
            printf("CMD_SIMPLE: ");
            switch (node->u.cmd) {
                case CMD_UP:
                    printf("up");
                    break;
                case CMD_DOWN:
                    printf("down");
                    break;
                case CMD_RIGHT:
                    printf("right");
                    break;
                case CMD_LEFT:
                    printf("left");
                case CMD_HEADING:
                    printf("heading");
                    break;
                case CMD_FORWARD:
                    printf("forward");
                    break;
                case CMD_BACKWARD:
                    printf("backward");
                    break;
                case CMD_POSITION:
                    printf("position");
                    break;
                case CMD_HOME:
                    printf("home");
                    break;
                case CMD_COLOR:
                    printf("color");
                    break;
                case CMD_PRINT:
                    printf("print");
                    break;
                default:
                    printf("unknown command");
                    break;
            }
            break;
        case KIND_CMD_REPEAT:
            printf("repeat:");
            break;
        case KIND_CMD_BLOCK:
            printf("block:");
            break;
        case KIND_CMD_PROC:
            printf("proc: %s", node->u.name);
            break;
        case KIND_CMD_CALL:
            printf("call: %s", node->u.name);
            break;
        case KIND_CMD_SET:
            printf("set: %s", node->u.name);
            break;

        case KIND_EXPR_VALUE:
            printf("value: %f", node->u.value);
            break;
        case KIND_EXPR_UNOP:
            printf("unop: %c", node->u.op);
            break;
        case KIND_EXPR_BINOP:
            printf("binop: %c", node->u.op);
            break;
        case KIND_EXPR_BLOCK:
            printf("block: %s", node->u.name);
            break;
        case KIND_EXPR_NAME:
            printf("name: %s", node->u.name);
            break;

        /* Insert case KIND_EXPR_FUNC here */
        default: break;
    }
    printf("\n");

    for (size_t i = 0; i < node->children_count; i++) {
        print_ast_node(node->children[i], indent + 1);
    }

    if (node->next != NULL) {
        print_ast_node(node->next, indent);
    }
}

void ast_print(const struct ast *self) {
    print_ast_node(self->unit, 0);
}
