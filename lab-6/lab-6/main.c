#include <stdio.h>
#include <malloc.h>
#include "quicksort.h"

void main()
{
	int arrSize;
	scanf_s("%d", &arrSize);

	int *arr = malloc(sizeof(int)*arrSize);
	for (int i = 0; i < arrSize; i++)
		scanf_s("%d", &arr[i]);

	quicksort(arr, 0, arrSize - 1);

	for (int i = 0; i < arrSize; i++)
	{
		printf_s("%d ", arr[i]);
	}

	free(arr);
}