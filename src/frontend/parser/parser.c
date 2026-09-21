#include "parser_internal.h"
#include <stdio.h>
#include <stdlib.h>

Token parser_advance(Parser *parser) {
  Token token = get_token(parser->tokens, parser->current);
  if (token.tag != TOKEN_EOF)
    parser->current++;

  return token;
}

void parser_error(Parser *parser, char *message) {
  if (parser->in_panic_mode) {
    return;
  }
  parser->in_panic_mode = true;
  parser->has_error = true;

  if (parser->length == parser->capacity) {
    size_t new_capacity = parser->capacity == 0 ? 8 : parser->capacity * 2;
    Error *new_data = realloc(parser->data, new_capacity * sizeof(*new_data));
    if (new_data == NULL) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }

    parser->data = new_data;
    parser->capacity = new_capacity;
  }

  parser->data[parser->length++] = (Error){
      .msg = message,
  };
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

bool parser_match(Parser *parser, TokenTag tag) {
  if (get_token(parser->tokens, parser->current).tag != tag)
    return false;

  parser_advance(parser);
  return true;
}

// main entry point
ASTNode *komiC_parse(Tokens *tokens) {
  Parser p = (Parser){
      tokens,      .current = 0,  .has_error = false, .in_panic_mode = false,
      .length = 0, .capacity = 0, .data = NULL,
  };

  ASTNode *root = parse_precedence(&p, PREC_ASSIGNMENT);
  if (p.has_error) {
    free_ast(root);
    return NULL;
  }
  return root;
}
