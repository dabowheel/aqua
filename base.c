#include "base.h"

#define OUT_OF_MEMORY "Out of memory"
#define CHUNK 100

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

void base_sbreset(base_string_builder b)
{
    b->data = base_malloc(CHUNK);
    b->len = 0;
    b->mlen = CHUNK;
}

void base_sbaddchar(base_string_builder b, char c)
{
    if(b->len + 1 > b->mlen) {
        b->mlen += CHUNK;
        base_realloc(b->data, b->mlen);
    }
    b->data[b->len++] = c;
}

void base_sbaddcstr(base_string_builder b, char *str)
{
    while (*str) {
        base_sbaddchar(b, *str);
        str++;
    }
}

void base_sbadds(base_string_builder b, base_string s)
{
    char *cstr;
    cstr = base_s2cstr(s);
    base_sbaddcstr(b, cstr);
}

base_string base_sb2s(base_string_builder b)
{
    base_string s = base_malloc(sizeof(struct base__string__));
    s->len = b->len;
    base_sbaddchar(b, '\0');
    s->data = b->data;
    b->data = NULL;
    base_sbdestroy(b);
    return s;
}

char *base_s2cstr(base_string s)
{
    char *cstr;
    cstr = s->data;
    s->data = NULL;
    base_sdestroy(s);
    return cstr;
}

base_string base_cstr2s(char *cstr)
{
    base_string_builder b = base_malloc(sizeof(struct base__string_builder__));

    base_sbreset(b);
    base_sbaddcstr(b, cstr);
    return base_sb2s(b);
}

void base_sbdestroy(base_string_builder b)
{
    if (b) {
        if (b->data) {
            free(b->data);
        }
        free(b);
    }
}

void base_sdestroy(base_string s)
{
    if (s) {
        if (s->data) {
            free(s->data);
        }
        free(s);
    }
}

size_t base_getline(char **lineptr, FILE *fp)
{
    int c;
    size_t size = CHUNK;
    int i = 0;

    *lineptr = base_malloc(size);
    while ((c = fgetc(fp)) != EOF) {
        if (i >= size) {
            size += CHUNK;
            *lineptr = base_realloc(*lineptr, size);
        }
        (*lineptr)[i++] = c;
        if (c == '\n')
            break;
    }
    *lineptr = base_realloc(*lineptr, i+1);
    (*lineptr)[i] = '\0';
    return i;
}

