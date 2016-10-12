#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

#ifdef WINAPI
#define EXPORT __declspec (dllexport)
#else
#define EXPORT
#endif

EXPORT void aqua_fatal(char *error);
EXPORT void *aqua_malloc(size_t size);
EXPORT void *aqua_realloc(void *ptr, size_t newsize);

typedef struct aqua__string__ {
    char *data;
    unsigned int len;
} *aqua_string;

typedef struct aqua__string_builder__ {
    char *data;
    unsigned int len;
    unsigned int mlen;
} *aqua_string_builder;

EXPORT aqua_string_builder aqua_sbldcreate();
EXPORT void aqua_sbldaddchar(aqua_string_builder b, char c);
EXPORT void aqua_sbldaddcstr(aqua_string_builder b, char *str);
EXPORT void aqua_sbldadds(aqua_string_builder b, aqua_string s);
EXPORT aqua_string aqua_sbld2s(aqua_string_builder b);
EXPORT char *aqua_s2cstr(aqua_string s);
EXPORT aqua_string aqua_cstr2s(char *cstr);
EXPORT void aqua_sblddestroy(aqua_string_builder b);
EXPORT void aqua_sdestroy(aqua_string s);

EXPORT aqua_string aqua_getline(FILE *fp, int *has_term);

EXPORT int regex_compile(regex_t *compiled, char *pattern, int cflags, char **errorptr);
EXPORT int regex_exec(regex_t *compiled, char *pattern, int nmatch, int eflags, regmatch_t **matchlistptr, int *ismatchptr, char **errorptr);

#ifdef IMPORT_FROM_AQUA

#define fatal aqua_fatal
#define malloc aqua_malloc
#define realloc aqua_realloc

#define string aqua_string
#define string_builder aqua_string_builder
#define sbldcreate aqua_sbldcreate
#define sbldaddchar aqua_sbldaddchar
#define sbldaddcstr aqua_sbldaddcstr
#define sbldadds aqua_sbldadds
#define sbld2s aqua_sbld2s
#define s2cstr aqua_s2cstr
#define cstr2s aqua_cstr2s
#define sblddestroy aqua_sblddestroy
#define sdestroy aqua_sdestroy

#define getline aqua_getline

#define regex_compile aqua_regex_compile
#define regex_exec aqua_regex_exec

#endif