#include <stdio.h>
#include <stdlib.h>
#include <bstrlib.h>

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

bstring base_bfromcstr(const char *str)
{
    bstring s = bfromcstr(str);
    if (!s)
        base_fatal(OUT_OF_MEMORY);
    return s;
}

char *base_bstr2cstr(const_bstring s, char z)
{
    char *str = bstr2cstr(s, z);
    if (!str)
        base_fatal(OUT_OF_MEMORY);
    return str;
}

bstring base_bstrcpy(const_bstring s)
{
    bstring s2 = bstrcpy(s);
    if (!s2)
        base_fatal(OUT_OF_MEMORY);
    return s2;
}
