#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

//топологическая сортировка графа

void topologicalSort(GraphVertex* graph, int* colors, int vertices)
{
    Stack* stack = NULL;

    int cycleFlag;
    int i;
    for (i = 1; i <= vertices; i++)
    {
        cycleFlag = dfs(graph, &colors, i, &stack, vertices);
        if (cycleFlag == 1)
        {
            printf("impossible to sort");
            return;
        }
    }

    int number;
    while (stack)
    {
        number = pop(&stack);
        printf("%d ", number);
    }
}

int main()
{
    //инициализация
    int vertices, edges;
    scanf("%d\n", &vertices);
    scanf("%d\n", &edges);
    GraphVertex* graph = NULL;

    if (vertices < 0 || vertices > 1000)
    {
        printf("bad number of vertices");
        return;
    }

    if (edges < 0 || edges > vertices*(vertices - 1) / 2)
    {
        printf("bad number of edges");
        return;
    }

    int i;
    int v, w; //2 вершинки
    int* colors = (int*)malloc(vertices*sizeof(int));
    for (i = 0; i < vertices; i++)
        colors[i] = WHITE;

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
            insert(&graph, &colors, v, w, vertices);
        }
    }

    topologicalSort(graph, colors, vertices);

    return 0;
}