#ifndef LOADER_H_
#define LOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylist_t.h"

/**
 * Loads file to RAM
 * @param dataptr address of pointer where to store the data
 * @param filename filename of file to open
 */
void load_file(char **dataptr, const char *filename);

/**
 * Unloads file from RAM
 * @param dataptr address of pointer where the data is stored
 */
void unload_file(char **dataptr);

/**
 * Works like GNU getline (on array instead of file descriptor)
 * @param lineptr address where we store the line
 * @param n size of line
 * @param dataptr address where the data is stored
 */
int fetchln(char **lineptr, size_t *n, char **dataptr);

/**
 * Loads data from file and turns it into mylist_t linked list
 * @param root linked list root
 * @param filename name of file to open
 */
void update_all(mylist_t *root, const char *filename);

#endif //LOADER_H_
