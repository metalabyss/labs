#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*struct _graphEdge;

struct _graphNode
{
    int value;
    int color;
    struct _graphEdge* edges;
};

struct _graphEdge
{
    struct _graphNode* node;
    struct _graphEdge* nextEdge;
};
//здесь лучше пока так не упарываться

*/

/*struct _graphVertex
{
    int number;
    int color;
    struct _graphVertex* adjacentVertices; //список смежных вершин
};*/

void insert(GraphVertex** graph, int v, int w, int vertices)
{
    GraphVertex* graphPtr = *graph;
    if (!graphPtr)
    {
        *graph = (GraphVertex*)malloc(vertices*sizeof(GraphVertex));
        graphPtr = *graph;
        
        for (int i = 0; i < vertices; i++)
        {
            graphPtr[i].color = WHITE;
            graphPtr[i].adjacentVertices = NULL;
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
        tmp->adjacentVertices = graphPtr[v - 1].adjacentVertices;
        tmp->number = w;
        tmp->color = WHITE;
        graphPtr[v - 1].adjacentVertices = tmp;
    }
}

int dfs(GraphVertex** graph, int vertex, Stack** stack, int vertices)
{
    GraphVertex* graphPtr = *graph;
    GraphVertex* v = graphPtr + vertex;

    if (v->color == GREY)
    {
        return 1;
    }
    else if (v->color == BLACK)
    {
        return 0;
    }

    assert(graphPtr + vertex < graphPtr + vertices);
    //v = v->adjacentVertices;
    v->color = GREY;
    graphPtr[vertex].color = GREY;

    while (v->adjacentVertices && v->number)
    {
        if (dfs(graph, v->number - 1, stack, vertices)) return 1;
        v = v->adjacentVertices;
    }

    v->color = BLACK;
    graphPtr[vertex].color = BLACK;
    *stack = push(*stack, vertex);

    return 0;
}