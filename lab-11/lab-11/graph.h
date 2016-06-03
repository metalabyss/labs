#ifndef H_GRAPH

#include "stack.h"

#define H_GRAPH

#define WHITE (0)
#define GREY (1)
#define BLACK (-1)

//typedef struct _graphVertex GraphVertex;

typedef struct _graphVertex
{
    int number;
    int color;
    struct _graphVertex* adjacentVertices; //список смежных вершин
} GraphVertex;

int dfs(GraphVertex**, int, Stack**, int);
void insert(GraphVertex**, int, int, int);
GraphVertex* deleteGraph(GraphVertex*);

#endif