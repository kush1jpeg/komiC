#ifndef KOMI_PARSER_H
#define KOMI_PARSER_H
#include "token.h"
#include "utils/source_file.h"

// @brief Scan the source file and generate a list of tokens
Tokens lex(SourceFile source);

// @brief Parse tokens into AST
void parse(const char *src, Tokens tokens);

#endif
