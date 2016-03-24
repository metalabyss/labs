#include "tree.h"
#include <malloc.h>
#include <stdio.h>

TreeNode *buildTree(TreeNode *root, int value)
{
	if (!root)
	{
		root = malloc(sizeof(TreeNode));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
		root->height = 1;

		return root;
	}
	else if (value < root->value)
	{
		root->left = buildTree(root->left, value);
		return rebalance(root);
	}
	else
	{
		root->right = buildTree(root->right, value);
		return rebalance(root);
	}
}

TreeNode *rebalance(TreeNode *node)
{
	updateTreeHeight(node);

	int balance = getBalance(node);
	int subBalance;
	if (balance == 2) //если правое поддерево выше
	{
		subBalance = getBalance(node->right);
		if (subBalance < 0) //и если его левое поддерево выше
		{
			//то сначала дополнительно делаем малое правое вращение (в сумме это б.л. вращение)
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}
	else if (balance == -2) //если левое поддерево выше
	{
		subBalance = getBalance(node->left);
		if (subBalance > 0)
		{
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}
	else
	{
		return node;
	}
}

int getHeight(TreeNode *node)
{
	if (node)
		return node->height;
	else
		return 0;
}

void updateTreeHeight(TreeNode *node)
{
	int left = getHeight(node->left);
	int right = getHeight(node->right);

	if (left > right)
		node->height = left + 1;
	else
		node->height = right + 1;
}

int getBalance(TreeNode *node)
{
	return getHeight(node->right) - getHeight(node->left);
}

TreeNode *rotateRight(TreeNode *a)
{
	TreeNode *b = a->left;
	a->left = b->right;
	b->right = a;

	updateTreeHeight(a);
	updateTreeHeight(b);

	return b;
}

TreeNode *rotateLeft(TreeNode *a)
{
	TreeNode *b = a->right;
	a->right = b->left;
	b->left = a;

	updateTreeHeight(a);
	updateTreeHeight(b);

	return b;
}

void deleteTree(TreeNode *root)
{
	if (root)
	{
		deleteTree((root)->left);
		deleteTree((root)->right);
		free(root);
	}
}