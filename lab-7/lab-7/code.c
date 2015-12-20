#pragma once

#include <stdio.h>
#include <malloc.h>
#include "token.h"
#include "calculator.h"

void main()
{
	unsigned char expression[1001];
	gets_s(expression, 1001);

	int tokensCount;
	token *tokens = parse(expression, &tokensCount);
	if (tokens == NULL)
	{
		printf_s("syntax error");
		return;
	}

	printf_s("%s", calculate(tokens, tokensCount));
	free(tokens);
}