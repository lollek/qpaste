#ifndef MYLIST_H_
#define MYLIST_H_

#include <string>

typedef struct mylist_t {
  int              num;
  std::string      data;
  struct mylist_t *next;
} mylist_t;

namespace mylist {

/**
 * Creates and returns a root struct for mylist_t linked list 
 */
mylist_t *init_root();

/**
 * Frees a root struct and all its links
 * @param root root struct to free
 */
void rm_root(mylist_t *root);

/**
 * Add new link to root struct
 * @param root root struct
 * @param index index of link (e.g. 3 for third)
 */
void add_new(mylist_t *root, int index);

/**
 * Add data to existing link struct
 * @param root root struct
 * @param index index of link to add data to
 * @param data data to append
 */
void add_data(mylist_t *root, int index, const char* data);

}



#endif //MYLIST_H_
