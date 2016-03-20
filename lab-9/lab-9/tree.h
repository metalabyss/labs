typedef struct _TreeNode
{
	int value;
	int height;
	struct _TreeNode *left;
	struct _TreeNode *right;
} TreeNode;

int getHeight(TreeNode *node);

void updateTreeHeight(TreeNode *node);

int getBalance(TreeNode *node);

TreeNode *rebalance(TreeNode *node);

TreeNode *buildTree(TreeNode *root, int value);

TreeNode *rotateRight(TreeNode *node);

TreeNode *rotateLeft(TreeNode *node);

void deleteTree(TreeNode *root);