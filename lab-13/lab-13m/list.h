#ifndef H_LIST

#define H_LIST

typedef struct _list List;

//���������� �������� � ������ ������. ��������� ��������� �� ������ ������, ���������� ��-���� �� ����� ������
List* addToList(List*, int, int);

void removeList(List*);

void printList(List*);

#endif // !H_LIST
