#include "frontend/ast.h"
#include "frontend/diagnostics.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Parser {
  const Tokens *tokens;
  uint32_t current; // to track the curr token;

  bool has_error;
  bool in_panic_mode;

  // error handling;
  size_t length;
  size_t capacity;
  Error *data;
} Parser;

// pratt-parser precedence table
typedef enum Precedence {
  PREC_NONE = 0,
  PREC_ASSIGNMENT, // =
  PREC_OR,         // ||
  PREC_AND,        // &&
  PREC_EQUALITY,   // == !=
  PREC_COMPARISON, // < <= > >=
  PREC_TERM,       // + -
  PREC_FACTOR,     // * / %
  PREC_UNARY,      // ! - (prefix)
  PREC_CALL,       // ()
  PREC_PRIMARY,
} Precedence;

static Precedence get_precedence(TokenTag tag) {
  switch (tag) {
  case TOKEN_EQUAL:
    return PREC_ASSIGNMENT;

  case TOKEN_OR_OR:
    return PREC_OR;

  case TOKEN_AND_AND:
    return PREC_AND;

  case TOKEN_EQUAL_EQUAL:
  case TOKEN_NOT_EQUAL:
    return PREC_EQUALITY;

  case TOKEN_LESS:
  case TOKEN_LESS_EQUAL:
  case TOKEN_GREATER:
  case TOKEN_GREATER_EQUAL:
    return PREC_COMPARISON;

  case TOKEN_PLUS:
  case TOKEN_MINUS:
    return PREC_TERM;

  case TOKEN_STAR:
  case TOKEN_SLASH:
  case TOKEN_PERCENT:
    return PREC_FACTOR;

  case TOKEN_LEFT_PAREN:
    return PREC_CALL;

  default:
    return PREC_NONE;
  }
}

// gets the current token
static Token parser_current_token(const Parser *parser) {
  return get_token(parser->tokens, parser->current);
}

// next token peek
static Token peek_parser_next_token(const Parser *parser) {
  return get_token(parser->tokens, parser->current + 1);
}

static void parser_advance(Parser *parser) {
  if (parser->current < parser->tokens->token_count)
    parser->current++;
  return;
}

ASTNode *create_node(TokenTag tag, char *value, ASTNode *left, ASTNode *right) {
  ASTNode *node = malloc(sizeof(*node));

  if (node == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  node->tag = tag;
  node->value = value;
  node->left = left;
  node->right = right;

  return node;
}

ASTNode *parse_prefix(Parser *parser) {
  /*
all of these frnow can start an expression.
INTEGER, IDENTIFIER, (, -, !, true, false
    */
}

ASTNode *parse_infix(Parser *parser) {
  /*
all of these can behave as an infix.
+, -, *, /, %, ==, !=, < , <=, >, >=, &&, ||, =
*/
}

ASTNode *parse_precedence(Parser *parser, Precedence precedence) {
  ASTNode *left = parse_prefix(parser);
  parser_advance(parser);

  while (precedence <=
         get_precedence(get_token(parser->tokens, parser->current).tag)) {
    parser_advance(parser);

    left = parse_infix(previous_token, left);
  }

  return left;
}

// main entry point
ASTNode *komiC_parse(Tokens *tokens) {
  Parser p = {
      tokens,      .current = 0,  .has_error = false, .in_panic_mode = false,
      .length = 0, .capacity = 0, .data = NULL,

  };
  return parse_precedence(&p, PREC_NONE);
}

void print_ast(ASTNode *node, int level) { // for debuggingg.
  if (!node)
    return;
  print_ast(node->right, level + 1);
  for (int i = 0; i < level; i++)
    printf("   ");
  printf(" the root is - %s\n", node->value);
  print_ast(node->left, level + 1);
}
