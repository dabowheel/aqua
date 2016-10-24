#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../include/aqua/aqua.h"

int a_GetRandomSeed(unsigned int *seedptr, a_string *errorptr)
{
  FILE *fp;
  const char *filename = "/dev/random";

  errno = 0;
  fp = fopen(filename, "r");
  if (!fp) {
    *errorptr = a_cstr2s(strerror(errno));
    return 0;
  }

  fread(seedptr, sizeof(unsigned int), 1, fp);

  return 1;
}
