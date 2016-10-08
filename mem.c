#include <stdio.h>
#include <stdlib.h>

#define OUT_OF_MEMORY "Out of memory"

void base_fatal(char *error)
{
    printf("%s\n", error);
    exit(1);
}

void *base_malloc(size_t size)
{
    void *p;
    p = malloc(size);
    if (!p)
        base_fatal(OUT_OF_MEMORY);
    return p;
}

void *base_realloc(void *ptr, size_t newsize)
{
    ptr = realloc(ptr, newsize);
    if (!ptr)
        base_fatal(OUT_OF_MEMORY);
    return ptr;
}
