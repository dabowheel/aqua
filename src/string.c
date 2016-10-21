#include <stdlib.h>
#include <aqua/string.h>

EXPORT char *a_s2cstr(a_string s)
{
    char *cstr;
    cstr = s->data;
    s->data = NULL;
    a_sdestroy(s);
    return cstr;
}

EXPORT void a_sdestroy(a_string s)
{
    if (s) {
        if (s->data) {
            free(s->data);
        }
        free(s);
    }
}
