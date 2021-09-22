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
void error_tok(Token *tok, char *fmt, ...);
int get_number(Token *tok);
bool equal(Token *tok, char *op);
Token *skip(Token *tok, char *s);
Token *tokenize(char *p);

//
// parse.c
//
typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NEG, // unary -
    ND_NUM, // Integer
} NodeKind;

// AST node type
typedef struct Node Node;
struct Node {
    NodeKind kind; // Node kind
    Node *lhs;     // Left-hand side
    Node *rhs;     // Right-hand side
    int val;       // Used if kind == ND_NUM
};

Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);
Node *new_unary(NodeKind kind, Node *expr);
Node *expr(Token **rest, Token *tok);
Node *mul(Token **rest, Token *tok);
Node *unary(Token **rest, Token *tok);
Node *primary(Token **rest, Token *tok);

//
// codegen.c
//

static int depth;
void gen_expr(Node *node);
