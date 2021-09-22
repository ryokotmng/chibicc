//
// Created by tominaga.ryoko on 2021/09/22.
//

#include "chibicc.h"

Node *new_node(NodeKind kind) {
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs) {
    Node *node = new_node(kind);
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_num(int val) {
    Node *node = new_node(ND_NUM);
    node->val = val;
    return node;
}


// expr = mul ("+" mul | "-" mul)*
Node *expr(Token **rest, Token *tok) {
    Node *node = mul(&tok, tok);

    for (;;) {
        if (equal(tok, "+")) {
            node = new_binary(ND_ADD, node, mul(&tok, tok->next));
            continue;
        }

        if (equal(tok, "-")) {
            node = new_binary(ND_SUB, node, mul(&tok, tok->next));
            continue;
        }
        *rest = tok;
        return node;
    }
}

// mul = primary ("*" primary | "/" primary)*
Node *mul(Token **rest, Token *tok) {
    Node *node = primary(&tok, tok);

    for (;;) {
        if (equal(tok, "*")) {
            node = new_binary(ND_MUL, node, primary(&tok, tok->next));
            continue;
        }

        if (equal(tok, "/")) {
            node = new_binary(ND_DIV, node, primary(&tok, tok->next));
            continue;
        }

        *rest = tok;
        return node;
    }
}

// primary = "(" expr ")" | num
Node *primary(Token **rest, Token *tok) {
    if (equal(tok, "(")) {
        Node *node = expr(&tok, tok->next);
        *rest = skip(tok, ")");
        return node;
    }

    if (tok->kind == TK_NUM) {
        Node *node = new_num(tok->val);
        *rest = tok->next;
        return node;
    }

    error_tok(tok, "expected an expression");
}
