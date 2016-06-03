#ifndef H_GRAPH

#define H_GRAPH

#define WHITE (0)
#define GREY (1)
#define BLACK (-1)

typedef struct _graphNode GraphNode;
typedef struct _graphEdge GraphEdge;
typedef struct _graph Graph;

void insert(Graph**, int, int, int);
Graph* deleteGraph(Graph*);
void topologicalSorting(Graph*, int);

#endif