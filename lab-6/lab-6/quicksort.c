#include "quicksort.h"

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int *arr, int left, int right)
{
	int i = left, j = right, privot = arr[(left + right) / 2];

	while (i < j)
	{
		while (arr[i] < privot) i++;
		while (arr[j] > privot) j--;

		if (j > i) swap(&arr[i], &arr[j]);
		i++;
		j--;
	}

	if (i < right) quicksort(arr, i, right);
	if (left < j) quicksort(arr, left, j);
}