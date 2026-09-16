#include "cli_args.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Option {
  const char *tag;
  const char *description;
} Option;

static const Option options[] = {
    {"--help, -h", "prints the help message"},
    {"--lex", "lexing only and then dump the result tokens"},
    {"--parse", "lex and parse, and then dump the result AST"},
    {"--validate",
     "lex, parse, perform the semantic analysis on result AST, and then stop"},
    {"--codegen", "generate the assembly, and then dump the result rather than "
                  "saving to a file"},
    {"-S", "Compile only; do not assemble or link."},
    {"-c", "Compile and assemble, but do not link."}};

void print_usage(FILE *stream, const char *msg) { fputs(msg, stream); }

void print_options(void) {
  printf("Options:\n");
  size_t size = sizeof(options) / sizeof(options[0]);
  for (size_t i = 0; i < size; i++) {
    printf("  %-15s %s\n", options[i].tag, options[i].description);
  }
}

CliArgs parse_cli_args(int argc, char **argv) {
  CliArgs result = {0};

  for (int i = 1; i < argc; ++i) {
    const char *arg = argv[i];

    if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
      print_usage(stdout, "Usage: komiC [options] filename...\n");
      print_options();
      exit(0);
    } else if (strcmp(arg, "--lex") == 0) {
      result.stop_after_lexer = true;
    } else if (strcmp(arg, "--parse") == 0) {
      result.stop_after_parser = true;
    } else if (strcmp(arg, "--validate") == 0) {
      result.stop_after_semantic_analysis = true;
    } else if (strcmp(arg, "--codegen") == 0) {
      result.codegen_only = true;
    } else if (strcmp(arg, "-S") == 0) {
      result.compile_only = true;
    } else if (strcmp(arg, "-c") == 0) {
      result.stop_before_linker = true;
    } else if (strcmp(arg, "-") == 0) {
      (void)print_usage(
          stderr,
          "komiC: fatal error: unrecognized command-line option: '%.*s'\n");
      exit(1);
    } else {
      // TODO: support more than one source file
      result.source_filename = argv[i];
    }
  }

  if (argc < 2) {
    print_usage(stderr, "komiC: fatal error: no input files\n");
    exit(1);
  }

  return result;
}
