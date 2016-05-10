#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "code.h"

void compress(FILE* input, FILE* output)
{
    HuffmanCode* codes = (HuffmanCode*)calloc(256, sizeof(HuffmanCode));
    int ch = EOF;
    int* table = (int*)calloc(256, sizeof(int));

    FILE *tempFile = fopen("tmp2.txt", "wb");
    FILE *inputsize = fopen("insize.txt", "wb");
    int insize = 0;
    while (EOF != (ch = fgetc(input)))
    {
        table[ch] += 1;
        insize++;
        fputc(ch, tempFile);
    }
    fputc(insize, inputsize);
    fclose(tempFile);

    HuffmanTree* tree = makeTree(table, 256);
    getCodes(tree, codes, 256);
    free(table);
    destroyTree(tree);

    tempFile = fopen("tmp2.txt", "rb");
    encodeHuffmanCodes(codes, output);
    int chSize = 0; //размер chToWrite в битах
    int chToWrite = 0; //символ, который будет записан, когда он будет готов
    while (EOF != (ch = fgetc(tempFile)))
    {
        HuffmanCode* chCode = codes + ch; //смещаемся по массиву на код ch
        int newChSize = chSize + chCode->length; //вычисляем новый размер символа для записи
        int offset = 0;

        if (newChSize > 8) offset = newChSize % 8;

        chSize += chCode->length - offset;
        chToWrite <<= chCode->length - offset;
        chToWrite |= chCode->code >> offset;

        if (chSize == 8) //если символ готов, записываем его
        {
            fputc(chToWrite, output);
            chSize = offset;

            //запись оставшегося кусочка
            int offsetPart = 0;
            for (int i = 0; i < offset; ++i) {
                offsetPart <<= 1;
                offsetPart |= 1;
            }
            chToWrite = chCode->code & offsetPart;
        }
    }
    if (chSize)
    {
        fputc(chToWrite, output);
        fputc(chSize, output);
    }
    else
    {
        fputc(8, output);
    }
    fclose(tempFile);
    free(codes);
}

void decompress(FILE* input, FILE* output)
{
    HuffmanCode* codes = (HuffmanCode*)calloc(256, sizeof(HuffmanCode));
    decodeHuffmanCodes(codes, input);
    HuffmanTree* tree = makeTreeFromCodes(codes);
    int ch1 = fgetc(input); //текущий байт
    int ch2 = fgetc(input); //кол-во значащих бит в ch1, если ch2 - последний
    int ch3 = fgetc(input); //на случай, если ch2 - последний
    int preparedCode = 0; //восстанавливаемый код символа
    int preparedCodeSize = 0; //его размер

    int visitedBit;
    if (ch3 == EOF)
    {
        visitedBit = ch2 - 1;
    }
    else
    {
        visitedBit = 7;
    }

    while (1)
    {
        if (visitedBit < 0)
        {
            if (ch3 == EOF)
            {
                break;
            }
            ch1 = ch2;
            ch2 = ch3;
            ch3 = fgetc(input);
            visitedBit = 7;
            if (ch3 == EOF) //в этом случае только ch2 бита являются значимыми
            {
                visitedBit = ch2 - 1;
            }
        }
        preparedCode <<= 1;
        preparedCode |= (ch1 >> (visitedBit--)) & 1;
        ++preparedCodeSize;
        int symbol = getSymbolByCode(tree, preparedCode, preparedCodeSize);
        if (-1 != symbol) // является ли preparedCode кодом символа
        {
            fputc(symbol, output);
            preparedCode = 0;
            preparedCodeSize = 0;
        } 
    }
    destroyTree(tree);
    free(codes);
}

int main()
{
    //char mode_string[10] = { 0 };
    char mode = 'c';
    FILE* input = fopen("tmp.txt", "rb");
    FILE* output = fopen("out.txt", "wb");

    if (!input) printf("input file doesn't exist");

    //fgets(mode_string, 10, input);
    
    if (mode == 'c')
    {
        compress(input, output);
    }
    else if (mode == 'd')
    {
        decompress(input, output);
    }
    else
    {
        printf("wrong option");
    }

    fclose(input);
    fclose(output);
    return 0;
}