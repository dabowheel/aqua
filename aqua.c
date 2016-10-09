#include "aqua.h"

#define OUT_OF_MEMORY "Out of memory"
#define CHUNK 100

void aqua_fatal(char *error)
{
    printf("%s\n", error);
    exit(1);
}

void *aqua_malloc(size_t size)
{
    void *p;
    p = malloc(size);
    if (!p)
        aqua_fatal(OUT_OF_MEMORY);
    return p;
}

void *aqua_realloc(void *ptr, size_t newsize)
{
    ptr = realloc(ptr, newsize);
    if (!ptr)
        aqua_fatal(OUT_OF_MEMORY);
    return ptr;
}

aqua_string_builder aqua_sbldcreate()
{
    aqua_string_builder b = aqua_malloc(sizeof(struct aqua__string_builder__));
    b->data = aqua_malloc(CHUNK);
    b->len = 0;
    b->mlen = CHUNK;
    return b;
}

void aqua_sbldaddchar(aqua_string_builder b, char c)
{
    if(b->len + 1 > b->mlen) {
        b->mlen += CHUNK;
        aqua_realloc(b->data, b->mlen);
    }
    b->data[b->len++] = c;
}

void aqua_sbldaddcstr(aqua_string_builder b, char *str)
{
    while (*str) {
        aqua_sbldaddchar(b, *str);
        str++;
    }
}

void aqua_sbldadds(aqua_string_builder b, aqua_string s)
{
    char *cstr;
    cstr = aqua_s2cstr(s);
    aqua_sbldaddcstr(b, cstr);
}

aqua_string aqua_sbld2s(aqua_string_builder b)
{
    aqua_string s = aqua_malloc(sizeof(struct aqua__string__));
    s->len = b->len;
    aqua_sbldaddchar(b, '\0');
    s->data = b->data;
    b->data = NULL;
    aqua_sblddestroy(b);
    return s;
}

char *aqua_s2cstr(aqua_string s)
{
    char *cstr;
    cstr = s->data;
    s->data = NULL;
    aqua_sdestroy(s);
    return cstr;
}

aqua_string aqua_cstr2s(char *cstr)
{
    aqua_string_builder b = aqua_sbldcreate();

    aqua_sbldaddcstr(b, cstr);
    return aqua_sbld2s(b);
}

void aqua_sblddestroy(aqua_string_builder b)
{
    if (b) {
        if (b->data) {
            free(b->data);
        }
        free(b);
    }
}

void aqua_sdestroy(aqua_string s)
{
    if (s) {
        if (s->data) {
            free(s->data);
        }
        free(s);
    }
}

aqua_string aqua_getline(FILE *fp)
{
    int c;
    aqua_string_builder b;

    b = aqua_sbldcreate();
    while ((c = fgetc(fp)) != EOF) {
        aqua_sbldaddchar(b, c);
        if (c == '\n')
            break;
    }
    if (b->len == 0) {
        aqua_sblddestroy(b);
        return NULL;
    }
    return aqua_sbld2s(b);
}
