#define IMPORT_FROM_BASE
#include "../base.h"

void ex1()
{
    string s;

    printf("ex1\n");
    s = cstr2s("hello world");
    printf("%s\n", s->data);
    sdestroy(s);
}

void ex2()
{
    string_builder b;
    string s;
    string s2;
    char *cstr;

    printf("ex2\n");
    b = sbcreate();
    sbaddchar(b, 'a');
    sbaddcstr(b, "bc");
    s2 = cstr2s("de");
    sbadds(b, s2);
    s = sb2s(b);
    printf("%s\n", s->data);
    cstr = s2cstr(s);
    printf("%s\n", cstr);
    free(cstr);
}

int main()
{
    ex1();
    ex2();
    return 0;
}