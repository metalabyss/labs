#include<stdio.h>
#include<math.h>
#include<string.h>

int nextPermutation(unsigned char *string, int length)
{
	int k = length - 2;

	while (string[k] >= string[k + 1]) k--; //находим ближайший к концу строки эл-т, который меньше следующего

	if (k < 0) return 0; //если таковой не нашёлся, значит это последняя перестановка

	int l = length - 1;
	while (string[k] >= string[l]) l--; //находим наибольший эл-т, который находится правее k

	if (k >= l) return 0;

	char tmp = string[k]; 
	string[k] = string[l];
	string[l] = tmp;

	for (int i = k + 1; i <= (k + length) / 2; i++) //разворачиваем то, что справа от k
	{
		tmp = string[i];
		string[i] = string[length - i + k];
		string[length - i + k] = tmp;
	}

	return 1;
}

void main()
{
	unsigned char string[11];
	int countOfPermutations;

	gets_s(string, 11);
	scanf_s("%d", &countOfPermutations);

	int length = strlen(string);

	for (size_t i = 0; i < length; i++)
	{
		if (string[i] > '9' || string[i] < '0')
		{
			printf("bad input");
			return;
		}

		for (size_t j = 0; j < i; j++)
		{
			if (string[i] == string[j])
			{
				printf("bad input");
				return;
			}
		}
	}

	for (size_t i = 0; i < countOfPermutations; i++)
	{
		if (!nextPermutation(string, length)) break;
		printf("%s\n", string);
	}
}