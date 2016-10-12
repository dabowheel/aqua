#include "aqua.h"

#define OUT_OF_MEMORY "Out of memory"
#define CHUNK 100

EXPORT void aqua_fatal(char *error)
{
    printf("%s\n", error);
    exit(1);
}

EXPORT void *aqua_malloc(size_t size)
{
    void *p;
    p = malloc(size);
    if (!p)
        aqua_fatal(OUT_OF_MEMORY);
    return p;
}

EXPORT void *aqua_realloc(void *ptr, size_t newsize)
{
    ptr = realloc(ptr, newsize);
    if (!ptr)
        aqua_fatal(OUT_OF_MEMORY);
    return ptr;
}

EXPORT aqua_string_builder aqua_sbldcreate()
{
    aqua_string_builder b = aqua_malloc(sizeof(struct aqua__string_builder__));
    b->data = aqua_malloc(CHUNK);
    b->len = 0;
    b->mlen = CHUNK;
    return b;
}

EXPORT void aqua_sbldaddchar(aqua_string_builder b, char c)
{
    if(b->len + 1 > b->mlen) {
        b->mlen += CHUNK;
        aqua_realloc(b->data, b->mlen);
    }
    b->data[b->len++] = c;
}

EXPORT void aqua_sbldaddcstr(aqua_string_builder b, char *str)
{
    while (*str) {
        aqua_sbldaddchar(b, *str);
        str++;
    }
}

EXPORT void aqua_sbldadds(aqua_string_builder b, aqua_string s)
{
    char *cstr;
    cstr = aqua_s2cstr(s);
    aqua_sbldaddcstr(b, cstr);
}

EXPORT aqua_string aqua_sbld2s(aqua_string_builder b)
{
    aqua_string s = aqua_malloc(sizeof(struct aqua__string__));
    s->len = b->len;
    aqua_sbldaddchar(b, '\0');
    s->data = b->data;
    b->data = NULL;
    aqua_sblddestroy(b);
    return s;
}

EXPORT char *aqua_s2cstr(aqua_string s)
{
    char *cstr;
    cstr = s->data;
    s->data = NULL;
    aqua_sdestroy(s);
    return cstr;
}

EXPORT aqua_string aqua_cstr2s(char *cstr)
{
    aqua_string_builder b = aqua_sbldcreate();

    aqua_sbldaddcstr(b, cstr);
    return aqua_sbld2s(b);
}

EXPORT void aqua_sblddestroy(aqua_string_builder b)
{
    if (b) {
        if (b->data) {
            free(b->data);
        }
        free(b);
    }
}

EXPORT void aqua_sdestroy(aqua_string s)
{
    if (s) {
        if (s->data) {
            free(s->data);
        }
        free(s);
    }
}

EXPORT aqua_string aqua_getline(FILE *fp, int *has_term)
{
    int c;
    aqua_string_builder b;

    *has_term = 0;
    b = aqua_sbldcreate();
    while ((c = fgetc(fp)) != EOF) {
        aqua_sbldaddchar(b, c);
        if (c == '\n') {
            *has_term = 1;
            break;
        }
    }
    if (b->len == 0) {
        aqua_sblddestroy(b);
        return NULL;
    }
    return aqua_sbld2s(b);
}

EXPORT int aqua_regex_compile(regex_t *compiled, char *pattern, int cflags, char **errorptr)
{
    int errcode;

    errcode = regcomp(compiled, pattern, cflags);
    if (errcode) {
        size_t length;
        length = regerror(errcode, compiled, NULL, 0);
        *errorptr = malloc(length);
        regerror(errcode, compiled, *errorptr, length);
        return 0;
    }
    return 1;
}

EXPORT int aqua_regex_exec(regex_t *compiled, char *pattern, int nmatch, int eflags, regmatch_t **matchlistptr, int *ismatchptr, char **errorptr)
{
    int errcode;

    if (nmatch > 0) {
        *matchlistptr = malloc(sizeof(regmatch_t) * nmatch);
    }
    errcode = regexec(compiled, pattern, nmatch, *matchlistptr, eflags);
    *ismatchptr = (errcode == 0);
    if (!*ismatchptr && errcode != REG_NOMATCH) {
        size_t length;
        length = regerror(errcode, compiled, NULL, 0);
        *errorptr = malloc(length);
        regerror(errcode, compiled, *errorptr, length);
        return 0;
    }
    return 1;
}
