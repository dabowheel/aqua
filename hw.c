#include <stdio.h>
#include <bstrlib.h>
#include "base.h"
#include "import_base.h"

int main()
{
    bstring s;
    char *str;
    bstring s2;
    bstring s3;

    s = bfromcstr("hello bstring");
    printf("%s\n", s->data);

    str = bstr2cstr(s, '\0');
    printf("%s\n", str);

    s2 = bstrcpy(s);
    printf("%s\n", s2->data);

    s3 = bfromcstr("abc: ");
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
