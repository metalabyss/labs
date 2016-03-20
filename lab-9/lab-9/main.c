#include<stdio.h>
#include"tree.h"

//АВЛ-дерево
//TODO: debug

void main()
{
	int countOfNodes;
	scanf_s("%d", &countOfNodes);

	if (countOfNodes)
	{
		int value;
		TreeNode *root = NULL;
		for (int i = 1; i < countOfNodes; i++)
		{
			scanf_s("%d ", &value);
			root = buildTree(root, value);
		}
		printf("%d", root->height);
	}
	else
	{
		printf("%d", 0); //empty tree
	}
}