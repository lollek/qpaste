#include <iostream>

#include "mylist_t.h"

mylist_t *mylist::init_root() {
  mylist_t *root = new mylist_t;
  root->num = -1;
  root->next = NULL;
  return root;
}

void mylist::rm_root(mylist_t *root) {
  mylist_t *kptr, *ptr (root);
  while (ptr != NULL) {
    kptr = ptr;
    ptr = ptr->next;
    delete kptr;
  }
}

void mylist::add_new(mylist_t *root, int index) {
  mylist_t *ptr (root);
  if (ptr == NULL) {
    std::cerr << "NULL root!\n";
    return;
  }
  while (ptr->next != NULL)
    ptr = ptr->next;
  ptr->next = new mylist_t;
  ptr->next->num = index;
}

void mylist::add_data(mylist_t *root, int index, const char* data) {
  mylist_t *ptr (root);
  if (data == NULL) return;
  while (ptr != NULL && ptr->num != index) ptr = ptr->next;
  if (ptr == NULL) return;
  ptr->data.append(data);
}
