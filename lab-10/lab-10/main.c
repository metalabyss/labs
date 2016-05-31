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

    FILE *tempFile = fopen("tmp.txt", "wb");
    //FILE *inputsize = fopen("insize.txt", "wb");
    //FILE *tablelog = fopen("table.txt", "wb");
    int insize = 0;
    while (EOF != (ch = fgetc(input)))
    {
        table[ch] += 1;
        insize++;
        fputc(ch, tempFile);
    }
    fclose(tempFile);

    HuffmanTree* tree = makeTree(table, 256);
    getCodes(tree, codes, 256);
    free(table);

    tempFile = fopen("tmp.txt", "rb");
    encodeTree(tree, output);

    int chToWrite = 0; //символ, который будет записан, когда он будет готов
    int chSize = 0; //размер chToWrite в битах
    while (EOF != (ch = fgetc(tempFile)))
    {
        HuffmanCode* chCode = codes + ch; //смещаемся по массиву на код ch
        int newChSize = chSize + chCode->length; //вычисляем новый размер символа для записи
        int offset = 0;
        int skipBytes = 0;

        if (newChSize > 8) {
            offset = newChSize % 8;
            skipBytes = newChSize / 8;
        }

        chSize += chCode->length - offset - (skipBytes ? skipBytes - 1 : 0) * 8;
        chToWrite <<= chCode->length - offset - (skipBytes ? skipBytes - 1 : 0) * 8;
        chToWrite |= chCode->code >> (offset + (skipBytes ? skipBytes - 1 : 0) * 8);

        if (chSize == 8) //если символ готов, записываем его
        {
            fputc(chToWrite, output);
            if (skipBytes) {
                for (int i = 0; i < skipBytes - 1; ++i) {
                    int code = (int)(chCode->code >> (i * 8 + offset));
                    fputc(code, output);
                }
            }
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
    destroyTree(tree);
    free(codes);
}

void decompress(FILE* input, FILE* output)
{
    HuffmanTree* tree = decodeTree(input);
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
}

int main()
{
    char mode_string[10] = { 0 };
    FILE* input = fopen("in.txt", "rb");
    FILE* output = fopen("out.txt", "wb");

    if (!input) printf("input file doesn't exist");

    fgets(mode_string, 10, input);
    
    if (mode_string[0] == 'c')
    {
        compress(input, output);
    }
    else if (mode_string[0] == 'd')
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