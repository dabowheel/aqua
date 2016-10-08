#include "../base.h"

void ex1()
{
    base_string s;

    printf("ex1\n");
    s = base_cstr2s("hello world");
    printf("%s\n", s->data);
}

int main()
{
    ex1();
    return 0;
}