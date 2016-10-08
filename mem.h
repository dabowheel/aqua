#include <bstrlib.h>

void fatal(char *error);
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t newsize);
bstring xfromcstr(const char *str);
char *xbstr2cstr(const_bstring s, char z);
bstring xstrcpy(const_bstring s);
