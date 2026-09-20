#ifndef KOMI_AST_H
#define KOMI_AST_H

#include "token.h"

typedef struct ASTNode {
  TokenTag tag;
  char *value;
  struct ASTNode *left;
  struct ASTNode *right;
} ASTNode;

#endif
