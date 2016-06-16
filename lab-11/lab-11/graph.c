#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct _graphEdge;

struct _graphNode
{
    int number;
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
    struct _graphNode* vertices; //массив вершин
};


//процедура создания графа без ребер
Graph* create(int vertices)
{
    Graph* graph = (Graph*)malloc(vertices*sizeof(Graph));
    graph->vertices = (GraphNode*)malloc(vertices*sizeof(GraphNode));

    int i;
    for (i = 0; i < vertices; i++)
    {
        (graph->vertices)[i].number = i + 1;
        (graph->vertices)[i].incoming = NULL;
    }
    return graph;
}

void insert(Graph** graph, int v, int w, int vertices)
{
    Graph* graphPtr = *graph;
    GraphNode* vNode = (graphPtr->vertices) + v - 1; //не вылазим за границы массива
    GraphNode* wNode = (graphPtr->vertices) + w - 1;

    //нового ребра
    GraphEdge* newEdge = (GraphEdge*)malloc(sizeof(GraphEdge));
    newEdge->from = vNode;
    newEdge->to = wNode;
    newEdge->next = NULL;

    if (!wNode->incoming)
    {
        wNode->incoming = newEdge;
    }
    else
    {
        GraphEdge* edge = wNode->incoming;
        while (edge->next)
        {
            edge = edge->next;
        }
        edge->next = newEdge;
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

int countOfRoots(int* indeg, int* graphColor, int vertices, int unvisitedVertices)
{
    int count = unvisitedVertices; //количество вершин с ненулевой степенью захода среди непосещенных
    for (int i = 0; i < vertices; i++)
    {
        if (indeg[i] && (graphColor[i] != BLACK)) count--;
    }
    return count;
}

void topologicalSorting(Graph* graph, int vertices)
{
    //идея: находим вершины, в которые ничего не входит
    //условие цикла: нет вершин, в которые ничего не входит
    int* graphColor = (int*)malloc(vertices*sizeof(int));
    int* indeg = (int*)malloc(vertices*sizeof(int)); //массив, в котором содержатся степени захода для каждой вершины
    Queue* queue = NULL;
    int i;
    for (i = 0; i < vertices; i++)
    {
        graphColor[i] = WHITE;
        indeg[i] = _countOfIncomingEdges(((graph->vertices) + i)->incoming);
    }

    int unvisitedVertices = vertices;
    int isNotComplete;
    do
    {
        if (!countOfRoots(indeg, graphColor, vertices, unvisitedVertices)) {
            printf("impossible to sort");
            return;
        }

        for (i = 0; i < vertices; i++)
        {
            GraphNode* node = (graph->vertices) + i;
            //если в ноду ничего не входит и она не обработана, запускаем обход для неё
            if (!indeg[i] && (graphColor[i] != BLACK))
            {
                pushTail(&queue, node->number);
                graphColor[i] = BLACK;
                unvisitedVertices--;
                
                //ищем ноды, в которые идут ребра от этой вершины, удаляем
                for (int j = 0; j < vertices; j++)
                {
                    if (graphColor[j] == BLACK || !indeg[j]) continue;

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
        isNotComplete = countOfRoots(indeg, graphColor, vertices, unvisitedVertices);
    } while (isNotComplete);

    int number;
    while (queue)
    {
        number = popHead(&queue);
        printf("%d ", number);
    }
}