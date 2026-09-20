typedef enum TokenTag {
  TOKEN_INVALID = 0,

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
