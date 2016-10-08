#include <stdlib.h>
#include <stdio.h>


void base_fatal(char *error);
void *base_malloc(size_t size);
void *base_realloc(void *ptr, size_t newsize);

typedef struct base__string__ {
    char *data;
    unsigned int len;
} *base_string;

typedef struct base__string_builder__ {
    char *data;
    unsigned int len;
    unsigned int mlen;
} *base_string_builder;

base_string_builder base_sbcreate();
void base_sbaddchar(base_string_builder b, char c);
void base_sbaddcstr(base_string_builder b, char *str);
void base_sbadds(base_string_builder b, base_string s);
base_string base_sb2s(base_string_builder b);
char *base_s2cstr(base_string s);
base_string base_cstr2s(char *cstr);
void base_sbdestroy(base_string_builder b);
void base_sdestroy(base_string s);

base_string base_getline(FILE *fp);

#ifdef IMPORT_FROM_BASE

#define fatal base_fatal
#define malloc base_malloc
#define realloc base_realloc

#define string base_string
#define string_builder base_string_builder
#define sbcreate base_sbcreate
#define sbaddchar base_sbaddchar
#define sbaddcstr base_sbaddcstr
#define sbadds base_sbadds
#define sb2s base_sb2s
#define s2cstr base_s2cstr
#define cstr2s base_cstr2s
#define sbdestroy base_sbdestroy
#define sdestroy base_sdestroy

#define getline base_getline

#endif