#ifndef H_LIST

#define H_LIST

typedef struct _list List;

//добавление элемента в начало списка. принимает указатель на начало списка, возвращает ук-тель на новое начало
List* addToList(List*, int, int);

void removeList(List*);

void printList(List*);

#endif // !H_LIST
