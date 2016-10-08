#include <bstrlib.h>

void base_fatal(char *error);
void *base_malloc(size_t size);
void *base_realloc(void *ptr, size_t newsize);
bstring base_bfromcstr(const char *str);
char *base_bstr2cstr(const_bstring s, char z);
bstring base_bstrcpy(const_bstring s);
