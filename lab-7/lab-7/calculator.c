//#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "calculator.h"

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

double calculateOperator(char op, double a, double b)
{
	switch (op)
	{
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '+':
		return a + b;
	case '-':
		return a - b;
	default:
		return 0;
	}
}

token *parse(unsigned char *string, int *tokensCount)
{
	token *result = malloc(sizeof(token) * strlen(string));
	*tokensCount = 0;

	int i;
	for (i = 0; i < strlen(string); i++)
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

token *convertToRPN(token *expression, int *expressionLength)
{
	token *result = malloc(sizeof(token) * (*expressionLength));
	int resultLength = 0;

	token *stack = malloc(sizeof(token) * (*expressionLength));
	int stackEnd = -1; //стек пуст!

	int i;
	for (i = 0; i < (*expressionLength); i++)
	{
		//если встретилось число - кладём в массив
		if (expression[i].type == NUMBER) { 
			result[resultLength++] = expression[i];
		}
		//если встретилась откр. скобка - помещаем её в стек.
		else if (expression[i].type == OPERATOR && expression[i].symbol == '(')
		{
			if (i < (*expressionLength) - 1 && expression[i + 1].type == OPERATOR && expression[i + 1].symbol == ')') return NULL;
			stack[++stackEnd] = expression[i];
		}
		else if (expression[i].type == OPERATOR && expression[i].symbol == ')')
		{
			while (stackEnd >= 0)
			{
				//если наткнулись на откр. скобку - выходим из цикла
				if (stack[stackEnd].type == OPERATOR && stack[stackEnd].symbol == '(') break;
				result[resultLength++] = stack[stackEnd--];
			}

			//если так и не встретили закр. скобку - в выражении ошибка
			if (stackEnd == -1) return NULL;

			//удаляем открывающую скобку
			stackEnd--;
		}
		else
		{
			//смотрим приоритеты операторов. Если стек непуст, и у текущего оператора приоритет меньше, то...
			int currOperatorPriority = getOperatorPriority(expression[i].symbol);
			while (stackEnd >= 0 && currOperatorPriority <= getOperatorPriority(stack[stackEnd].symbol))
			{
				result[resultLength] = stack[stackEnd]; //помещаем его в конец выходной строки
				resultLength++;
				stackEnd--;
			}

			stack[++stackEnd] = expression[i];
		}
	}

	//освобождаем стек
	while (stackEnd >= 0)
	{
		if (stack[stackEnd].type == OPERATOR && stack[stackEnd].symbol == '(') return NULL; //неправильно расставлены скобки!
		result[resultLength++] = stack[stackEnd--];
	}

	*expressionLength = resultLength;
	free(stack);
	return result;
}

char *calculate(token *expression, int expressionLength)
{
	token *rpnExp = convertToRPN(expression, &expressionLength);
	if (rpnExp == NULL) return "syntax error";

	double *stack = malloc(sizeof(double) * expressionLength);
	int stackEnd = -1;

	int i;
	for (i = 0; i < expressionLength; i++)
	{
		if (rpnExp[i].type == NUMBER)
		{
			stack[++stackEnd] = rpnExp[i].number;
		}
		else
		{
			if (rpnExp[i].symbol == '/' && stack[stackEnd] == 0) return "division by zero";

			double result = calculateOperator(rpnExp[i].symbol, stack[stackEnd - 1], stack[stackEnd]);
			stack[--stackEnd] = result;
		}
	}
	
	if (stackEnd != 0) //если после вычислений в стеке > 1 элемента
	{
		free(stack);
		return "syntax error";
	}
	else
	{
		char *result = malloc(sizeof(char) * 32);
		sprintf_s(result, 32, "%lf", stack[0]);
		free(stack);
		return result;
	}
}