#include <stdio.h>
#include <bstrlib.h>
#include "mem.h"

int main()
{
    bstring s;
    char *str;
    bstring s2;
    bstring s3;

    s = xfromcstr("hello bstring");
    printf("%s\n", s->data);

    str = xbstr2cstr(s, '\0');
    printf("%s\n", str);

    s2 = xstrcpy(s);
    printf("%s\n", s2->data);

    s3 = xfromcstr("abc: ");
    if (bconcat(s3, s2) == BSTR_ERR)
        printf("Error\n");
    else
        printf("%s\n", s3->data);

    bdestroy(s);
    bdestroy(s2);
    bdestroy(s3);
    bcstrfree(str);
    return 0;
}
