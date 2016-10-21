#include <string.h>
#include <aqua/node.h>
#include <aqua/util.h>
#include <aqua/win32.h>

EXPORT a_node a_nodeCreate(void *data)
{
    a_node node = a_malloc(sizeof(struct a_node));
    node->data = data;
    return node;
}

EXPORT a_node a_nodePush(a_node head, a_node node)
{
    node->next = head;
    return node;
}

EXPORT a_node *a_hashCreate(size_t array_size)
{
    a_node *array;
    array = a_malloc(sizeof(a_node) * array_size);
    memset(array, 0, sizeof(a_node) * array_size);
    return array;
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

EXPORT void a_hashAdd(a_node *array, a_node item, a_string key, size_t array_size)
{
    int hash = a_hash(key, array_size);
    array[hash] = a_nodePush(array[hash], item);
}
