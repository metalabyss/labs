#ifndef H_GRAPH

#include "stack.h"

#define H_GRAPH

#define WHITE (0)
#define GREY (1)
#define BLACK (-1)

typedef struct _graphVertex GraphVertex;
//typedef struct _graph Graph;

int dfs(GraphVertex*, int**, int, Stack**, int);
void insert(GraphVertex**, int**, int, int, int);
GraphVertex* deleteGraph(GraphVertex*);

#endif