#ifndef KOMI_AST_H
#define KOMI_AST_H

#include "token.h"

typedef struct ASTNode {
  TokenTag kind;
  Token token;
  char *value;
  struct ASTNode *left;
  struct ASTNode *right;
} ASTNode;

void free_ast(ASTNode *node);
ASTNode *create_leaf(Token token, ASTNode *left, ASTNode *right);

#endif
