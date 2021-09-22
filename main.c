//
// Created by tominaga.ryoko on 2021/09/22.
//
#include "chibicc.h"

int main(int argc, char **argv) {
    if (argc != 2)
        error("%s: invalid number of arguments", argv[0]);

    Token *tok = tokenize(argv[1]);

    printf("  .globl main\n");
    printf("main:\n");

    // The first token must be a number
    printf("  mov $%d, %%rax\n", get_number(tok));
    tok = tok->next;

    // ... followed by either `+ <number>` or `- <number>`.
    while (tok->kind != TK_EOF) {
        if (equal(tok, "+")) {
            printf("  add $%d, %%rax\n", get_number(tok->next));
            tok = tok->next->next;
            continue;
        }

        tok = skip(tok, "-");
        printf("  sub $%d, %%rax\n", get_number(tok));
        tok = tok->next;
    }

    printf("  ret\n");
    return 0;
}