#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "mylist_t.h"

#define CONFIGNAME "paste.cfg"

void update_fileinfo(mylist_t *root) {
  int current_index (0);
  char *line     (NULL);
  FILE *fd       (NULL);
  size_t size;

  /* Open Config */
  fd = fopen(CONFIGNAME, "r");
  if (fd == NULL) {
    std::cerr << "Failed to open " << CONFIGNAME << std::endl;
    return;
  }
  
  /* Parse */
  while (getline(&line, &size, fd) != -1) {
    //if (size >= 5 && line[0] == '#' && line[1] == '#' 
    //&& line[2] == '-' && line[3] == '-')
    //mylist::add_new(root, ++current_index);
    if (size >= 7 && !strncmp(line, "~split~", 7))
      mylist::add_new(root, ++current_index);
    else if (current_index == 0) 
      continue;
    else 
      mylist::add_data(root, current_index, line);
  }
  free(line);
  fclose(fd);
}

int main(void) 
{
  int selector;
  mylist_t *ptr, *root = mylist::init_root();
  update_fileinfo(root);

  std::cout << "Which do you want to show?\n";
  std::cin >> selector;
  
  for (ptr = root; ptr != NULL; ptr = ptr->next)
    if (ptr->num == selector)
      std::cout << ptr->data;

  mylist::rm_root(root);
  return 0;
}
