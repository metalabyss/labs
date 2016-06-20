#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct _list
{
    int v1;
    int v2;
    struct _list* next;
};


List* addToList(List* head, int v1, int v2)
{
    if (!head)
    {
        head = (List*)malloc(sizeof(List));
        head->v1 = v1;
        head->v2 = v2;
        head->next = NULL;
        return head;
    }
    else
    {
        List* newEl = (List*)malloc(sizeof(List));
        newEl->next = head;
        newEl->v1 = v1;
        newEl->v2 = v2;
        return newEl;
    }
}

void printList(List* head)
{
    if (!head)
    {
        //printf("nothing to print\n");
        return;
    }
    else
    {
        List* currElement = head;
        while (currElement)
        {
            printf("%d %d\n", (currElement->v1 + 1), (currElement->v2 + 1));
            currElement = currElement->next;
        }
    }
}

void removeList(List* head)
{
    if (head)
    {
        removeList(head->next);
        free(head);
    }
}