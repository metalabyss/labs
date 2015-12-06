#include "quicksort.h"

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int *arr, int left, int right)
{
	int i = left, j = right;
	int pivot = arr[(left + right) / 2]; //в качестве опорного элемента берем средний

	while (i < j)
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j)
		{
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}

	if (i < right) quicksort(arr, i, right);
	if (left < j) quicksort(arr, left, j);
}
