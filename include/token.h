#ifndef KOMI_TOKEN_H
#define KOMI_TOKEN_H
#include <assert.h>
#include <stdint.h>

typedef enum TokenTag {
  TOKEN_INVALID = 0,

  // Delimiters
  TOKEN_LEFT_PAREN,  // (
  TOKEN_RIGHT_PAREN, // )
  TOKEN_LEFT_BRACE,  // {
  TOKEN_RIGHT_BRACE, // }

  // Arithmetic
  TOKEN_PLUS,    // +
  TOKEN_MINUS,   // -
  TOKEN_STAR,    // *
  TOKEN_SLASH,   // /
  TOKEN_PERCENT, // %

  // Assignment / comparison
  TOKEN_EQUAL,       // =
  TOKEN_EQUAL_EQUAL, // ==
  TOKEN_NOT,         // !
  TOKEN_NOT_EQUAL,   // !=

  TOKEN_LESS,          // <
  TOKEN_LESS_EQUAL,    // <=
  TOKEN_GREATER,       // >
  TOKEN_GREATER_EQUAL, // >=

  // Logical
  TOKEN_AND_AND, // &&
  TOKEN_OR_OR,   // ||

  // Punctuation
  TOKEN_COMMA,     // ,
  TOKEN_COLON,     // :
  TOKEN_SEMICOLON, // ;
  TOKEN_ARROW,     // ->

  // Keywords
  TOKEN_KEYWORD_LET,
  TOKEN_KEYWORD_FN,

  TOKEN_KEYWORD_IF,
  TOKEN_KEYWORD_ELSE,
  TOKEN_KEYWORD_WHILE,

  TOKEN_KEYWORD_RETURN,

  TOKEN_KEYWORD_TRUE,
  TOKEN_KEYWORD_FALSE,

  // Types
  TOKEN_KEYWORD_INT,
  TOKEN_KEYWORD_FLOAT,
  TOKEN_KEYWORD_BOOL,
  TOKEN_KEYWORD_STRING,
  TOKEN_KEYWORD_VOID,

  // Values
  TOKEN_IDENTIFIER,
  TOKEN_INTEGER,
  TOKEN_FLOAT,
  TOKEN_STRING,

  // Special
  TOKEN_ERROR,
  TOKEN_EOF,

  TOKEN_TYPES_COUNT,
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
} Tokens;

inline static Token get_token(Tokens *tokens, uint32_t i) {
  assert(i < tokens->token_count && i > 0);
  Token t;
  t.tag = tokens->token_types[i];
  t.start = tokens->token_starts[i];
  t.size = tokens->token_sizes[i];
  return t;
}

#endif // KOMI_TOKEN_H
