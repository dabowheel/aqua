#include <string.h>
#include <aqua/link.h>
#include <aqua/util.h>
#include <aqua/win32.h>

EXPORT a_link a_linkCreate(void *data)
{
    a_link link = a_malloc(sizeof(struct a_link));
    link->data = data;
    link->next = NULL;
    return link;
}

EXPORT a_link a_linkPush(a_link head, a_link link)
{
    link->next = head;
    return link;
}

EXPORT void a_lMap(a_link head, void (*func) (a_link))
{
    while (head) {
        func(head);
        head = head->next;
    }
}
