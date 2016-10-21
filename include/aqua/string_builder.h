#include "win32.h"

typedef struct a_string_builder {
    char *data;
    unsigned int len;
    unsigned int mlen;
} *a_string_builder;

EXPORT a_string a_cstr2s(char *cstr);
EXPORT a_string a_nextPiece(a_string s, char delim, int *posptr);
EXPORT a_string_builder a_sbldcreate();
EXPORT void a_sbldaddchar(a_string_builder b, char c);
EXPORT void a_sbldaddcstr(a_string_builder b, char *str);
EXPORT void a_sbldadds(a_string_builder b, a_string s);
EXPORT void a_sbldaddmem(a_string_builder b, char *buffer, size_t size);
EXPORT a_string a_sbld2s(a_string_builder b);
EXPORT void a_sblddestroy(a_string_builder b);
EXPORT a_string a_getline(FILE *fp, int *has_term);
