#include "frontend/ast.h"

#include <stdio.h>
#include <stdlib.h>

void free_ast(ASTNode *node) {
  if (node == NULL)
    return;

  free_ast(node->left);
  free_ast(node->right);

  free(node);
}

void print_ast(const ASTNode *node, const char *source, int level) {
  if (node == NULL)
    return;

  print_ast(node->right, source, level + 1);

  for (int i = 0; i < level; i++)
    printf("    ");

  printf("%s '%.*s'\n", token_tag_name(node->kind), (int)node->token.size,
         source + node->token.start);

  print_ast(node->left, source, level + 1);
}

ASTNode *create_leaf(Token token, ASTNode *left, ASTNode *right) {
  ASTNode *node = malloc(sizeof(*node));

  if (node == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  node->kind = token.tag;
  node->token = token;
  node->left = left;
  node->right = right;
  return node;
}
