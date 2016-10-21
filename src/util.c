#include <stdio.h>
#include <stdlib.h>
#include <aqua/win32.h>

#define OUT_OF_MEMORY "Out of memory"

EXPORT void a_fatal(char *error)
{
    printf("%s\n", error);
    exit(1);
}

EXPORT void *a_malloc(size_t size)
{
    void *p;
    p = malloc(size);
    if (!p)
        a_fatal(OUT_OF_MEMORY);
    return p;
}

EXPORT void *a_realloc(void *ptr, size_t newsize)
{
    ptr = realloc(ptr, newsize);
    if (!ptr)
        a_fatal(OUT_OF_MEMORY);
    return ptr;
}
