#include "parser_internal.h"

static ASTNode *parse_while_statement(Parser *parser);
static ASTNode *parse_if_statement(Parser *parser);
static ASTNode *parse_return_statement(Parser *parser);
static ASTNode *parse_expression_statement(Parser *parser);
