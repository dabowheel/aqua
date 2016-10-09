#define IMPORT_FROM_AQUA
#include "../aqua.h"
#include <criterion/criterion.h>

Test(cstr2s, test) {
    string s = cstr2s("hello");
    cr_assert(strcmp(s->data, "hello") == 0, "string is hello");
    cr_assert(s->len == 5, "length is 5");
    sdestroy(s);
}