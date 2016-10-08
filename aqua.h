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

aqua_string_builder aqua_sbcreate();
void aqua_sbaddchar(aqua_string_builder b, char c);
void aqua_sbaddcstr(aqua_string_builder b, char *str);
void aqua_sbadds(aqua_string_builder b, aqua_string s);
aqua_string aqua_sb2s(aqua_string_builder b);
char *aqua_s2cstr(aqua_string s);
aqua_string aqua_cstr2s(char *cstr);
void aqua_sbdestroy(aqua_string_builder b);
void aqua_sdestroy(aqua_string s);

aqua_string aqua_getline(FILE *fp);

#ifdef IMPORT_FROM_AQUA

#define fatal aqua_fatal
#define malloc aqua_malloc
#define realloc aqua_realloc

#define string aqua_string
#define string_builder aqua_string_builder
#define sbcreate aqua_sbcreate
#define sbaddchar aqua_sbaddchar
#define sbaddcstr aqua_sbaddcstr
#define sbadds aqua_sbadds
#define sb2s aqua_sb2s
#define s2cstr aqua_s2cstr
#define cstr2s aqua_cstr2s
#define sbdestroy aqua_sbdestroy
#define sdestroy aqua_sdestroy

#define getline aqua_getline

#endif