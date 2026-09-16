#include <fcntl.h>
#include <sourceFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

SourceFile map_file(const char *path) {
  int fd = open(path, O_RDONLY);

  if (fd == -1) {
    perror("open");
    exit(1);
  }

  struct stat st;

  if (fstat(fd, &st) == -1) {
    perror("fstat");
    close(fd);
    exit(1);
  }

  if (st.st_size == 0) {
    close(fd);

    return (SourceFile){.data = NULL, .size = 0};
  }

  void *mapped = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

  close(fd);

  if (mapped == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  return (SourceFile){.data = mapped, .size = st.st_size};
}

void unmap_file(SourceFile *source) {
  if (source->data != NULL) {
    munmap((void *)source->data, source->size);
  }
}
