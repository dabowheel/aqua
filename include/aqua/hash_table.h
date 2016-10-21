#ifndef AQUA_HASH_TABLE_H
#define AQUA_HASH_TABLE_H

#include <aqua/link.h>

typedef struct a_hash_table {
  a_link *array;
  size_t array_size;
} *a_hash_table;

typedef struct a_hash_item {
  a_string key;
  void *data;
} *a_hash_item;

#endif
