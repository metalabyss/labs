#include <memory.h>
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

token_t *parse(unsigned char *string, int *tokensCount)
{
	token_t *result = malloc(sizeof(token_t) * strlen(string));
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

token_t *convertToRPN(token_t *expression, int expressionLength)
{
	token_t *result = malloc(sizeof(token_t)* expressionLength);
	int resultLength = 0;

	token_t *stack = malloc(sizeof(token_t)* expressionLength);
	int stackEnd = -1; //стек пуст!

	int i;
	for (i = 0; i < expressionLength; i++)
	{
		//если встретилось число - кладём в массив
		if (expression[i].type == NUMBER) { 
			result[resultLength++] = expression[i];
		}
		//если встретилась откр. скобка - помещаем её в стек.
		else if (expression[i].type == OPERATOR && expression[i].symbol == '(')
		{
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

	while (stackEnd >= 0)
	{
		if (stack[stackEnd].type == OPERATOR && stack[stackEnd].symbol == '(') return NULL; //неправильно расставлены скобки!
		result[resultLength++] = stack[stackEnd--];
	}

	free(stack);
	return result;
}

char *calculate(token_t *expression, int expressionLength)
{
	token_t *rpn = convertToRPN(expression, expressionLength);
	if (rpn == NULL) return "syntax error";


	
}