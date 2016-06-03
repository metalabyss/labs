#ifndef H_QUEUE

#define H_QUEUE

typedef struct _queue Queue;

void pushTail(Queue** queue, int value);
int popHead(Queue** queue);

#endif // !H_QUEUE