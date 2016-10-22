#ifndef AQUA_HASH_TABLE_H
#define AQUA_HASH_TABLE_H

#include <aqua/string.h>

typedef struct a_hash_item {
    a_string key;
    a_string value;
    struct a_hash_item *next;
} *a_hash_item;

typedef struct a_hash_table {
  a_hash_item *array;
  size_t array_size;
} *a_hash_table;

EXPORT a_hash_table a_htCreate(size_t array_size);
EXPORT void a_htSet(a_hash_table t, a_string key, a_string value);
EXPORT a_string a_htGet(a_hash_table t, a_string key);
EXPORT void a_htMap(a_hash_table table, void (*func) (a_hash_item));
EXPORT void a_htPrint(a_hash_item item);
EXPORT void a_htDestroy(a_hash_table table);

#endif
