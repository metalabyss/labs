#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<math.h>
#include<locale.h>

int ASCIITableSize = 256;

int* initializeShiftTable(unsigned char *sample, int sampleLength)
{
	int i;
	int *table = malloc(sizeof(int) * ASCIITableSize);

	for (i = 0; i < ASCIITableSize; i++)
		table[i] = sampleLength;

	for (i = sampleLength - 1 - 1; i != -1; i--) /*игнорируем последний символ сэмпла, если он встретился единожды!*/
	{
		if (table[sample[i]] == sampleLength)
			table[sample[i]] = (sampleLength - 1) - i;
	}

	return table;
}

int readAdditionalSybmols(unsigned char *string, int sybmolPosition, int sampleLength, int count)
{
	char buff[17];
	int size = fread(&buff, sizeof(unsigned char), count, stdin);
	if (size < count) return 0;

	for (int i = 0; i < size; i++)
	{
		string[(sybmolPosition + i) % sampleLength] = buff[i];
	}
	
	return 1;
}

void substringSearch(unsigned char *sample, unsigned char *string)
{
	int sampleLength = strlen(sample);

	int *shiftTable = initializeShiftTable(sample, sampleLength);

	for (int i = 0; ;)
	{
		int j = 0; // смещение по образцу
		for (j = sampleLength - 1; j >= 0; --j)
		{
			printf("%d ", i + j + 1);
			if (string[(i + j) % sampleLength] != sample[j]) break;
		}

		int count = shiftTable[string[(i + sampleLength - 1) % sampleLength]];

		if (!readAdditionalSybmols(string, i, sampleLength, count)) break;
		i += count;
	}
}

void main()
{
	setlocale(LC_ALL, "ru-RU.UTF-8");
	unsigned char sample[17];
	gets_s(sample, 17);

	unsigned char string[17];
	int size = fread(string, sizeof(unsigned char), strlen(sample), stdin);
	string[size] = '\0';
	if (size < strlen(sample)) return;

	substringSearch(sample, string);
}