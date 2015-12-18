#include <memory.h>
#include "calculator.h"

#define OPERATOR (1)
#define NUMBER (0)

int getNumber(char c)
{
	if (c >= '0' && c <= '9') return (int)(c - '0');
	else return -1;
}

int getOperatorPriority(char c)
{
	switch (c)
	{
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	case '(':
	case ')':
		return 1;
	default:
		return -1;
	}
}

token_t *parse(unsigned char *string, int *tokensCount)
{
	token_t *result = malloc(sizeof(token_t) * strlen(string));
	*tokensCount = 0;

	for (int i = 0; i < strlen(string); i++)
	{
		if (getNumber(string[i]) == -1)
		{
			if (getOperatorPriority(string[i]) == -1) return NULL; // недопустимый оператор

			result[*tokensCount].type = OPERATOR;
			result[*tokensCount].symbol = string[i];
		}
		else
		{
			int tmp = getNumber(string[i]);

			//пока не конец строки или встретился не операнд
			while (i + 1 < strlen(string) && getNumber(string[i + 1]) != -1)
			{
				i++;
				tmp *= 10;
				tmp += getNumber(string[i]);
			}
			result[*tokensCount].type = NUMBER;
			result[*tokensCount].number = tmp;
		}
		(*tokensCount)++;
	}

	return result;
}