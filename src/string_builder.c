#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/aqua/aqua.h"

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

EXPORT void a_sbldaddcstr(a_string_builder b, const char *str)
{
    while (*str) {
        a_sbldaddchar(b, *str);
        str++;
    }
}

EXPORT void a_sbldadds(a_string_builder b, a_string s)
{
    a_sbldaddmem(b, s->data, s->len);
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

/*
    sqlformat(const a_string query, &a_string out, a_string error, const variable...) => (1 if successful, otherwise 0)

    if there are single or double quotes in the query, then return 0 and set error
    if there are more parameters than variables then return 0 and set error
    otherwise set out to the query with parameters replaced with variables surrounded by single quotes
*/

EXPORT a_string a_sqlformat(a_string query, a_string *errorptr, ...)
{
    va_list ap;
    a_string_builder b;
    a_string value;

    *errorptr = NULL;
    b = a_sbldcreate();
    va_start(ap, errorptr);
    for (int i = 0; i < query->len; i++) {
        switch (query->data[i]) {
            case '?':
                value = va_arg(ap, a_string);
                a_sbldaddchar(b, '\'');
                a_sbldadds(b, a_sqlescape(value));
                a_sbldaddchar(b, '\'');
                break;
            case '\'':
            case '"':
                va_end(ap);
                *errorptr = a_cstr2s("Quotes are not allowed; use a parameter instead.");
                a_sblddestroy(b);
                return NULL;
                break;
            default:
                a_sbldaddchar(b, query->data[i]);
                break;
        }
    }
    va_end(ap);
    return a_sbld2s(b);
}

EXPORT a_string a_sqlescape(a_string s)
{
    a_string_builder b;
    b = a_sbldcreate();

    for (int i = 0; i < s->len; i++) {
        if (s->data[i] == '\'') {
            a_sbldaddcstr(b, "''");
        } else {
            a_sbldaddchar(b, s->data[i]);
        }
    }
    return a_sbld2s(b);
}

EXPORT void a_sbldaddlen(a_string_builder b, unsigned int len)
{
    b->len += len;
    if (b->len > b->mlen) {
        b->mlen += MAX(len, CHUNK);
        b->data = a_realloc(b->data, b->mlen);
    }
}

EXPORT a_string a_itoa(int i)
{
    a_string_builder b;
    int shifter;
    unsigned int len = 0;
    
    b = a_sbldcreate();
    if (i < 0) {
        a_sbldaddchar(b, '-');
        i *= -1;
    }
    len += b->len;
    
    shifter = i;
    do {
        len++;
        shifter /= 10;
    } while (shifter);
    a_sbldaddlen(b, len - b->len);

    do {
        b->data[--len] = (i % 10) + '0';
        i /= 10;
    } while (i);

    return a_sbld2s(b);
}

EXPORT a_string a_leftpad(a_string s, int num, char c)
{
    a_string_builder b;
    b = a_sbldcreate();
    for (int i = 0; i < num - s->len; i++)
        a_sbldaddchar(b, c);
    a_sbldadds(b, s);
    return a_sbld2s(b);
}
