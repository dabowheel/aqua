#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aqua/win32.h>
#include <aqua/util.h>
#include <aqua/string.h>
#include <aqua/string_builder.h>

#define CHUNK 100
#define MAX(a,b) ((b) > (a)) ? (b) : (a)
#define MIN(a,b) ((b) < (a)) ? (b) : (a)

EXPORT a_string a_cstr2s(char *cstr)
{
    a_string_builder b = a_sbldcreate();

    if (cstr)
        a_sbldaddcstr(b, cstr);
    return a_sbld2s(b);
}

/*
    return the next piece in a delimited string
    *posptr should be set to 0 when passed into the first call and passed in on each call
    *posptr set to -1 if the last piece was returned
*/
EXPORT a_string a_nextPiece(a_string s, char delim, int *posptr)
{
    a_string_builder b;

    if (*posptr < 0) return NULL;
    b = a_sbldcreate();

    while ((*posptr < s->len) && (s->data[*posptr] != delim)) {
        a_sbldaddchar(b, s->data[*posptr]);
        (*posptr)++;
    }

    /* we saw the delim then move past it, otherwise we are done with s */
    if (*posptr < s->len)
        (*posptr)++;
    else
        *posptr = -1;

    return a_sbld2s(b);
}

EXPORT a_string_builder a_sbldcreate()
{
    a_string_builder b = a_malloc(sizeof(struct a_string_builder));
    b->data = a_malloc(CHUNK);
    b->len = 0;
    b->mlen = CHUNK;
    return b;
}

EXPORT void a_sbldaddchar(a_string_builder b, char c)
{
    if(b->len + 1 > b->mlen) {
        b->mlen += CHUNK;
        a_realloc(b->data, b->mlen);
    }
    b->data[b->len++] = c;
}

EXPORT void a_sbldaddcstr(a_string_builder b, char *str)
{
    while (*str) {
        a_sbldaddchar(b, *str);
        str++;
    }
}

EXPORT void a_sbldadds(a_string_builder b, a_string s)
{
    char *cstr;
    cstr = a_s2cstr(s);
    a_sbldaddcstr(b, cstr);
}

EXPORT void a_sbldaddmem(a_string_builder b, char *buffer, size_t size)
{
    size_t new_len = b->len + size;
    size_t new_mlen = b->mlen;

    if (new_len > new_mlen) {
        new_mlen += MAX(new_len - new_mlen, CHUNK);
    }
    b->data = a_realloc(b->data, new_mlen);
    memcpy(&b->data[b->len], buffer, size);
    b->len = new_len;
    b->mlen = new_mlen;
}

EXPORT a_string a_sbld2s(a_string_builder b)
{
    a_string s = a_malloc(sizeof(struct a_string));
    s->len = b->len;
    a_sbldaddchar(b, '\0');
    s->data = b->data;
    b->data = NULL;
    a_sblddestroy(b);
    return s;
}

EXPORT void a_sblddestroy(a_string_builder b)
{
    if (b) {
        if (b->data) {
            free(b->data);
        }
        free(b);
    }
}

EXPORT a_string a_getline(FILE *fp, int *has_term)
{
    int c;
    a_string_builder b;

    if (has_term)
        *has_term = 0;
    b = a_sbldcreate();
    while ((c = fgetc(fp)) != EOF) {
        a_sbldaddchar(b, c);
        if (c == '\n') {
            if (has_term)
                *has_term = 1;
            break;
        }
    }
    if (b->len == 0) {
        a_sblddestroy(b);
        return NULL;
    }
    return a_sbld2s(b);
}
