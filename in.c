#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#define CHUNK 100

size_t bgetline(char **lineptr, FILE *fp)
{
    int c;
    size_t size = CHUNK;
    int i = 0;

    *lineptr = xmalloc(size);
    while ((c = fgetc(fp)) != EOF) {
        if (i >= size) {
            size += CHUNK;
            *lineptr = xrealloc(*lineptr, size);
        }
        (*lineptr)[i++] = c;
        if (c == '\n')
            break;
    }
    *lineptr = xrealloc(*lineptr, i+1);
    (*lineptr)[i] = '\0';
    return i;
}
