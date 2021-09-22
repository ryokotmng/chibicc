//
// Created by tominaga.ryoko on 2021/09/22.
//

#ifndef CHIBICC_CHIBICC_H
#define CHIBICC_CHIBICC_H

#endif //CHIBICC_CHIBICC_H

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// tokenize.c
//

typedef enum {
    TK_PUNCT, // Keywords or punctuators
    TK_NUM,   // Numeric literals
    TK_EOF,   // End-of-file markers
} TokenKind;

// Token type
typedef struct Token Token;
struct Token {
    TokenKind kind; // Token kind
    Token *next;    // Next token
    int val;        // If kind is TK_NUM, its value
    char *loc;      // Token location
    int len;        // Token length
};

void error(char *fmt, ...);

int get_number(Token *tok);
bool equal(Token *tok, char *op);

Token *skip(Token *tok, char *s);

Token *tokenize(char *p);