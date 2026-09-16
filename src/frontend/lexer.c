#include "frontend.h"
#include "token.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Lexer {
  const char *start;
  const char *tokenStart;
  const char *current;
  const char *end;
  uint32_t line;
  uint32_t column;
} Lexer;

static Lexer lexer_create(const char *data, size_t size) {
  return (Lexer){
      .start = data,
      .tokenStart = data,
      .current = data,
      .end = data + size,
      .line = 1,
      .column = 1,
  };
}

static bool lexer_is_at_end(const Lexer *lexer) {
  return lexer->current >= lexer->end;
}

static Token make_token(const Lexer *lexer, TokenTag type) {
  return (Token){
      .tag = type,
      .start = lexer->tokenStart - lexer->start,
      .size = lexer->current - lexer->tokenStart,
  };
}

static char peek_next(const Lexer *lexer) {
  if (lexer_is_at_end(lexer)) {
    return '\0';
  }
  return lexer->current[1];
}

static char advance(Lexer *lexer) {
  if (*lexer->current == '\n') {
    ++lexer->line;
    lexer->column = 1;
  } else {
    lexer->column++;
  }
  return *lexer->current++;
}

static void skip_comments(Lexer *lexer) {
  while (*lexer->current != '\n' && !lexer_is_at_end(lexer)) {
    advance(lexer);
  }
}

static void skipWhitespaces(Lexer *lexer) {
  for (;;) {
    char c = *lexer->current;
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
    case '\n':
      advance(lexer);
      break;
    case '/': {
      if (peek_next(lexer) == '/') {
        skip_comments(lexer);
        break;
      }
    }
    }
  }
}

static TokenTag get_identifier_type(Lexer *lexer) {
  size_t len = lexer->current - lexer->tokenStart;
  const char *start = lexer->tokenStart;
  if (len == 3 && strncmp(start, "let", 3) == 0)
    return TOKEN_KEYWORD_LET;
  if (len == 2 && strncmp(start, "fn", 2) == 0)
    return TOKEN_KEYWORD_FN;
  if (len == 2 && strncmp(start, "if", 2) == 0)
    return TOKEN_KEYWORD_IF;
  if (len == 4 && strncmp(start, "else", 4) == 0)
    return TOKEN_KEYWORD_ELSE;
  if (len == 5 && strncmp(start, "while", 5) == 0)
    return TOKEN_KEYWORD_WHILE;
  if (len == 6 && strncmp(start, "return", 6) == 0)
    return TOKEN_KEYWORD_RETURN;
  if (len == 4 && strncmp(start, "true", 4) == 0)
    return TOKEN_KEYWORD_TRUE;
  if (len == 5 && strncmp(start, "false", 5) == 0)
    return TOKEN_KEYWORD_FALSE;
  if (len == 3 && strncmp(start, "int", 3) == 0)
    return TOKEN_KEYWORD_INT;
  if (len == 5 && strncmp(start, "float", 5) == 0)
    return TOKEN_KEYWORD_FLOAT;
  if (len == 4 && strncmp(start, "bool", 4) == 0)
    return TOKEN_KEYWORD_BOOL;
  if (len == 6 && strncmp(start, "string", 6) == 0)
    return TOKEN_KEYWORD_STRING;
  if (len == 4 && strncmp(start, "void", 4) == 0)
    return TOKEN_KEYWORD_VOID;

  return TOKEN_IDENTIFIER;
}

static bool is_digit(char c) { return c >= '0' && c <= '9'; }

static bool check_identifier(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static Token scan_identifier(Lexer *lexer) {
  while (is_digit(*lexer->current) || check_identifier(*lexer->current)) {
    advance(lexer);
  }
  return make_token(lexer, get_identifier_type(lexer));
}

static Token scan_number(Lexer *lexer) {
  while (!lexer_is_at_end(lexer) && is_digit(*lexer->current)) {
    advance(lexer);
  }
  return make_token(lexer, TOKEN_INTEGER);
}

static Token scan_symbol(Lexer *lexer) {
  switch (lexer->tokenStart[0]) {

  // delimiters
  case '(':
    return make_token(lexer, TOKEN_LEFT_PAREN);

  case ')':
    return make_token(lexer, TOKEN_RIGHT_PAREN);

  case '{':
    return make_token(lexer, TOKEN_LEFT_BRACE);

  case '}':
    return make_token(lexer, TOKEN_RIGHT_BRACE);

  // punctuation
  case ',':
    return make_token(lexer, TOKEN_COMMA);

  case ':':
    return make_token(lexer, TOKEN_COLON);

  case ';':
    return make_token(lexer, TOKEN_SEMICOLON);

  // arithmetic
  case '+':
    return make_token(lexer, TOKEN_PLUS);

  case '-':
    if (peek_next(lexer) == '>') {
      return make_token(lexer, TOKEN_ARROW);
    }
    return make_token(lexer, TOKEN_MINUS);

  case '*':
    return make_token(lexer, TOKEN_STAR);

  case '/':
    return make_token(lexer, TOKEN_SLASH);

  case '%':
    return make_token(lexer, TOKEN_PERCENT);

  // assignment / equality
  case '=':
    if (peek_next(lexer) == '=')
      return make_token(lexer, TOKEN_EQUAL_EQUAL);

    return make_token(lexer, TOKEN_EQUAL);

  // logical not / inequality
  case '!':
    if (peek_next(lexer) == '=')
      return make_token(lexer, TOKEN_NOT_EQUAL);

    return make_token(lexer, TOKEN_NOT);

  // comparison
  case '<':
    if (peek_next(lexer) == '=')
      return make_token(lexer, TOKEN_LESS_EQUAL);

    return make_token(lexer, TOKEN_LESS);

  case '>':
    if (peek_next(lexer) == '=')
      return make_token(lexer, TOKEN_GREATER_EQUAL);

    return make_token(lexer, TOKEN_GREATER);

  // logical AND
  case '&':
    if (peek_next(lexer) == '&')
      return make_token(lexer, TOKEN_AND_AND);

    return make_token(lexer, TOKEN_ERROR);

  // logical OR
  case '|':
    if (peek_next(lexer) == '|')
      return make_token(lexer, TOKEN_OR_OR);

    return make_token(lexer, TOKEN_ERROR);
  default:
    return make_token(lexer, TOKEN_ERROR);
  }
}

static Token scan_token(Lexer *lexer) {
  skipWhitespaces(lexer);
  lexer->tokenStart = lexer->current;

  if (lexer_is_at_end(lexer))
    return make_token(lexer, TOKEN_EOF);

  char curr = advance(lexer);

  if (is_digit(curr))
    return scan_number(lexer);

  if (check_identifier(curr))
    return scan_identifier(lexer);

  return scan_symbol(lexer);
}

Tokens lex(SourceFile source) {
  Lexer lexer = lexer_create(source.data, source.size);

  for (;;) {
    const Token token = scan_token(&lexer);
    // ....continue
  }
}
