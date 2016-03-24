typedef struct _TreeNode
{
	int value;
	int height;
	struct _TreeNode *left;
	struct _TreeNode *right;
} TreeNode;

int getHeight(TreeNode *node);

/* Функция обновляет высоту каждого поддерева (после ребалансировки или вставки нового листа)
	node - указатель на вершину (под)дерева */
void updateTreeHeight(TreeNode *node);

/* Функция возращает значение баланса для текущей вершины
	node - указатель на вершину (под)дерева */
int getBalance(TreeNode *node);

/* Функция ребалансировки дерева (делает её, если нужно).
	 node - указатель на вершину (под)дерева,
	 возвращаемое значение - указатель на вершину сбалансированнго дерева. */
TreeNode *rebalance(TreeNode *node);


TreeNode *buildTree(TreeNode *root, int value);

/* Функция, производящая малый правый поворот дерева.
	node - указатель на вершину изменяемого поддерева,
	возвращаемое значение - указатель на вершину повернутого дерева. */
TreeNode *rotateRight(TreeNode *node);

/* Функция, поизводящая малый левый поворот дерева.
	node - указатель на вершину изменяемого поддерева,
	возвращаемое значение - указатель на вершину повернутого дерева. */
TreeNode *rotateLeft(TreeNode *node);

/* Функция удаляет дерево и освобождает память. */
void deleteTree(TreeNode *root);