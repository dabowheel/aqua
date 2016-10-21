#include "win32.h"
#include "string.h"

typedef struct a_node {
    void *data;
    struct a_node *next;
} *a_node;

EXPORT a_node a_nodeCreate(void *data);
EXPORT a_node a_nodePush(a_node head, a_node node);
EXPORT a_node *a_hashCreate(size_t array_size);
EXPORT int a_hash(a_string key, size_t array_size);
EXPORT void a_hashAdd(a_node *array, a_node item, a_string key, size_t array_size);
