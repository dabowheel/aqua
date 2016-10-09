#define IMPORT_FROM_AQUA
#include "../aqua.h"
#include <criterion/criterion.h>

Test(string, cstr2s) {
    string s = cstr2s("hello");

    cr_assert(strcmp(s->data, "hello") == 0, "string is hello");
    cr_assert(s->len == 5, "length is 5");
    sdestroy(s);
}

Test(string_builder, sbldaddchar) {
    string_builder b;
    string s;
    char *cstr;

    b = sbldcreate();
    sbldaddchar(b, 'a');
    s = sbld2s(b);
    cstr = s2cstr(s);

    cr_assert(strcmp(cstr, "a") == 0, "check we can add a char to string builder");
    free(cstr);
}

Test(string_builder, sbldadds) {
    string_builder b;
    string s;
    string s2;
    char *cstr;

    b = sbldcreate();
    s = cstr2s("abc");
    sbldadds(b, s);
    s2 = sbld2s(b);
    cstr = s2cstr(s2);

    cr_assert(strcmp(cstr, "abc") == 0, "check we can add a string to string builder");
    free(cstr);    
}