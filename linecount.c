#include "in.h"

int main()
{
    char *line;
    int count = 0;
    while (bgetline(&line, stdin)) {
        count++;
    }

    printf("line count is %d\n", count);
    return 0;
}