#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
    node->u.name = strdup(name);
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
    node->u.name = strdup(var->u.name); // c'est peut-etre pas utile ça
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

/* Creators for arithmetic operators */

struct ast_node *make_expr_binop(const char operator, struct ast_node *expr1, struct ast_node *expr2) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));

    node->kind = KIND_EXPR_BINOP;
    node->u.op = operator;
    node->children_count = 2;
    node->children[0] = expr1;
    node->children[1] = expr2;
    node->next = NULL;

    return node;
}

struct ast_node *make_expr_unop(const char operator, struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_UNOP;
    node->u.op = operator;
    node->children_count = 1;
    node->children[0] = expr;
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
 * ast_node_list
 */

//ast_node_list creation
void create_ast_node_list(struct ast_node_list *self) {
    self->capacity = 10;
    self->size = 0;
    self->nodes = malloc(self->capacity * sizeof(struct ast_node *));
}

//ast_node_list destruction
void destroy_ast_node_list(struct ast_node_list *self) {
    free(self->nodes);
}

//ast_node_list addition
void ast_node_list_append(struct ast_node_list *self, struct ast_node *node) {
    for (size_t i = 0; i < self->size; i++) {
        if ( strcmp(self->nodes[i]->children[0]->u.name,node->children[0]->u.name) == 0) {
            self->nodes[i] = node;
            return;
        }
    }

    //full capacity
    if (self->size == self->capacity-1) {
        self->capacity += 10;
        self->nodes = realloc(self->nodes,self->capacity * sizeof(struct ast_node *));
    }

    self->nodes[self->size] = node;
    self->size++;
}

//ast_node_list obtaining
struct ast_node *ast_node_list_get(struct ast_node_list *self, struct ast_node *node) {
    for (size_t i = 0; i < self->size; i++) {
        if ( strcmp(self->nodes[i]->children[0]->u.name,node->children[0]->u.name) == 0) {
            return self->nodes[i];
        }
    }

    return NULL;
}

/*
 * context
 */

//context creation
void context_create(struct context *self) {
    self->x = 0;
    self->y = 0;
    self->angle = 0;
    self->up = false;

    //procedure and variable handling
    create_ast_node_list(&self->variable_list);
    create_ast_node_list(&self->proc_list);
}

//context destruction
void context_destroy(struct context *self) {
    destroy_ast_node_list(&self->variable_list);
    destroy_ast_node_list(&self->proc_list);
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

void print_ast_node_func(const struct ast_node *node) {
    switch (node->u.func) {
        case FUNC_COS:
            printf("cos ");
            break;
        case FUNC_SIN:
            printf("sin ");
            break;
        case FUNC_TAN:
            printf("tan ");
            break;
        case FUNC_SQRT:
            printf("sqrt ");
            break;
        case FUNC_RANDOM:
            printf("random ");
            break;
        default:
            printf("unknown function ");
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
            // indent++;
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

        case KIND_EXPR_FUNC:
            print_ast_node_func(node);
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

/* Tree evaluation */

void move_to(struct context *ctx, double x, double y) {
    ctx->x = x;
    ctx->y = y;
}

double deg_to_rad(const double degrees) {
    return degrees * PI / 180;
}

void ast_node_eval_cmd_simple(const struct ast_node *node, struct context *ctx) {
    switch (node->u.cmd) {
        case CMD_UP:
            ctx->up = true;
            break;
        case CMD_DOWN:
            ctx->up = false;
            break;
        case CMD_RIGHT: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            ctx->angle += angle;
            break;
        }
        case CMD_LEFT: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            ctx->angle -= angle;
            break;
        }
        case CMD_HEADING: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            ctx->angle = angle;
            break;
        }
        case CMD_FORWARD: {
            const double distance = ast_node_eval_expr(node->children[0], ctx);
            const double angle = deg_to_rad(ctx->angle);
            const double new_x = ctx->x + distance * sin(angle);
            const double new_y = ctx->y - distance * cos(angle);
            move_to(ctx, new_x, new_y);
            break;
        }
        case CMD_BACKWARD: {
            const double distance = ast_node_eval_expr(node->children[0], ctx);
            const double angle = deg_to_rad(ctx->angle);
            const double new_x = ctx->x - distance * sin(angle);
            const double new_y = ctx->y + distance * cos(angle);
            move_to(ctx, new_x, new_y);
            break;
        }
        case CMD_POSITION: {
            const bool up = ctx->up;
            ctx->up = true;
            const double new_x = ast_node_eval_expr(node->children[0], ctx);
            const double new_y = ast_node_eval_expr(node->children[1], ctx);
            move_to(ctx, new_x, new_y);
            ctx->up = up;
            break;
        }
        case CMD_HOME: {
            move_to(ctx, 0, 0);
            ctx->angle = 0;
            break;
        }
        case CMD_COLOR: {
            const double r = ast_node_eval_expr(node->children[0], ctx);
            const double g = ast_node_eval_expr(node->children[1], ctx);
            const double b = ast_node_eval_expr(node->children[2], ctx);
            ctx->color[0] = r;
            ctx->color[1] = g;
            ctx->color[2] = b;
            break;
        }
        case CMD_PRINT: {
            const double val = ast_node_eval_expr(node->children[0], ctx);
            fprintf(stderr, "print => %f\n", val);
            break;
        }
        default:
            break;
    }
}

void ast_node_eval_cmd(const struct ast_node *node, struct context *ctx) {
    while (node != NULL) {
        switch (node->kind) {
            case KIND_CMD_SIMPLE:
                ast_node_eval_cmd_simple(node, ctx);
                break;
            case KIND_CMD_REPEAT: {
                const int repeat = (int)floor(ast_node_eval_expr(node->children[0], ctx));
                for (int i = 0; i < repeat; i++) {
                    ast_node_eval_cmd(node->children[1], ctx);
                }
                break;
            }
            case KIND_CMD_BLOCK:
                ast_node_eval_cmd(node->children[0], ctx);
                break;
            case KIND_CMD_PROC:
                // ast_node_list_append(&ctx->proc_list, node);
                break;
            case KIND_CMD_CALL: {
                // const struct ast_node *proc = get_procedure(node->children[0], ctx);
                // if (proc != NULL) {
                //     ast_node_eval_cmd(proc, ctx);
                // }
                break;
            }
            case KIND_CMD_SET: {
                // const double value = ast_node_eval_expr(node->children[1], ctx);
                // struct ast_node *value_node = make_expr_value(value);
                // struct ast_node *node = get_variable(node->children[0], ctx);
                // if (node == NULL) {
                //     ast_node_list_append(&ctx->variable_list, value_node);
                // } else {
                //     node->children[1] = value_node;
                // }
                break;
            }

            // Expression commands
            case KIND_EXPR_FUNC:
            case KIND_EXPR_VALUE:
            case KIND_EXPR_UNOP:
            case KIND_EXPR_BINOP:
            case KIND_EXPR_BLOCK:
            case KIND_EXPR_NAME:
                ast_node_eval_expr(node, ctx);

            default:
                break;
        }

        node = node->next;
    }
}

double ast_node_eval_expr_binop(const struct ast_node *node, struct context *ctx) {
    const double left = ast_node_eval_expr(node->children[0], ctx);
    const double right = ast_node_eval_expr(node->children[1], ctx);
    switch (node->u.op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right != 0) {
                return left / right;
            }
            break;
        case '^':
            return pow(left, right);
        default:
            break;
    }
    return 0;
}

