#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#define CHUNK 100

size_t base_getline(char **lineptr, FILE *fp)
{
    int c;
    size_t size = CHUNK;
    int i = 0;

    *lineptr = base_malloc(size);
    while ((c = fgetc(fp)) != EOF) {
        if (i >= size) {
            size += CHUNK;
            *lineptr = base_realloc(*lineptr, size);
        }
        (*lineptr)[i++] = c;
        if (c == '\n')
            break;
    }
    *lineptr = base_realloc(*lineptr, i+1);
    (*lineptr)[i] = '\0';
    return i;
}
