#include <stdio.h>
#include <aqua/win32.h>
#include <aqua/string.h>
#include <aqua/hash_table.h>
#include <aqua/util.h>
#include <aqua/link.h>
#include <string.h>

EXPORT a_hash_table a_hashCreate(size_t array_size)
{
    a_hash_table t;
    t = a_malloc(sizeof(struct a_hash_table));
    t->array = a_malloc(sizeof(a_link) * array_size);
    memset(t->array, 0, sizeof(a_link) * array_size);
    return t;
}

EXPORT int a_hash(a_string key, size_t array_size)
{
    int value = 0;
    for (int i = 0; i < 10 && i < key->len; i++) {
        value += key->data[i];
        value %= array_size;
    }
    return value;
}

EXPORT a_hash_item a_hash_itemCreate(a_string key, void *data)
{
  a_hash_item item = a_malloc(sizeof(struct a_hash_item));
  item->key = key;
  item->data = data;
  return item;
}

EXPORT void a_hashSet(a_hash_table t, a_string key, void *data)
{
    a_hash_item item = a_hash_itemCreate(key, data);
    a_link l = a_linkCreate(item);
    int hash = a_hash(key, t->array_size);
    t->array[hash] = a_linkPush(t->array[hash], l);
}

EXPORT void *a_hashGet(a_hash_table t, a_string key)
{
    int hash = a_hash(key, t->array_size);
    a_link l = t->array[hash];
    void *data = NULL;

    while (l)
    {
      a_hash_item item = l->data;
      if (strcmp(item->key->data, key->data) == 0) {
        data = item->data;
        break;
      }
      l = l->next;
    }

    return data;
}
