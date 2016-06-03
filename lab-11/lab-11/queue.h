typedef struct _queue Queue;

//здесь и далее предполагаем, что проверка на то, что очередь не пуста, уже выполнена

//добавить в хвост
void pushTail(Queue** queue, int value);

//столкнуть с вершины
int popHead(Queue** queue);