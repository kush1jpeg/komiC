#include "cli_args.h"
#include "frontend.h"
#include "sourceFile.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  const CliArgs result = parse_cli_args(argc, argv);
  printf("%s", result.source_filename);

  SourceFile source = map_file(result.source_filename);
  Tokens tokens = lex(source);

  unmap_file(&source);
  return 0;
}
