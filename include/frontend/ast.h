#ifndef KOMI_AST_H
#define KOMI_AST_H

#include "token.h"
#include <stdbool.h>
typedef struct ASTNode ASTNode;

#define AST_KIND_LIST(X)                                                       \
  X(AST_LITERAL)                                                               \
  X(AST_IDENTIFIER)                                                            \
  X(AST_BINARY)                                                                \
  X(AST_UNARY)                                                                 \
  X(AST_LET)                                                                   \
  X(AST_WHILE)                                                                 \
  X(AST_IF)                                                                    \
  X(AST_BLOCK)                                                                 \
  X(AST_CALL)

#define X(name) name,

typedef enum {
  AST_KIND_LIST(X)
#undef X
      AST_KIND_COUNT
} ASTNodeKind;

/*
typedef struct {
  Token name;
  Token type;
  bool has_type;
  ASTNode *initializer;
} ASTLet; // for future
*/

typedef struct {
  Token token;
  ASTNode *left;
  ASTNode *right;
} ASTBinary;

typedef struct {
  Token token;
  ASTNode *operand;
} ASTUnary;

typedef struct ASTNode {
  ASTNodeKind kind;
  union {
    ASTBinary binary;
    ASTUnary unary;
    //  ASTLet let;
  };
} ASTNode;

// PERF: ASTNode reserves enough space for the largest one cuz of union

#endif
