#ifndef KOMI_PARSER_H
#define KOMI_PARSER_H
#include "sourceFile.h"
#include "token.h"

// @brief Scan the source file and generate a list of tokens
Tokens lex(SourceFile source);

#endif
