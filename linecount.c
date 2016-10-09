#include <stdio.h>

#define IMPORT_FROM_AQUA
#include "aqua.h"

int main()
{
    string s;
    int has_term;
    int count = 0;

    while ((s = getline(stdin, &has_term))) {
        if (has_term)
            count++;
        sdestroy(s);
    }

    printf("line count is %d\n", count);
    return 0;
}