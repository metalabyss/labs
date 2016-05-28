#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

//топологическая сортировка графа
//TODO: храни цвета вершин как-нибудь по другому, раз такая тупая

void topologicalSort(GraphVertex* graph, int vertices)
{
    Stack* stack = NULL;
    int cycleFlag;
    for (int i = 0; i < vertices; i++)
    {
        if (cycleFlag = dfs(&graph, i, &stack, vertices))
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

    topologicalSort(graph, vertices);

    return 0;
}