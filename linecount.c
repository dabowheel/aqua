#include "base.h"
#include "import_base.h"

int main()
{
    char *line;
    int count = 0;
    while (getline(&line, stdin)) {
        count++;
    }

    printf("line count is %d\n", count);
    return 0;
}