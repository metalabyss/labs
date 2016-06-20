#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include <stdio.h>

int main()
{
    int vertices, edges;

    if (scanf("%d", &vertices) == EOF)
    {
        printf("bad number of lines");
        return;
    }

    if (vertices < 0 || vertices > 5000)
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

    if (!vertices)
    {
        printf("no spanning tree");
        return;
    }

    int i;
    int v, w, weight;
    int** graphMatrix = createGraph(vertices);

    for (i = 0; i < edges; i++)
    {
        if (scanf("%d %d %d", &v, &w, &weight) == EOF)
        {
            printf("bad number of lines");
            return;
        }

        if (v < 1 || v > vertices || w < 1 || w > vertices)
        {
            printf("bad vertex");
            return;
        }
        else if (weight < 0)
        {
            printf("bad length");
            return;
        }
        else
        {
            //вставка ребра - тривиальна
            graphMatrix[v - 1][w - 1] = weight;
            graphMatrix[w - 1][v - 1] = weight;
        }
    }
    primFindMst(graphMatrix, vertices);
    return 0;
}