#include <stdio.h>
#include "external/bstrlib/bstrlib.h"

int main()
{
    bstring s = bfromcstr("hello bstring");
    char *cstr = bstr2cstr(s, '\0');

    printf("%s\n", cstr);
    bdestroy(s);
    bcstrfree(cstr);
    return 0;
}