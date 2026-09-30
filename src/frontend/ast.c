#include "frontend/ast.h"
#include <stdio.h>
#include <stdlib.h>

// printing names
static const char *ast_names[] = {
#define X(name) [name] = #name,
    AST_KIND_LIST(X)
#undef X
};

const char *ast_tag_name(ASTNodeKind tag) {
  if (tag < 0 || tag >= AST_KIND_COUNT)
    return "TOKEN_UNKNOWN";

  return ast_names[tag];
}

void print_ast_binary(const ASTNode *node, const char *source, int level) {
  if (node == NULL)
    return;

  print_ast_binary(node->binary.right, source, level + 1);

  for (int i = 0; i < level; i++)
    printf("    ");

  printf("%s '%.*s'\n", ast_tag_name(node->kind), (int)node->binary.token.size,
         source + node->binary.token.start);

  print_ast_binary(node->binary.left, source, level + 1);
}

void free_ast(ASTNode *node) {
  if (node == NULL)
    return;
  switch (node->kind) {
  case AST_BINARY:
    free_ast(node->binary.left);
    free_ast(node->binary.right);
    break;

  case AST_UNARY:
    free_ast(node->unary.operand);
    break;
  }
  free_ast(node->left);
  free_ast(node->right);

  free(node);
}

// create_ast
ASTNode *create_ast_binary(Token token, ASTNode *left, ASTNode *right,
                           ASTNodeKind kind) {
  ASTNode *node = malloc(sizeof(*node));

  if (node == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  node->kind = kind;
  node->binary.token = token;
  node->binary.left = left;
  node->binary.right = right;
  return node;
}

ASTNode *create_ast_unary(Token token, ASTNode *operand, ASTNodeKind kind) {
  ASTNode *node = malloc(sizeof(*node));

  if (node == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  node->kind = kind;
  node->unary.token = token;
  node->unary.operand = operand;
  return node;
}
