#include <stdio.h>

#define IMPORT_FROM_AQUA
#include "../../aqua.h"

int main()
{
    string s;
    int has_term;
    int lcount = 0;
    int wcount = 0;
    int ccount = 0;
    int inspace = 1;
    char c;

    while ((s = getline(stdin, &has_term))) {
        for (int i = 0; i < s->len; i++) {
            c = s->data[i];
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
                inspace = 1;
            } else {
                if (inspace)
                    wcount++;
                inspace = 0;
            }
        }
        ccount += s->len;
        if (has_term)
            lcount++;
        sdestroy(s);
    }

    printf("%d %d %d\n", lcount, wcount, ccount);
    return 0;
}