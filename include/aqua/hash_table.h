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

EXPORT a_hash_table a_htCreate(size_t array_size);
EXPORT int a_htHash(a_string key, size_t array_size);
EXPORT a_hash_item a_hiCreate(a_string key, void *data);
EXPORT void a_htSet(a_hash_table t, a_string key, void *data);
EXPORT void *a_htGet(a_hash_table t, a_string key);
EXPORT void a_htMap(a_hash_table table, void (*func) (a_link));

#endif
