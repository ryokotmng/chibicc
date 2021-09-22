//
// Created by tominaga.ryoko on 2021/09/22.
//

#include "chibicc.h"

void push(void) {
    printf("  push %%rax\n");
    depth++;
}

void pop(char *arg) {
    printf("  pop %s\n", arg);
    depth--;
}

void gen_expr(Node *node) {
    switch (node->kind) {
    case ND_NUM:
        printf("  mov $%d, %%rax\n", node->val);
        return;
    case ND_NEG:
        gen_expr(node->lhs);
        printf("  neg %%rax\n");
        return;
    }

    gen_expr(node->rhs);
    push();
    gen_expr(node->lhs);
    pop("%rdi");

    switch (node->kind) {
    case ND_ADD:
        printf("  add %%rdi, %%rax\n");
        return;
    case ND_SUB:
        printf("  sub %%rdi, %%rax\n");
        return;
    case ND_MUL:
        printf("  imul %%rdi, %%rax\n");
        return;
    case ND_DIV:
        printf("  cqo\n");
        printf("  idiv %%rdi\n");
        return;
    }

    error("invalid expression");
}
