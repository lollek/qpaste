#include <iostream>

#include "mylist_t.h"
#include "loader.h"

#define CONFIGNAME "paste.cfg"

int main(void) 
{
  int selector;
  mylist_t *ptr, *root = mylist::init_root();
  update_all(root, CONFIGNAME);

  std::cout << "Which do you want to show?\n";
  std::cin >> selector;
  
  for (ptr = root; ptr != NULL; ptr = ptr->next)
    if (ptr->num == selector)
      std::cout << ptr->data;

  mylist::rm_root(root);
  return 0;
}
