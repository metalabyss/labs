#include "code.h"

typedef union _code_bytes {
    long long int number;
    char bytes[8];
} CodeBytes;

void encodeHuffmanCodes(HuffmanCode* codes, FILE* output)
{
    FILE* encodedCodes = fopen("enCodes.txt", "w");
    int count = 0;
    int i = 0;
    for (i = 0; i < 256; ++i)
    {
        if (codes[i].length) ++count;
    }
    fputc(count, output);
    for (i = 0; i < 256; ++i)
    {
        if (!codes[i].length) continue;
        fputc(i, output); //символ
        fputc(codes[i].length, output); //количество значащих бит в его коде
        CodeBytes cb;
        cb.number = codes[i].code;
        int printCount = codes[i].length / 8 + (codes[i].length % 8 ? 1 : 0);
        for (int i = 0; i < printCount; ++i) {
            fputc(cb.bytes[i], output);
        }
        //fprintf(encodedCodes, "Символ: %d, код: %d\n", i, codes[i].code);
    }
    fclose(encodedCodes);
}

void decodeHuffmanCodes(HuffmanCode* codes, FILE* input)
{
    int count = 0;
    int i = 0;
    count = fgetc(input);
    for (i = 0; i < count; ++i)
    {
        int symbol = fgetc(input);
        int length = fgetc(input);
        CodeBytes cb;
        int readCount = length / 8 + (length % 8 ? 1 : 0);
        for (int i = 0; i < readCount; ++i) {
            cb.bytes[i] = fgetc(input);
        }
        HuffmanCode* hCode = codes + symbol;
        hCode->length = length;
        hCode->code = cb.number;
    }
}
