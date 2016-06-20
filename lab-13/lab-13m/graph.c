#include "graph.h"
#include "list.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define INF UINT_MAX
#define EMPTY (INT_MAX + 1) //это уже исключенные из очереди вершины

unsigned int** createGraph(int vertices)
{
    unsigned int** graphMatrix = (unsigned int**)calloc(vertices, sizeof(unsigned int*));
    int i, j;
    for (i = 0; i < vertices; i++)
    {
        graphMatrix[i] = (unsigned int*)calloc(vertices, sizeof(unsigned int));
        for (j = 0; j < vertices; j++)
            graphMatrix[i][j] = INF;
    }
    return graphMatrix;
}

unsigned int _findMinPriorityVertex(unsigned int* arrOfPriorities, int vertices)
{
    int vertex = INF;
    unsigned int minPriority = INF;
    int i;
    for (i = 0; i < vertices; i++)
    {
        if (arrOfPriorities[i] < minPriority && arrOfPriorities[i] != EMPTY)
        {
            minPriority = arrOfPriorities[i];
            vertex = i;
        }
    }
    return vertex;
}

unsigned int* _updateArrOfPriorities(unsigned int* arrOfPriorities, int vertices, int min, unsigned int** graphMatrix)
{
    int i;
    for (i = 0; i < vertices; i++)
    {
        if ((arrOfPriorities[i] != EMPTY) && (graphMatrix[min][i] < arrOfPriorities[i]))
            arrOfPriorities[i] = graphMatrix[min][i];
    }
    return arrOfPriorities;
}

void primFindMst(unsigned int** graphMatrix, int vertices) //minimum spanning tree
{
    unsigned int* arrOfPriorities = (unsigned int*)calloc(vertices, sizeof(unsigned int));
    int i, j;
    List* list = NULL;

    for (i = 1; i < vertices; i++)
    {
        arrOfPriorities[i] = INF;
    }

    arrOfPriorities[0] = 0;
    unsigned int v;
    for (i = 0; i < vertices; i++)
    {
        v = _findMinPriorityVertex(arrOfPriorities, vertices);
        if (v == INF) //если остались непросмотренные вершины, значит остовное дерево не сущ.
        {
            //удаляем всё
            removeList(list);
            printf("no spanning tree");
            return;
        }
        unsigned int priority = arrOfPriorities[v];

        //поиск конца ребра
        for (j = 0; j < vertices; j++)
        {
            if ((graphMatrix[v][j] == priority) && (arrOfPriorities[j] == EMPTY))
            {
                list = addToList(list, v, j);
                break;
            }
        }
        arrOfPriorities[v] = EMPTY;
        arrOfPriorities = _updateArrOfPriorities(arrOfPriorities, vertices, v, graphMatrix);
    }
    printList(list);
    //deletegraph
    removeList(list);
    free(arrOfPriorities);
}