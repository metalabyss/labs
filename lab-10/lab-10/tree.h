#ifndef H_TREE

#define H_TREE

#include "code.h"

typedef struct _huffmanTree HuffmanTree;

HuffmanTree* makeTreeFromCodes(HuffmanCode*);
HuffmanTree* makeTree(int*, int);
void getCodes(HuffmanTree*, HuffmanCode*, int);
void destroyTree(HuffmanTree*);
int getSymbolByCode(HuffmanTree*, int, int);

#endif