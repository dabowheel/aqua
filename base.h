#include <stdlib.h>
#include <stdio.h>

typedef struct base__string__ {
    char *data;
    unsigned int len;
} *base_string;

typedef struct base__string_builder__ {
    char *data;
    unsigned int len;
    unsigned int mlen;
} *base_string_builder;

void base_fatal(char *error);
void *base_malloc(size_t size);
void *base_realloc(void *ptr, size_t newsize);

void base_sbreset(base_string_builder b);
void base_sbaddchar(base_string_builder b, char c);
void base_sbaddcstr(base_string_builder b, char *str);
void base_sbadds(base_string_builder b, base_string s);
base_string base_sb2s(base_string_builder b);
char *base_s2cstr(base_string s);
base_string base_cstr2s(char *cstr);
void base_sbdestroy(base_string_builder b);
void base_sdestroy(base_string s);

size_t base_getline(char **lineptr, FILE *fp);

#ifdef IMPORT_BASE

#define fatal base_fatal
#define malloc base_malloc
#define realloc base_realloc
#define getline base_getline

#endif