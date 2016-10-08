#include <stdio.h>
#include <stdlib.h>
#include <bstrlib.h>
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

bstring xfromcstr(const char *str)
{
    bstring s = bfromcstr(str);
    if (!s)
        fatal(OUT_OF_MEMORY);
    return s;
}

char *xbstr2cstr(const_bstring s, char z)
{
    char *str = bstr2cstr(s, z);
    if (!str)
        fatal(OUT_OF_MEMORY);
    return str;
}

bstring xstrcpy(const_bstring s)
{
    bstring s2 = bstrcpy(s);
    if (!s2)
        fatal(OUT_OF_MEMORY);
    return s2;
}
