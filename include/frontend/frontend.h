#ifndef KOMI_PARSER_H
#define KOMI_PARSER_H
#include "token.h"
#include "utils/source_file.h"
#include <stdbool.h>

// @brief Scan the source file and generate a list of tokens
Tokens lex(SourceFile source);
void print_tokens(const Tokens *tokens, bool *has_err, SourceFile *source);

// @brief Parse tokens into AST
void komiC_parse(Tokens tokens);

#endif
