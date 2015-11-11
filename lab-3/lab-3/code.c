#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<math.h> 

#define bufferSize 4096

int powersOf3[17];
unsigned char cache[bufferSize];
int cachePosition = bufferSize;
int cacheSize = 0;

int cachedFread(unsigned char *str)
{
	if (cachePosition >= bufferSize || cachePosition >= cacheSize)
	{
		cachePosition = 0;
		cacheSize = fread(cache, sizeof(unsigned char), bufferSize, stdin);
	}

	if (cacheSize == 0)
	{
		return 0;
	}

	*str = cache[cachePosition];
	cachePosition++;
	return 1;
}

int hash(unsigned char *str, int length)
{
	int hash = 0;
	for (int i = 0; i < length; i++)
		hash += (str[i] % 3) * powersOf3[i];
	return hash;
}

int hashUpdate(int hash, unsigned char out, unsigned char in, int sampleLength)
{
	hash -= (out % 3);
	hash /= 3;
	hash += (in % 3) * powersOf3[sampleLength - 1];
	return hash;
}

int readAdditionalSybmol(unsigned char *string, int sybmolPosition, int sampleLength)
{
	int c = cachedFread(&string[sybmolPosition % sampleLength]);
	return c;
}

void substringSearch(unsigned char *sample, unsigned char *string)
{
	int sampleLength = strlen(sample);
	int sampleHash = hash(sample, sampleLength);
	printf("%d ", sampleHash);
	int currentHash = hash(string, sampleLength);

	if (sampleLength > strlen(string)) return;

	for (int i = 0;; i++)
	{
		if (sampleHash == currentHash)
		{
			for (int j = 0; j < sampleLength; j++)
			{
				printf("%d ", i + j + 1);
				if (sample[j] != string[(i + j) % sampleLength]) break;
			}
		}

		unsigned char out = string[i % sampleLength];

		int isNotLastSybmol = readAdditionalSybmol(string, i, sampleLength);

		currentHash = hashUpdate(currentHash, out, string[i % sampleLength], sampleLength);

		if (!isNotLastSybmol) break;
	}
}

void main()
{
	for (int i = 0; i < 17; i++)
		powersOf3[i] = pow(3, i);
	
	unsigned char sample[17];
	gets_s(sample, 17);

	unsigned char string[17];
	int size = fread(string, sizeof(unsigned char), strlen(sample), stdin);
	string[size] = '\0';

	substringSearch(sample, string);
}