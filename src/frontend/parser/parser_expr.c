#include "frontend/ast.h"
#include "parser_internal.h"
#include <stdio.h>
#include <stdlib.h>

static ASTNode *parse_prefix(Parser *parser, Token token);
static ASTNode *parse_infix(Parser *parser, ASTNode *left, Token op);

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

ASTNode *parse_precedence(Parser *parser, Precedence precedence) {
  Token token = parser_advance(parser);
  ASTNode *left = parse_prefix(parser, token);
  if (left == NULL)
    return NULL;
  while (precedence <=
         get_precedence(get_token(parser->tokens, parser->current).tag)) {
    Token op = parser_advance(parser);
    left = parse_infix(parser, left, op);

    if (left == NULL)
      return NULL;
  }
  return left;
}

static ASTNode *parse_unary(Parser *parser, Token op) {
  ASTNode *operand = parse_precedence(parser, PREC_UNARY);
  if (operand == NULL)
    return NULL;

  // i am attaching operand to the right side
  ASTNode *unary = create_ast_unary(op, operand);
  return unary;
}

static ASTNode *parse_grouping(Parser *parser) {
  ASTNode *exp = parse_precedence(parser, PREC_ASSIGNMENT);

  if (exp == NULL)
    return NULL;

  if (!parser_match(parser, TOKEN_RIGHT_PAREN)) {
    parser_error(parser, "komic: expected ')' after expression");
    return exp;
  }
  return exp;
}

static ASTNode *parse_prefix(Parser *parser, Token token) {
  // Tokens that can BEGIN an expression:
  switch (token.tag) {

  case TOKEN_INTEGER:
  case TOKEN_FLOAT:
  case TOKEN_STRING:
  case TOKEN_KEYWORD_TRUE:
  case TOKEN_KEYWORD_FALSE:
    return create_ast_literal(token);

  case TOKEN_IDENTIFIER:
    return create_ast_identifier(token);

  case TOKEN_MINUS:
  case TOKEN_NOT:
    return parse_unary(parser, token);

  case TOKEN_LEFT_PAREN:
    return parse_grouping(parser);

  default:
    fprintf(stderr, "komic: expected expression, got %s\n",
            token_tag_name(token.tag));
    parser->has_error = true;
    return NULL;
  }
}

static ASTNode *parse_assignment(Parser *parser, ASTNode *left, Token op) {
  // NOTE: Assignment is RIGHT associative.
  Precedence p = get_precedence(op.tag);

  ASTNode *right = parse_precedence(parser, p);

  if (right == NULL)
    return NULL;

  return create_ast_binary(op, left, right);
}

static ASTNode *parse_binary(Parser *parser, ASTNode *left, Token op) {
  Precedence a = get_precedence(op.tag);
  // NOTE: +1 makes ordinary binary operators LEFT associative.
  ASTNode *right = parse_precedence(parser, (Precedence)(a + 1));

  if (right == NULL)
    return NULL;

  return create_ast_binary(op, left, right);
}

static void ast_call_push_argument(ASTNode *call, ASTNode *arg,
                                   Parser *parser) {
  if (call->kind != AST_CALL) {
    char msg[128];
    snprintf(msg, sizeof(msg), "komic: expected AST_CALL node, got %s",
             ast_tag_name(call->kind));
    parser_error(parser, msg);
    return;
  }

  if (call->call.argument_count == call->call.argument_capacity) {
    size_t newSize = call->call.argument_capacity == 0
                         ? 4
                         : call->call.argument_capacity * 2;
    ASTNode **new_args =
        realloc(call->call.arguments, newSize * sizeof(*new_args));
    if (new_args == NULL) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }

    call->call.arguments = new_args;
    call->call.argument_capacity = newSize;
  }

  call->call.arguments[call->call.argument_count++] = arg;
}

static ASTNode *parse_call(Parser *parser, ASTNode *callee) {
  ASTNode *call = create_ast_call(callee);
  do {
    ASTNode *arg = parse_expression(parser);
    if (arg == NULL) {
      free_ast(call);
      return NULL;
    }
    ast_call_push_argument(call, arg, parser);

  } while (parser_match(parser, TOKEN_COMMA));

  if (!parser_match(parser, TOKEN_RIGHT_PAREN)) {
    parser_error(parser, "expected ')' after function arguments");

    return call;
  }
  return call;
}

ASTNode *parse_infix(Parser *parser, ASTNode *left, Token op)
// Tokens that can be in-between expressions:
{
  char msg[128] = "";
  switch (op.tag) {

  // arithmetic
  case TOKEN_PLUS:
  case TOKEN_MINUS:
  case TOKEN_STAR:
  case TOKEN_SLASH:
  case TOKEN_PERCENT:

  // equality
  case TOKEN_EQUAL_EQUAL:
  case TOKEN_NOT_EQUAL:

  // comparison
  case TOKEN_LESS:
  case TOKEN_LESS_EQUAL:
  case TOKEN_GREATER:
  case TOKEN_GREATER_EQUAL:

  // logical
  case TOKEN_AND_AND:
  case TOKEN_OR_OR:
    return parse_binary(parser, left, op);

  // assignment
  case TOKEN_EQUAL:
    return parse_assignment(parser, left, op);

    // function call
  case TOKEN_LEFT_PAREN:
    return parse_call(parser, left);

  default:
    snprintf(msg, sizeof(msg), "komiLang: invalid infix operator %s",
             token_tag_name(op.tag));
    parser_error(parser, msg);

    return NULL;
  }
}
