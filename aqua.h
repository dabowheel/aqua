#include <stdlib.h>
#include <stdio.h>


void aqua_fatal(char *error);
void *aqua_malloc(size_t size);
void *aqua_realloc(void *ptr, size_t newsize);

typedef struct aqua__string__ {
    char *data;
    unsigned int len;
} *aqua_string;

typedef struct aqua__string_builder__ {
    char *data;
    unsigned int len;
    unsigned int mlen;
} *aqua_string_builder;

aqua_string_builder aqua_sbldcreate();
void aqua_sbldaddchar(aqua_string_builder b, char c);
void aqua_sbldaddcstr(aqua_string_builder b, char *str);
void aqua_sbldadds(aqua_string_builder b, aqua_string s);
aqua_string aqua_sbld2s(aqua_string_builder b);
char *aqua_s2cstr(aqua_string s);
aqua_string aqua_cstr2s(char *cstr);
void aqua_sblddestroy(aqua_string_builder b);
void aqua_sdestroy(aqua_string s);

aqua_string aqua_getline(FILE *fp);

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
#define sbdestroy aqua_sblddestroy
#define sdestroy aqua_sdestroy

#define getline aqua_getline

#endif