double ast_node_eval_expr_func(const struct ast_node *node, struct context *ctx) {
    switch (node->u.func) {
        case FUNC_COS: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            return cos(deg_to_rad(angle));
        }
        case FUNC_SIN: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            return sin(deg_to_rad(angle));
        }
        case FUNC_TAN: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            return tan(deg_to_rad(angle));
        }
        case FUNC_SQRT: {
            const double angle = ast_node_eval_expr(node->children[0], ctx);
            return sqrt(deg_to_rad(angle));
        }
        case FUNC_RANDOM: {
            const double min = ast_node_eval_expr(node->children[0], ctx);
            const double max = ast_node_eval_expr(node->children[1], ctx);
            if (min <= max) {
                return min + (double)rand() / RAND_MAX * (max - min);
            }
        }
    }
    return 0;
}

double ast_node_eval_expr(const struct ast_node *node, struct context *ctx) {
    switch (node->kind) {
        case KIND_EXPR_VALUE:
            return node->u.value;
        case KIND_EXPR_NAME: {
            // const struct ast_node *var = get_variable(node, ctx);
            // if (var != NULL) {
            //     ast_node_eval_expr(var->children[0], ctx);
            // }
            break;
        }
        case KIND_EXPR_BINOP:
            return ast_node_eval_expr_binop(node, ctx);
        case KIND_EXPR_UNOP: {
            const double val = ast_node_eval_expr(node->children[0], ctx);
            return -val;
        }
        case KIND_EXPR_FUNC:
            return ast_node_eval_expr_func(node, ctx);
        default:
            break;
    }
    return 0;
}

void ast_eval(const struct ast *self, struct context *ctx) {
    ast_node_eval_cmd(self->unit, ctx);
}
