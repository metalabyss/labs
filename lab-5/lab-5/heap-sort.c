#include "heap-sort.h"

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


// "Родитель" -> "левый" потомок

int getLeft(int i)
{
	return 2 * i + 1;
}


// "Родитель" -> "правый" потомок

int getRight(int i)
{
	return 2 * i + 2;
}


/* Хипификация пирамиды (поддержка свойства невозраст. пирамиды:
	arr - неупорядоченный массив,
	size - текущий размер массива,
	i - индекс элемента, начиная с которого производим "хипификацию". */

void maxHeapify(int arr[], int size, int i)
{
	int left = getLeft(i);
	int right = getRight(i);

	int max;

	if ((left < size) && (arr[left] > arr[i]))
		max = left;
	else
		max = i;

	if ((right < size) && (arr[right] >= arr[max]))
		max = right;

	if (max != i)
	{
		swap(&arr[i], &arr[max]);
		maxHeapify(arr, size, max);
	}
}


/* Посторение невозрастающей пирамиды:
	arr - массив,
	arrSize - размер массива. */

void buildMaxHeap(int arr[], int arrSize)
{
	for (int i = arrSize / 2 - 1; i >= 0; i--) //рассматриваем эл-ты на уровне, имеющие хотя бы одного "потомка"
		maxHeapify(arr, arrSize, i);
}


/* Процедура пирамидальной сортировки:
	arr - массив,
	arrSize - размер массива. */

void heapsort(int arr[], int arrSize)
{
	buildMaxHeap(arr, arrSize);

	for (int i = arrSize - 1; i >= 1; i--)
	{
		swap(&arr[0], &arr[i]);
		maxHeapify(arr, i, 0);
	}
}