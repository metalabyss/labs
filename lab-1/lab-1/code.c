/*Лабораторная работа №1

Перевести число X из системы счисления с основанием b1 в систему с основанием b2.

Дано:
строка 1:
целые числа b1 и b2 от 2 до 16 -- основание исходной и конечной системы счисления, разделенные пробелом

строка 2:
от 1 до 12 b1-ричных цифр, возможно разделенных точкой на целую и дробную часть.
Это b1-ричная запись числа X. Всего должно быть не более 13 символов.

Вывод программы:
	Если b1 и b2 в первой строке не от 2 до 16, то "bad input".
	Если в второй строке не b1-ричная запись, то "bad input".
	Иначе -- запись всей целой части X в b2-ричной системе счисления.
	и если X содержит дробную часть, то точка и первые 12 b2-ричных цифр дробной части.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define maxInputLength 30
#define epsilon 0.0000000000001

//Символ -> число
int getNumberByChar(char c)
{
	if (c >= '0' && c <= '9') return (int)(c - '0');
	if (c >= 'A' && c <= 'F') return (int)(c - 'A') + 10;
	if (c >= 'a' && c <= 'f') return (int)(c - 'a') + 10;
	return -1;
}

//Число -> символ
char getCharByNumber(int number)
{
	if (number >= 0 && number < 10) return '0' + (char)number;
	if (number >= 10 && number < 16) return 'A' + (char)(number - 10);
	return 0;
}


/*Проверка введенного числа на корректность:
	number - введенное число,
	b1 - основание исходной системы счисления.
	Если нет ошибок - возвращаем 1. */

int isNumberCorrect(char number[], int b1, int *pointPosition)
{
	int currentNumber;
	for (int i = 0; number[i] != '\0'; i++)
	{
		if (number[i] == '.')
		{
			if (*pointPosition != -1) return 0; //вдруг вторая точка?
			*pointPosition = i;
		}
		else
		{
			currentNumber = getNumberByChar(number[i]);
			if (currentNumber >= b1 || currentNumber < 0) return 0;
		}
	}

	//если не нашлась точка
	if (*pointPosition == -1) *pointPosition = strlen(number);
	//если точка в самом начале/конце строки, то ввод некорректен
	if (*pointPosition == strlen(number) - 1 || *pointPosition == 0) return 0;

	//всё хорошо.
	return 1;
}

void prependChar(char **string, char c)
{
	int length = strlen(*string);
	char *newString = malloc(length + 1 + 1); // одна из единичек для доп. символа, другая - для символа конца строки
	strcpy_s(newString + 1, length + 1, *string); // копируем старую строку в новую со сдвигом вправо на 1 символ
	newString[0] = c; // в начало - очередной символ
	newString[length + 1] = '\0'; // в конец - символ конца строки

	free(*string);
	*string = newString;
}

void appendChar(char **string, char c)
{
	int length = strlen(*string);
	char *newString = malloc(length + 1 + 1);
	strcpy_s(newString, length + 1, *string);
	newString[length] = c;
	newString[length + 1] = '\0';

	free(*string);
	*string = newString;
}

/*Перевод введенного числа в десятичную СС:
	number - указатель на введенное число
	b1 - старое основание
	pointPosition - положение точки в строке
	возвращаемое значение - указатель на полученное число в десятичной СС. */

double *anyToDec(char *number, int b1, int *pointPosition)
{
	//переводим целую часть числа в десятичную СС
	double *resultPointer = malloc(sizeof(double)); //выделяем память под результат
	*resultPointer = 0;
	double currentPower = 1;
	for (int i = *pointPosition - 1; i >= 0; i--)
	{
		*resultPointer += currentPower * getNumberByChar(number[i]);
		currentPower *= b1;
	}

	//теперь - дробную
	currentPower = 1.0 / /*(double)*/b1;
	if (*pointPosition != strlen(number))
	{
		for (int i = *pointPosition + 1; number[i] != '\0'; i++)
		{
			*resultPointer += currentPower * getNumberByChar(number[i]);
			currentPower /= b1;
		}
	}

	return resultPointer;
}

/*Перевод десятичного числа в нужную СС:
	decNumber - число в десятичной СС,
	b2 - основание результирующей СС.
	Возвращаемое значение - указатель на полученное число в b2-ичной СС.*/

char *decToAny(double decNumber, int b2)
{
	char *result = malloc(sizeof(char));
	result[0] = '\0';

	//переводим целую часть числа в нужную СС и конвертируем в строку
	long long integerPart = (long long)decNumber; //используем long long, т.к. в 18 тесте число, не помещающееся в int
	long long currentPower = (long long)b2;
	double fractionalPart = fmod(decNumber, 1);

	//исключение для 0
	if (integerPart == 0 && fractionalPart == 0)
	{
		appendChar(&result, '0');
		return result;
	}

	while (integerPart > 0)
	{
		prependChar(&result, getCharByNumber((int)(integerPart % currentPower)));
		integerPart /= b2;
	}

	//на очереди - дробная
	if (fractionalPart > epsilon)
	{
		if (strlen(result) == 0) // на случай, если целой части нет
			appendChar(&result, '0');
		appendChar(&result, '.');
	}

	while (fractionalPart > epsilon)
	{
		fractionalPart *= b2;
		appendChar(&result, getCharByNumber((int)fractionalPart));
		fractionalPart -= (int)fractionalPart;
	}

	return result;
}

void main()
{
	char number[maxInputLength]; //число, с которым творим магию
	int b1, b2; //основания систем счисления (radix)
	int *pointPosition = malloc(sizeof(int));
	*pointPosition = -1;

	scanf_s("%d %d\n", &b1, &b2);
	gets_s(number, maxInputLength);

	if (isNumberCorrect(number, b1, pointPosition) && b1 >= 2 && b1 <= 16 && b2 >=2 && b2 <=16)
	{
		//творим магию
		double *decNumber = anyToDec(number, b1, pointPosition);
		char *result = decToAny(*decNumber, b2);
		printf("%s\n", result);
	}
	else
	{
		printf("%s\n", "bad input");
	}

	system("pause");
}