#include "queue.h"
#include <stdlib.h>

struct _node
{
    int value;
    struct _node *next;
};

struct _queue
{
    struct _node* tail;
    struct _node* head;
};

void pushTail(Queue** queue, int value)
{
    struct _node* newNode = (struct _node*)malloc(sizeof(struct _node));
    newNode->next = NULL;
    newNode->value = value;

    if (!(*queue))
    {
        *queue = (Queue*)malloc(sizeof(Queue));
        (*queue)->head = newNode;
    }
    else
	{
		(*queue)->tail->next = newNode;
	}
	(*queue)->tail = newNode;
}

int popHead(Queue** queue)
{
	struct _node *tmp = NULL; //создаём вспомогат. указатель
	tmp = (*queue)->head;
	int value = tmp->value;

	(*queue)->head = (*queue)->head->next;

    if (!(*queue)->head)
    {
        free(*queue);
        *queue = NULL;
    }
	free(tmp);
	return value;
}