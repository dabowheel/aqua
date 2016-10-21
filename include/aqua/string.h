#ifndef AQUA_STRING_H
#define AQUA_STRING_H

#include <stdio.h>
#include <aqua/win32.h>

typedef struct a_string {
    char *data;
    unsigned int len;
} *a_string;

EXPORT char *a_s2cstr(a_string s);
EXPORT void a_sdestroy(a_string s);

#endif
