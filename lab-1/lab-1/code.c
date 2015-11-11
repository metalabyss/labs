/*������������ ������ �1

��������� ����� X �� ������� ��������� � ���������� b1 � ������� � ���������� b2.

����:
������ 1:
����� ����� b1 � b2 �� 2 �� 16 -- ��������� �������� � �������� ������� ���������, ����������� ��������

������ 2:
�� 1 �� 12 b1-������ ����, �������� ����������� ������ �� ����� � ������� �����.
��� b1-������ ������ ����� X. ����� ������ ���� �� ����� 13 ��������.

����� ���������:
	���� b1 � b2 � ������ ������ �� �� 2 �� 16, �� "bad input".
	���� � ������ ������ �� b1-������ ������, �� "bad input".
	����� -- ������ ���� ����� ����� X � b2-������ ������� ���������.
	� ���� X �������� ������� �����, �� ����� � ������ 12 b2-������ ���� ������� �����.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define maxInputLength 30
#define epsilon 0.0000000000001

//������ -> �����
int getNumberByChar(char c)
{
	if (c >= '0' && c <= '9') return (int)(c - '0');
	if (c >= 'A' && c <= 'F') return (int)(c - 'A') + 10;
	if (c >= 'a' && c <= 'f') return (int)(c - 'a') + 10;
	return -1;
}

//����� -> ������
char getCharByNumber(int number)
{
	if (number >= 0 && number < 10) return '0' + (char)number;
	if (number >= 10 && number < 16) return 'A' + (char)(number - 10);
	return 0;
}


/*�������� ���������� ����� �� ������������:
	number - ��������� �����,
	b1 - ��������� �������� ������� ���������.
	���� ��� ������ - ���������� 1. */

int isNumberCorrect(char number[], int b1, int *pointPosition)
{
	int currentNumber;
	for (int i = 0; number[i] != '\0'; i++)
	{
		if (number[i] == '.')
		{
			if (*pointPosition != -1) return 0; //����� ������ �����?
			*pointPosition = i;
		}
		else
		{
			currentNumber = getNumberByChar(number[i]);
			if (currentNumber >= b1 || currentNumber < 0) return 0;
		}
	}

	//���� �� ������� �����
	if (*pointPosition == -1) *pointPosition = strlen(number);
	//���� ����� � ����� ������/����� ������, �� ���� �����������
	if (*pointPosition == strlen(number) - 1 || *pointPosition == 0) return 0;

	//�� ������.
	return 1;
}

void prependChar(char **string, char c)
{
	int length = strlen(*string);
	char *newString = malloc(length + 1 + 1); // ���� �� �������� ��� ���. �������, ������ - ��� ������� ����� ������
	strcpy_s(newString + 1, length + 1, *string); // �������� ������ ������ � ����� �� ������� ������ �� 1 ������
	newString[0] = c; // � ������ - ��������� ������
	newString[length + 1] = '\0'; // � ����� - ������ ����� ������

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

/*������� ���������� ����� � ���������� ��:
	number - ��������� �� ��������� �����
	b1 - ������ ���������
	pointPosition - ��������� ����� � ������
	������������ �������� - ��������� �� ���������� ����� � ���������� ��. */

double *anyToDec(char *number, int b1, int *pointPosition)
{
	//��������� ����� ����� ����� � ���������� ��
	double *resultPointer = malloc(sizeof(double)); //�������� ������ ��� ���������
	*resultPointer = 0;
	double currentPower = 1;
	for (int i = *pointPosition - 1; i >= 0; i--)
	{
		*resultPointer += currentPower * getNumberByChar(number[i]);
		currentPower *= b1;
	}

	//������ - �������
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

/*������� ����������� ����� � ������ ��:
	decNumber - ����� � ���������� ��,
	b2 - ��������� �������������� ��.
	������������ �������� - ��������� �� ���������� ����� � b2-����� ��.*/

char *decToAny(double decNumber, int b2)
{
	char *result = malloc(sizeof(char));
	result[0] = '\0';

	//��������� ����� ����� ����� � ������ �� � ������������ � ������
	long long integerPart = (long long)decNumber; //���������� long long, �.�. � 18 ����� �����, �� ������������ � int
	long long currentPower = (long long)b2;
	double fractionalPart = fmod(decNumber, 1);

	//���������� ��� 0
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

	//�� ������� - �������
	if (fractionalPart > epsilon)
	{
		if (strlen(result) == 0) // �� ������, ���� ����� ����� ���
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
	char number[maxInputLength]; //�����, � ������� ������ �����
	int b1, b2; //��������� ������ ��������� (radix)
	int *pointPosition = malloc(sizeof(int));
	*pointPosition = -1;

	scanf_s("%d %d\n", &b1, &b2);
	gets_s(number, maxInputLength);

	if (isNumberCorrect(number, b1, pointPosition) && b1 >= 2 && b1 <= 16 && b2 >=2 && b2 <=16)
	{
		//������ �����
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