#ifndef KOMI_AST_H
#define KOMI_AST_H

#include "token.h"
#include <stdbool.h>
#include <stddef.h>

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

typedef struct {
  Token name;
  Token type;
  bool has_type;
  ASTNode *initializer;
} ASTLet;

typedef struct {
  ASTNode *condition;
  ASTNode *body;
} ASTWhile;

typedef struct {
  ASTNode *condition;

  ASTNode *then_branch;
  ASTNode *else_branch; // NULL if no else
} ASTIf;

typedef struct {
  ASTNode **statements;
  size_t count;
  size_t capacity;
} ASTBlock;

typedef struct {
  ASTNode *callee;
  ASTNode **arguments;
  size_t argument_count;
  size_t argument_capacity;
} ASTCall;

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
    Token literal;
    Token identifier;
    ASTBinary binary;
    ASTUnary unary;
    ASTLet let;
    ASTWhile while_loop;
    ASTIf if_stmt;
    ASTBlock block;
    ASTCall call;
  };
} ASTNode;

// PERF: ASTNode reserves enough space for the largest one cuz of union

const char *ast_tag_name(ASTNodeKind tag);

ASTNode *create_ast_literal(Token token);

ASTNode *create_ast_identifier(Token token);

ASTNode *create_ast_binary(Token token, ASTNode *left, ASTNode *right);

ASTNode *create_ast_unary(Token token, ASTNode *operand);

ASTNode *create_ast_call(ASTNode *callee);

void free_ast(ASTNode *node);

#endif
