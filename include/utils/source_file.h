#ifndef KOMI_SOURCE_FILE_H
#define KOMI_SOURCE_FILE_H

#include <stddef.h>

typedef struct SourceFile {
  const char *data;
  size_t size;
} SourceFile;

SourceFile mmap_file(const char *filename);
void unmap_file(SourceFile *source);

#endif
