#pragma once
#include<stdio.h>
#include<string.h>

#include"token.h"
#include"calculator.h"

void main()
{
	unsigned char expression[1001];
	gets_s(expression, 1001);

	int tokensCount;
	token_t *tokens = parse(expression, tokensCount);
	if (tokens == NULL)
	{
		printf_s("syntax error");
		return;
	}

}