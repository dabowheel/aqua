#include <stdio.h>
#include <stdlib.h>
#define OUT_OF_MEMORY "Out of memory"

void fatal(char *error)
{
    printf("%s\n", error);
    exit(1);
}

void *xmalloc(size_t size)
{
    void *p;
    p = malloc(size);
    if (!p)
        fatal(OUT_OF_MEMORY);
    return p;
}

void *xrealloc(void *ptr, size_t newsize)
{
    ptr = realloc(ptr, newsize);
    if (!ptr)
        fatal(OUT_OF_MEMORY);
    return ptr;
}
