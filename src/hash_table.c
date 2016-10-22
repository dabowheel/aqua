#include <stdio.h>
#include <string.h>
#include <aqua/win32.h>
#include <aqua/string.h>
#include <aqua/hash_table.h>
#include <aqua/util.h>

/* 
    Public
    Create a hash table
*/
EXPORT a_hash_table a_htCreate(size_t array_size)
{
    a_hash_table t;
    t = a_malloc(sizeof(struct a_hash_table));
    t->array = a_malloc(sizeof(a_hash_item) * array_size);
    memset(t->array, 0, sizeof(a_hash_item) * array_size);
    t->array_size = array_size;
    return t;
}

/*
    Private
    Create a hash item
*/
a_hash_item a_hiCreate(a_string key, a_string value)
{
    a_hash_item item = a_malloc(sizeof(struct a_hash_item));
    item->key = key;
    item->value = value;
    item->next = NULL;
    return item;
}

/*
    Private
    Push a hash item on the list
*/
a_hash_item a_linkPush(a_hash_item head, a_hash_item item)
{
    item->next = head;
    return item;
}

/*
    Private
    Execute a function every item of the list
*/
void a_lMap(a_hash_item head, void (*func) (a_hash_item))
{
    while (head) {
        func(head);
        head = head->next;
    }
}

/*
    Private
    Get the hash for this key and array size
*/
int a_htHash(a_string key, size_t array_size)
{
    int value = 0;
    for (int i = 0; i < 10 && i < key->len; i++) {
        value += key->data[i];
        value %= array_size;
    }
    return value;
}

/*
    Public
    Set a value in the hash table
*/
EXPORT void a_htSet(a_hash_table t, a_string key, a_string value)
{
    a_hash_item item = a_hiCreate(key, value);
    int hash = a_htHash(key, t->array_size);
    t->array[hash] = a_linkPush(t->array[hash], item);
}

/*
    Public
    Get a value in the hash table, NULL if key not found
*/
EXPORT a_string a_htGet(a_hash_table t, a_string key)
{
    int hash = a_htHash(key, t->array_size);
    a_hash_item item = t->array[hash];
    a_string value = NULL;

    while (item) {
      if (strcmp(item->key->data, key->data) == 0) {
        value = item->value;
        break;
      }
      item = item->next;
    }

    return value;
}

/*
    Public
    Execute a function on each item of the hash table
*/
EXPORT void a_htMap(a_hash_table table, void (*func) (a_hash_item))
{
    for (int i = 0; i < table->array_size; i++) {
        a_lMap(table->array[i], func);
    }
}

/*
    Public
    Function to print a hash item; used with a_htMap
*/
EXPORT void a_htPrint(a_hash_item item)
{
    printf("%s=%s\n", item->key->data, item->value->data);
}

/*
    Public
    Destroy the hash table
*/
EXPORT void a_htDestroy(a_hash_table table)
{
    for (int i = 0; i < table->array_size; i++) {
        a_hash_item item = table->array[i];
        while (item) {
            a_hash_item next = item->next;
            a_sdestroy(item->key);
            a_sdestroy(item->value);
            free(item);
            item = next;
        }
    }
    free(table->array);
    free(table);
}