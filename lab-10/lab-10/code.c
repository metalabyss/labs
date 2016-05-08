#include "code.h"

void encodeHuffmanCodes(HuffmanCode* codes, FILE* output)
{
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
        fputc(codes[i].code, output); //сам код
    }
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
        int code = fgetc(input);
        HuffmanCode* hCode = codes + symbol;
        hCode->length = length;
        hCode->code = code;
    }
}
