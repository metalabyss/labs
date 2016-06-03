#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct _graphEdge;

struct _graphNode
{
    int number;
    //int indeg; //степнь захода вершины
    struct _graphEdge* incoming; //указатель на список входящих рёбер
};

struct _graphEdge
{
    struct _graphNode* from; //указатель на начало ребра
    struct _graphNode* to; //на конец ребра
    struct _graphEdge* next; //указатель на следующий элемент списка
};

struct _graph
{
    //int* colors; //массив цветов
    struct _graphNode* vertices; //массив вершин
};

void insert(Graph** graph, int v, int w, int vertices)
{
    if (!(*graph))
    {
        *graph = (Graph*)malloc(vertices*sizeof(Graph));
        (*graph)->vertices = (GraphNode*)malloc(vertices*sizeof(GraphNode));

        int i;
        for (i = 0; i < vertices; i++)
        {
            ((*graph)->vertices)[i].number = 0;
        }

    }

    Graph* graphPtr = *graph;
    GraphNode* vNode = (graphPtr->vertices) + v - 1; //не вылазим за границы массива
    GraphNode* wNode = (graphPtr->vertices) + w - 1;

    //инициализация начала ребра
    if (!(vNode->number))
    {
        vNode->number = v;
        vNode->incoming = NULL;
    }

    //нового ребра
    GraphEdge* newEdge = (GraphEdge*)malloc(sizeof(GraphEdge));
    newEdge->from = vNode;
    newEdge->to = wNode;
    newEdge->next = NULL;

    //и его конца
    if (!(wNode)->number)
    {
        wNode->number = w;
        wNode->incoming = newEdge;
    }
    else
    {
        if (!wNode->incoming)
        {
            wNode->incoming = newEdge;
        }
        else
        {
            GraphEdge* edge = wNode->incoming;
            while (edge/*->next*/)
            {
                edge = edge->next;
            }
            edge->next = newEdge;
        }
    }
}

int _countOfIncomingEdges(GraphEdge* head)
{
    int count = 0;
    GraphEdge* edge = head;
    while (edge)
    {
        edge = edge->next;
        count++;
    }
    return count;
}

void topologicalSorting(Graph* graph, int vertices)
{
    //идея: находим вершины, в которые ничего не входит
    //условие цикла: нет вершин, в которые ничего не входит
    int* graphColor = (int*)malloc(vertices*sizeof(int));
    int* indeg = (int*)malloc(vertices*sizeof(int));
    Queue* queue = NULL;
    int i;   
    for (i = 0; i < vertices; i++)
    {
        graphColor[i] = WHITE;
        indeg[i] = _countOfIncomingEdges(((graph->vertices) + i)->incoming);
    }

    int countOfRoots = vertices;
    for (i = 0; i < vertices; i++)
    {
        GraphNode* node = (graph->vertices) + i;
        //если в ноду ничего не входит и она не обработана, запускаем обход для неё
        if (!indeg[i])
        {
            pushTail(&queue, node->number);
            graphColor[i] = BLACK;
            countOfRoots--;
            //ищем ноды, в которые идут ребра от этой вершины. избавляемся от ребер и продолжаем поиск для этих вершин
            for (int j = 0; j < vertices; j++)
            {
                if (graphColor[j] == BLACK) continue;
                
                GraphNode* currentNode = (graph->vertices) + j;
                GraphEdge* currentEdge = currentNode->incoming;
                while (currentEdge)
                {
                    if (currentEdge->from == node) indeg[j]--;
                    currentEdge = currentEdge->next;
                }
            }
        }
    }

    if (countOfRoots)
    {
        while (queue) popHead(&queue);
        printf("impossible to sort");
    }
    else
    {
        int number;
        while (queue)
        {
            number = popHead(&queue);
            printf("%d ", number);
        }
    }
}