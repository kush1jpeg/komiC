#ifndef KOMI_CLI_ARGS_H
#define KOMI_CLI_ARGS_H
#include <stdbool.h>

typedef struct CliArgs {
  const char *source_filename; // Filename of the source file (with extension)
  bool stop_after_lexer;       // --lex
  bool stop_after_parser;      // --parse
  bool stop_after_semantic_analysis;
  bool codegen_only;       // generate assembly; but does not save to a file
  bool compile_only;       // Compile only; do not assemble or link
  bool stop_before_linker; // Compile and assemble, do not run linker
} CliArgs;

CliArgs parse_cli_args(int argc, char **argv);

#endif // KOMI_CLI_ARGS_H
