#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct _graphVertex
{
    int number;
    struct _graphVertex* adjacentVertex; //список смежных вершин
};

struct _graph
{
    int* colors;
    struct _graphVertex* vertices;
};

void insert(GraphVertex** graph, int** colors, int v, int w, int vertices)
{
    GraphVertex* graphPtr = *graph;
    int* colorsArr = *colors;
    if (!graphPtr)
    {
        *graph = (GraphVertex*)malloc(vertices*sizeof(GraphVertex));
        graphPtr = *graph;
        
        for (int i = 0; i < vertices; i++)
        {
            colorsArr[i] = WHITE;
            graphPtr[i].adjacentVertex = NULL;
            graphPtr[i].number = 0;
        }
    }

    if (!graphPtr[v - 1].number)
    {
        graphPtr[v - 1].number = w;
    }
    else
    {
        GraphVertex* tmp = (GraphVertex*)malloc(sizeof(GraphVertex));
        tmp->adjacentVertex = graphPtr[v - 1].adjacentVertex;
        tmp->number = w;
        graphPtr[v - 1].adjacentVertex = tmp;
    }
}

int dfs(GraphVertex* graph, int** colors, int vertex, Stack** stack, int vertices)
{
    int* colorsArr = *colors;

    if (colorsArr[vertex - 1] == GREY)
    {
        return 1;
    }
    else if (colorsArr[vertex - 1] == BLACK)
    {
        return 0;
    }

    //assert(graph + vertex < graph + vertices);
    colorsArr[vertex - 1] = GREY;
    GraphVertex* v = &graph[vertex - 1];

    while ((v) && (v->number != 0))
    {
        if (dfs(graph, colors, v->number, stack, vertices) == 1) return 1; //условие цикла
        v = v->adjacentVertex;
    }

    colorsArr[vertex - 1] = BLACK;
    *stack = push(*stack, vertex);

    return 0;
}