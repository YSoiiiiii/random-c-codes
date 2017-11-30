#include<stdio.h>
#include<stdlib.h>

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif 


struct TreeNode {
	struct TreeNode *left;
	struct TreeNode *right;
	int val;
	int height;
};

typedef struct TreeNode TreeNode;


///////////////////////////////////////////000000000114514
TreeNode *make_new_node(int val);
void insert_value(TreeNode **root, int val);
void delete_value(TreeNode **root, int val); //replace root->val with biggest leftval
int find_max(TreeNode **root);
void single_rotate_left(TreeNode *root, TreeNode **fatherpointer);
void single_rotate_right(TreeNode *root, TreeNode **fatherpointer);
void double_rotate_left(TreeNode *root, TreeNode **fatherpointer);
void double_rotate_right(TreeNode *root, TreeNode **fatherpointer);
int get_height(TreeNode *root);
int isballanced(TreeNode *root);//this is a (slow) checker
int height(TreeNode *root);//this is the checker that makes others slow
int heightchecker(TreeNode *root);//this is a (slow) checker
int count(TreeNode *root);// this is a checker
/////////////////////////////////////////////////00001919

int main(void)
{
	TreeNode *root = make_new_node(5);
	for (int i = 0; i <= 100; i++)
	{
		insert_value(&root, i);
	}
	int b = count(root);
	for (int i = 40; i <= 80; i++)
	{
		int a = isballanced(root);
		delete_value(&root, i);
	}
	return 0;
}

// checkers
int count(TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return  1 + count(root->left) + count(root->right);
}
int heightchecker(TreeNode *root)
{
	if (root == NULL)
	{
		return 1;
	}
	if (height(root) != root->height)
	{
		return 0;
	}
	return heightchecker(root->left) && heightchecker(root->right);
}
int isballanced(TreeNode *root)
{
	if (!root)
	{
		return 1;
	}
	if (abs(height(root->left) - height(root->right)) >= 2)
	{
		return 0;
	}
	return isballanced(root->left) && isballanced(root->right);
}
int height(TreeNode *root)
{
	if (!root)
	{
		return -1;
	}
	return max(height(root->left), height(root->right)) + 1;
}

void single_rotate_left(TreeNode *root, TreeNode **fatherpointer)
{
	TreeNode *FirstNode = root;
	TreeNode *SecondNode = root->left;
	FirstNode->left = SecondNode->right;
	SecondNode->right = FirstNode;
	SecondNode->height = max(get_height(SecondNode->right), get_height(SecondNode->left)) + 1;
	FirstNode->height = max(get_height(FirstNode->right), get_height(FirstNode->left)) + 1;
	*fatherpointer = SecondNode;
	return;
}
void single_rotate_right(TreeNode *root, TreeNode **fatherpointer)
{
	TreeNode *FirstNode = root;
	TreeNode *SecondNode = root->right;
	FirstNode->right = SecondNode->left;
	SecondNode->left = FirstNode;
	SecondNode->height = max(get_height(SecondNode->right), get_height(SecondNode->left)) + 1;
	FirstNode->height = max(get_height(FirstNode->right), get_height(FirstNode->left)) + 1;
	*fatherpointer = SecondNode;
	return;
}
void double_rotate_left(TreeNode *root, TreeNode **fatherpointer)
{
	single_rotate_right(root->left, &(root->left));
	single_rotate_left(root, fatherpointer);
}
void double_rotate_right(TreeNode *root, TreeNode **fatherpointer)
{
	single_rotate_left(root->right, &(root->right));
	single_rotate_right(root, fatherpointer);
}
TreeNode *make_new_node(int val)
{
	TreeNode *NewNode = malloc(sizeof(TreeNode));
	NewNode->right = NULL;
	NewNode->left = NULL;
	NewNode->val = val;
	NewNode->height = 0;
	return NewNode;
}
int get_height(TreeNode *root)
{
	return root == NULL ? -1 : root->height;
}
void delete_value(TreeNode **root, int val)
{
	if (*root == NULL)
	{
		return;
	}
	//right here
	if (val == (*root)->val)
	{
		if ((*root)->left)
		{
			//slow delete, but makes it easier to rebalance
			(*root)->val = find_max(&(*root)->left);
			delete_value(&(*root)->left, (*root)->val);
		}
		else
		{
			TreeNode *tmp = *root;
			*root = (*root)->right;
			free(tmp);
		}
	}  
	//else left
	else if (val < (*root)->val)
	{
		delete_value(&(*root)->left, val);
		if (get_height((*root)->right) - get_height((*root)->left) >= 2)
		{
			if (get_height((*root)->right->right) >= get_height((*root)->right->left))
			{
				single_rotate_right(*root, root);
			}
			else
			{
				double_rotate_right(*root, root);
			}
		}
	}
	//else right
	else
	{
		delete_value(&(*root)->right, val);
		if (get_height((*root)->left) - get_height((*root)->right) >= 2)
		{
			if (get_height((*root)->left->left) >= get_height((*root)->left->right))
			{
				single_rotate_left(*root, root);
			}
			else
			{
				double_rotate_left(*root, root);
			}
		}
	}
	if (*root)
	{
		(*root)->height = max(get_height((*root)->right), get_height((*root)->left)) + 1;
	}
}
int find_max(TreeNode **root)
{
	while ((*root)->right)
	{
		root = &((*root)->right);
	}
	return (*root)->val;
}
void insert_value(TreeNode **root, int val)
{
	if (root == NULL)
	{
		return;
	}
	if (val == (*root)->val)
	{
		return;
	}
	else if (val < (*root)->val)
	{
		if ((*root)->left)
		{
			insert_value(&((*root)->left), val);
		}
		else
		{
			(*root)->left = make_new_node(val);
		}
		if (get_height((*root)->left) - get_height((*root)->right) >= 2)//leftside unbalanced
		{
			if (get_height((*root)->left->left) > get_height((*root)->left->right))
			{
				single_rotate_left(*root, root);
			}
			else
			{
				double_rotate_left(*root, root);
			}
		}
		(*root)->height = max(get_height((*root)->right), get_height((*root)->left)) + 1;
	}
	else
	{
		if ((*root)->right)
		{
			insert_value(&((*root)->right), val);
		}
		else
		{
			(*root)->right = make_new_node(val);
		}
		if (get_height((*root)->right) - get_height((*root)->left) >= 2)//rightside unbalanced
		{
			if (get_height((*root)->right->right) > get_height((*root)->right->left))
			{
				single_rotate_right(*root, root);
			}
			else
			{
				double_rotate_right(*root, root);
			}
		}
		(*root)->height = max(get_height((*root)->right), get_height((*root)->right)) + 1;
	}
	return;
}
