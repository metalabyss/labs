#ifndef H_GRAPH

#define H_GRAPH

#define UNVISITED (0)
#define VISITED (1)

typedef struct _graphNode GraphNode;
typedef struct _graphEdge GraphEdge;
typedef struct _graph Graph;

Graph* create(int);
void insert(Graph**, int, int, int);
Graph* deleteGraph(Graph*);
void topologicalSorting(Graph*, int);

#endif