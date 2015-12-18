#include "token.h"

int getNumber(char c);

int getOperatorPriority(char c);

/* Фунция разбивает строку на операторы и операнды:
	string - введенная строка,
	tokensCount - указатель на кол-во токенов.
	Возвращаемое значение - массив (список?) из токенов.
	Если в выражении встретился недопустимый символ - возвращается нулевой указатель. */
token_t *parse(unsigned char *string, int *tokensCount);

/* Функция представляет выражение в обратной польской нотации (reverse polish notation):
	expression - список из токенов
	expressionLength - длина этого списка (выражения)
	Возвращаемое значение - список (выражение) в ОПН.
	Если в выражении ошибка - возвращается нулевой указатель. */
token_t *convertToRPN(token_t *expression, int expressionLength);

token_t *calculate();