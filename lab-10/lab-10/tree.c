#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

typedef struct _huffmanTreeNode
{
    int symbol;
    int priority;
    struct _huffmanTreeNode* left;
    struct _huffmanTreeNode* right;
} HuffmanTreeNode;

struct _huffmanTree
{
    HuffmanTreeNode* right;
    HuffmanTreeNode* left;
};

int _nodeComparator(const void* a, const void* b)
{
    HuffmanTreeNode* nodeAPtr = *((HuffmanTreeNode**)a);
    HuffmanTreeNode* nodeBPtr = *((HuffmanTreeNode**)b);
    if (!nodeAPtr && !nodeBPtr)
    {
        return 0;
    }
    else if (!nodeAPtr)
    {
        return 1;
    }
    else if (!nodeBPtr)
    {
        return -1;
    }
    return nodeAPtr->priority - nodeBPtr->priority;
}

//returns size of symbolNodes array
int _symbolNodesSize(HuffmanTreeNode** symbolNodes, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (!symbolNodes[i]) return i;
    }
    return size;
}

void _printSymbolNodes(HuffmanTreeNode** symbolNode, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!symbolNode[i])
        {
            printf("empty element\n");
        }
        else
        {
            printf("Node %d: size %d, priority %d, pointer %p\n", i, symbolNode[i]->symbol, symbolNode[i]->priority, symbolNode[i]);
        }
    }
    printf("\n");
}

void _printHuffmanCodes(HuffmanCode *codes, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d. symbol %d, code %d, length %d\n", i, i, codes[i].code, codes[i].length);
    }
    printf("\n");
}

HuffmanTreeNode* _makeTreeNodeFromCode(HuffmanTreeNode* node, int symbol, int code, int length)
{
    if (!node) {
        node = (HuffmanTreeNode*)calloc(1, sizeof(HuffmanTreeNode));
        node->symbol = -1;
    }
    if (!length) {
        node->symbol = symbol;
        return node;
    }
    if (code & (1 << (length - 1)))
    {
        node->right = _makeTreeNodeFromCode(node->right, symbol, code, length - 1);
    }
    else
    {
        node->left = _makeTreeNodeFromCode(node->left, symbol, code, length - 1);
    }
    return node;
}

HuffmanTree* makeTreeFromCodes(HuffmanCode* codes)
{
    HuffmanTree* tree = (HuffmanTree*)calloc(1, sizeof(HuffmanTree));
    for (int i = 0; i < 256; ++i) {
        if (!codes[i].length) continue;
        if (codes[i].code & (1 << (codes[i].length - 1)))
        {
            tree->right = _makeTreeNodeFromCode(tree->right, i, codes[i].code, codes[i].length - 1);
        }
        else
        {
            tree->left = _makeTreeNodeFromCode(tree->left, i, codes[i].code, codes[i].length - 1);
        }
    }
    return tree;
}

//do not touch - everthing is correct!
HuffmanTree* makeTree(int* symbolTable, int size)
{
    HuffmanTree* tree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    HuffmanTreeNode** symbolNodes = (HuffmanTreeNode**)calloc(size, sizeof(HuffmanTreeNode*)); //array for sorting

    for (int i = 0; i < size; i++)
    {
        if (!symbolTable[i]) continue; //no such symbol in input

        HuffmanTreeNode* newNode = (HuffmanTreeNode*)calloc(1, sizeof(HuffmanTreeNode));
        newNode->symbol = i;
        newNode->priority = symbolTable[i];
        symbolNodes[i] = newNode;
    }

    int symbolNodesSize = 0;
    do
    {
        //_printSymbolNodes(symbolNodes, size);
        qsort(symbolNodes, size, sizeof(HuffmanTreeNode*), _nodeComparator);
        symbolNodesSize = _symbolNodesSize(symbolNodes, size);
        if (symbolNodesSize > 2)
        {
            HuffmanTreeNode* left = symbolNodes[0];
            HuffmanTreeNode* right = symbolNodes[1];
            HuffmanTreeNode* newNode = (HuffmanTreeNode*)calloc(1, sizeof(HuffmanTreeNode));
            newNode->symbol = -1;
            newNode->priority = left->priority + right->priority;
            newNode->left = left;
            newNode->right = right;
            symbolNodes[1] = NULL;
            symbolNodes[0] = newNode;
        }
    } while (symbolNodesSize > 2);
    tree->left = symbolNodes[0];
    tree->right = symbolNodes[1];
    free(symbolNodes);
    return tree;
}


int getSymbolByCode(HuffmanTree* tree, int code, int length)
{
    HuffmanTreeNode* node = NULL;
    if (!length || !tree->left && !tree->right)
    {
        return -1;
    }
    if (code & (1 << (length - 1)))
    {
        node = tree->right;
    }
    else
    {
        node = tree->left;
    }
    --length;
    while (length)
    {
        if (code & (1 << (length - 1)))
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
        --length;
    }
    return node->symbol;
}

void _dfs(HuffmanTreeNode* treeNode, HuffmanCode* codeCollection, int size, int code, int depth)
{
    if (!treeNode) return;

    if (treeNode->symbol == -1)
    {
        _dfs(treeNode->left, codeCollection, size, code << 1, depth + 1);
        _dfs(treeNode->right, codeCollection, size, (code << 1) + 1, depth + 1);
        return;
    }
    HuffmanCode* symbolPtr = codeCollection + treeNode->symbol;
    symbolPtr->code = code;
    symbolPtr->length = depth;
}

void getCodes(HuffmanTree* tree, HuffmanCode* code, int size)
{
    _dfs(tree->left, code, size, 0, 1);
    _dfs(tree->right, code, size, 1, 1);
    //_printHuffmanCodes(code, size);
}

void _destroyNode(HuffmanTreeNode* node)
{
    if (node)
    {
        _destroyNode(node->left);
        _destroyNode(node->right);
        free(node);
    }
}

void destroyTree(HuffmanTree* tree)
{
    _destroyNode(tree->left);
    _destroyNode(tree->right);
    free(tree);
}
