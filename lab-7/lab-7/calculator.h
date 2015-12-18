#include "token.h"

#define OPERATOR (1)
#define NUMBER (0)

int getNumber(char c);

int getOperatorPriority(char c);

/* Фунция разбивает строку на операторы и операнды:
	string - введенная строка,
	tokensCount - указатель на кол-во токенов.
	Возвращаемое значение - массив из токенов.
	Если в выражении встретился недопустимый символ - возвращается нулевой указатель. */
token_t *parse(unsigned char *string, int *tokensCount);

/* Функция представляет выражение в обратной польской нотации (reverse polish notation):
	expression - массив из токенов
	expressionLength - длина этого массива (выражения)
	Возвращаемое значение - выражение в ОПН (массив).
	Если в выражении ошибка - возвращается нулевой указатель. */
token_t *convertToRPN(token_t *expression, int expressionLength);

/* Функция вычисляет выражение, записанное в ОПН.
	expression - массив из токенов,
	expressionLength - длина выражения,
	Возвращаемое значение - строка с результатом вычисления, либо "syntax error/division by zero" в случае ошибки. */
char *calculate(token_t *expression, int expressionLength);