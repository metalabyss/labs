typedef struct _queue Queue;

//����� � ����� ������������, ��� �������� �� ��, ��� ������� �� �����, ��� ���������

//�������� � �����
void pushTail(Queue** queue, int value);

//��������� � �������
int popHead(Queue** queue);