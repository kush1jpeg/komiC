#ifndef KOMI_TOKEN_H
#define KOMI_TOKEN_H
#include <assert.h>
#include <stdint.h>

// /docs/token.md
#define TOKEN_LIST(X)                                                          \
  X(TOKEN_INVALID)                                                             \
  X(TOKEN_LEFT_PAREN)                                                          \
  X(TOKEN_RIGHT_PAREN)                                                         \
  X(TOKEN_LEFT_BRACE)                                                          \
  X(TOKEN_RIGHT_BRACE)                                                         \
  X(TOKEN_PLUS)                                                                \
  X(TOKEN_MINUS)                                                               \
  X(TOKEN_STAR)                                                                \
  X(TOKEN_SLASH)                                                               \
  X(TOKEN_PERCENT)                                                             \
  X(TOKEN_EQUAL)                                                               \
  X(TOKEN_EQUAL_EQUAL)                                                         \
  X(TOKEN_NOT)                                                                 \
  X(TOKEN_NOT_EQUAL)                                                           \
  X(TOKEN_LESS)                                                                \
  X(TOKEN_LESS_EQUAL)                                                          \
  X(TOKEN_GREATER)                                                             \
  X(TOKEN_GREATER_EQUAL)                                                       \
  X(TOKEN_AND_AND)                                                             \
  X(TOKEN_OR_OR)                                                               \
  X(TOKEN_COMMA)                                                               \
  X(TOKEN_COLON)                                                               \
  X(TOKEN_SEMICOLON)                                                           \
  X(TOKEN_ARROW)                                                               \
  X(TOKEN_KEYWORD_LET)                                                         \
  X(TOKEN_KEYWORD_FN)                                                          \
  X(TOKEN_KEYWORD_IF)                                                          \
  X(TOKEN_KEYWORD_ELSE)                                                        \
  X(TOKEN_KEYWORD_WHILE)                                                       \
  X(TOKEN_KEYWORD_RETURN)                                                      \
  X(TOKEN_KEYWORD_TRUE)                                                        \
  X(TOKEN_KEYWORD_FALSE)                                                       \
  X(TOKEN_KEYWORD_INT)                                                         \
  X(TOKEN_KEYWORD_FLOAT)                                                       \
  X(TOKEN_KEYWORD_BOOL)                                                        \
  X(TOKEN_KEYWORD_STRING)                                                      \
  X(TOKEN_KEYWORD_VOID)                                                        \
  X(TOKEN_IDENTIFIER)                                                          \
  X(TOKEN_INTEGER)                                                             \
  X(TOKEN_FLOAT)                                                               \
  X(TOKEN_STRING)                                                              \
  X(TOKEN_ERROR)                                                               \
  X(TOKEN_EOF)

#define X(name) name,
typedef enum TokenTag {
  TOKEN_LIST(X)
#undef X
      TOKEN_TYPES_COUNT
} TokenTag;

typedef struct Token {
  TokenTag tag;
  uint32_t start; // The offset of the starting character in a token
  uint32_t size;  // size taken by it
} Token;

/// @SOA view of tokens
typedef struct Tokens {
  TokenTag *token_types;
  uint32_t *token_starts;
  uint32_t *token_sizes;
  uint32_t token_count;
  uint32_t capacity;
} Tokens;

inline static Token get_token(const Tokens *tokens, uint32_t i) {
  assert(i < tokens->token_count);
  Token t;
  t.tag = tokens->token_types[i];
  t.start = tokens->token_starts[i];
  t.size = tokens->token_sizes[i];
  return t;
}

const char *token_tag_name(TokenTag tag);

#endif // KOMI_TOKEN_H
