#include<stdio.h>
#include"tree.h"

void main()
{
	int count;
	scanf_s("%d", &count);

	if (count)
	{
		int value;
		TreeNode *root = NULL;

		while (count)
		{
			scanf_s("%d", &value);
			root = buildTree(root, value);
			count--;
		}
		printf("%d", root->height);

		deleteTree(root);
	}
	else
	{
		printf("%d", 0); //empty tree
	}
}