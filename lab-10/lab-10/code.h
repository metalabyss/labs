#ifndef H_CODE

#define H_CODE

#include <stdio.h>

typedef struct _code
{
    long long code;
    int length;
} HuffmanCode;

//Функция кодирования таблицы
void encodeHuffmanCodes(HuffmanCode*, FILE*);

//Функция декодирования таблицы
void decodeHuffmanCodes(HuffmanCode*, FILE*);

#endif