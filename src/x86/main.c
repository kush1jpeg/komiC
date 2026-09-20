#include "frontend/frontend.h"
#include "token.h"
#include "utils/cli_args.h"
#include "utils/source_file.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void print_tokens(const Tokens *tokens, bool *has_err, SourceFile *source) {
  uint32_t i = 0;
  while (i < tokens->token_count) {
    printf("token[%u]: type=%-24s start=%u size=%u text='%.*s'\n", i,
           token_tag_name(tokens->token_types[i]), tokens->token_starts[i],
           tokens->token_sizes[i], (int)tokens->token_sizes[i],
           source->data + tokens->token_starts[i]);

    if (tokens->token_types[i] == TOKEN_ERROR)
      *has_err = true;
    i++;
  }
}

int main(int argc, char **argv) {
  const CliArgs args = parse_cli_args(argc, argv);
  printf("%s \n", args.source_filename);

  SourceFile source = mmap_file(args.source_filename);
  Tokens tokens = lex(source);
  if (args.stop_after_lexer) {
    bool has_err = false;
    print_tokens(&tokens, &has_err, &source);
    exit(has_err ? 1 : 0);
  }

  unmap_file(&source);
  return 0;
}
