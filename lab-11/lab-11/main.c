#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//топологическая сортировка графа

int main()
{
    //инициализация
    int vertices, edges;
    Graph* graph = NULL;

    if (scanf("%d", &vertices) == EOF)
    {
        printf("bad number of lines");
        return;
    }

    if (vertices < 0 || vertices > 1000)
    {
        printf("bad number of vertices");
        return;
    }

    if (scanf("%d", &edges) == EOF)
    {
        printf("bad number of lines");
        return;
    }

    if (edges < 0 || (edges > vertices*(vertices + 1) / 2))
    {
        printf("bad number of edges");
        return;
    }

    int i;
    int v, w;

    for (i = 0; i < edges; i++)
    {
        if (scanf("%d %d", &v, &w) == EOF)
        {
            printf("bad number of lines");
            return;
        }

        if (v < 0 || v > 1000 || w < 0 || w > 1000 || v > vertices || w > vertices)
        {
            printf("bad vertex");
            return;
        }
        else
        {
            insert(&graph, v, w, vertices);
        }
    }

    topologicalSorting(graph, vertices);

    return 0;
}