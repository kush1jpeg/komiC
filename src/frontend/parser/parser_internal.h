#ifndef KOMIC_PARSER_INTERNAL_H
#define KOMIC_PARSER_INTERNAL_H

#include "frontend/ast.h"
#include "frontend/diagnostics.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

/* expressions */
ASTNode *parse_expression(Parser *parser);
ASTNode *parse_precedence(Parser *parser, Precedence precedence);

/* token navigation */
Token parser_current(const Parser *parser);
Token parser_previous(const Parser *parser);
Token parser_advance(Parser *parser);

bool parser_check(const Parser *parser, TokenTag tag);
bool parser_match(Parser *parser, TokenTag tag);

/* statements */
ASTNode *parse_statement(Parser *parser);

/* declarations */
ASTNode *parse_declaration(Parser *parser);

/* errors */
void parser_error(Parser *parser, char *message);

#endif

// PERF: add the parser_error everywhere!
