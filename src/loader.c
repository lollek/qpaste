#include "loader.h"

void load_file(char **dataptr, const char *filename) {
  
  size_t filesize;
  FILE *fd = fopen(filename, "rb");

  if (fd == NULL) {
    fprintf(stderr, "Failed to open %s\n", filename);
    return;
  }

  fseek(fd, 0L, SEEK_END);
  filesize = ftell(fd);
  fseek(fd, 0L, SEEK_SET);

  *dataptr = (char *)realloc(*dataptr, filesize);
  if (*dataptr == NULL) {
    fprintf(stderr, "malloc failed!\n");
    return;
  }

  fread(*dataptr, 1, filesize, fd);
  fclose(fd);
}

void unload_file(char **dataptr) {
  free(*dataptr);
  *dataptr = NULL;
}

int fetchln(char **lineptr, size_t *n, char **dataptr) {
  char *c = NULL;
  
  *n = 0;
  for (c = *dataptr; *c != '\n' && *c != '\0'; c++, (*n)++);

  if (*c == '\0' && *n == 0) {
    free(*lineptr);
    return -1;
  } else {
    *lineptr = (char *)realloc(*lineptr, ++(*n) + 1);
    strncpy(*lineptr, *dataptr, *n);
    *(*lineptr + *n) = '\0';
    *dataptr = *c == '\n'? *dataptr + *n : *dataptr + *n -1;
    return *n;
  }
}

void update_all(mylist_t *root, const char *filename) {
  int current_index = 0;
  char *fileroot = NULL, *fileptr = NULL, *line = NULL;
  size_t size;
  
  load_file(&fileroot, filename);
  fileptr = fileroot;

  while (fetchln(&line, &size, &fileptr) != -1) {
    if (size >= 7 && !strncmp(line, "~split~", 7))
      mylist::add_new(root, ++current_index);
    else if (current_index == 0)
      continue;
    else
      mylist::add_data(root, current_index, line);
  }

  unload_file(&fileroot);

}
