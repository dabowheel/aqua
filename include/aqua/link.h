#ifndef AQUA_LINK_H
#define AQUA_LINK_H

#include "win32.h"
#include "string.h"

typedef struct a_link {
    void *data;
    struct a_link *next;
} *a_link;

EXPORT a_link a_linkCreate(void *data);
EXPORT a_link a_linkPush(a_link head, a_link link);

#endif
