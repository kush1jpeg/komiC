#include "token.h"

static const char *token_names[] = {
#define X(name) [name] = #name,
    TOKEN_LIST(X)
#undef X
};

const char *token_tag_name(TokenTag tag) {
  if (tag < 0 || tag >= TOKEN_TYPES_COUNT)
    return "TOKEN_UNKNOWN";

  return token_names[tag];
}
