#include <aqua/aqua.h>

void ex1()
{
    a_string s;

    printf("ex1\n");
    s = a_cstr2s("hello world");
    printf("%s\n", s->data);
    a_sdestroy(s);
}

void ex2()
{
    a_string_builder b;
    a_string s;
    a_string s2;
    char *cstr;

    printf("ex2\n");
    b = a_sbldcreate();
    a_sbldaddchar(b, 'a');
    a_sbldaddcstr(b, "bc");
    s2 = a_cstr2s("de");
    a_sbldadds(b, s2);
    s = a_sbld2s(b);
    printf("%s\n", s->data);
    cstr = a_s2cstr(s);
    printf("%s\n", cstr);
    free(cstr);
}

int main()
{
    ex1();
    ex2();
    return 0;
}