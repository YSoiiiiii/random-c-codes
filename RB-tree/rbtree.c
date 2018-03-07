#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


enum color {red,black,dummy};
struct node
{
	enum color color;
	int val;
	struct node* left;
	struct node* right;
	struct node* parent;
};
//API
//I will be using a dummy node
enum color getColor(struct node* root);
struct node* initNewTree(int val);
struct node* makeNewNode(int val, struct node* parent, enum color color);
void llRotate(struct node** pointer);
void lrRotate(struct node** pointer);
void rrRotate(struct node** pointer);
void rlRotate(struct node** pointer);
void insert1(struct node* root, int newVal);
void insert(struct node* dummy, int newVal);
void delete(struct node* dummy, int val);
void delete1(struct node* root, int val);
void countBlack(struct node* root, int curVal);
void inorder(struct node* root);
int findmax(struct node* root);
int findmin(struct node* root);
void printTree(struct node* root, int spaces);
//114!514!fa!?

void countBlack(struct node* root,int curVal)
{
	if (root == NULL)
	{
		printf("%d ", curVal+1);
		return;
	}
	if (root->color == black)
	{
		countBlack(root->left, curVal + 1);
		countBlack(root->right, curVal + 1);
		return;
	}
	else
	{
		countBlack(root->left, curVal);
		countBlack(root->right, curVal);
		return;
	}
}
void inorder(struct node* root)
{
	if (root == NULL)
	{
		return;
	}
	inorder(root->left);
	printf("%d ", root->val);
	inorder(root->right);
	return;
}
void checkParent(struct node* root, struct node* father)
{
	if (root == NULL)
	{
		return;
	}
	if (root->parent != father)
	{
		printf("funckcud");
		return;
	}
	else
	{
		printf("11454as ");
		checkParent(root->left, root);
		checkParent(root->right, root);
		return;
	}
}
struct node* foo;

int main(void)
{
	foo = initNewTree(1);
	for (int i = 2; i <= 20; i++)
	{
		insert(foo, i);
	}
	for (int i = 5; i <= 15; i++)
	{
		delete(foo, i);
	}
	printTree(foo->right, 2);
	system("pause");
	return 0;
}

void printTree(struct node *root, int spaces)
//found this online, much elegeant
{
	while (root != NULL)
	{
		printTree(root->right, spaces + 4);
		for (int loop = 1; loop <= spaces; loop++)
		{
			printf(" ");
		}
		printf("%d", root->val);
		root->color == red ? printf("r") : printf("b");
		printf("\n");
		printTree(root->left, spaces + 4);
		root = NULL;
	}
}
enum color getColor(struct node* root)
{
	if (!root)
	{
		return black;
	}
	else
	{
		return root->color;
	}
}
struct node* initNewTree(int val)
{
	struct node* dummy = makeNewNode(INT_MIN, NULL, 2);
	dummy->right = makeNewNode(val, dummy, black);
	return dummy;
}
struct node* makeNewNode(int val, struct node* parent, enum color color)
{
	struct node* ret = malloc(sizeof(struct node));
	ret->color = color;
	ret->left = NULL;
	ret->right = NULL;
	ret->val = val;
	ret->parent = parent;
	return ret;
}
/*rotations can be only used for insertion*/
void llRotate(struct node** pointer)//single rotate
{
	struct node* G = *pointer, *P = (*pointer)->left, 
		 *X = (*pointer)->left->left;
	//rotate
	G->left = P->right;
	P->right = G;
	*pointer = P;
	//dye
	P->color = black;
	G->color = red;
	//change parent
	P->parent = G->parent;
	G->parent = P;
	if (G->left)
	{
		G->left->parent = G;
	}
	return;
}
void lrRotate(struct node** pointer)//double rotate
{
	struct node* G = *pointer, *P = (*pointer)->left,
		 *X = (*pointer)->left->right;
	//rotate
	P->right = X->left;
	G->left = X->right;
	X->left = P;
	X->right = G;
	*pointer = X;
	//dye
	X->color = black;
	G->color = red;
	//change parent
	if (P->right)
	{
		P->right->parent = P;
	}
	if (G->left)
	{
		G->left->parent = P;
	}
	X->parent = G->parent;
	G->parent = X;
	P->parent = X;
	return;
}
void rrRotate(struct node** pointer)//symmetric single rotate
{
	struct node* G = *pointer, *P = (*pointer)->right,
		 *X = (*pointer)->right->right;
	//rotate
	G->right = P->left;
	P->left = G;
	*pointer = P;
	//dye
	P->color = black;
	G->color = red;
	//change parent
	P->parent = G->parent;
	G->parent = P;
	if (G->right)
	{
		G->right->parent = G;
	}
	return;
}
void rlRotate(struct node** pointer)//double rotate
{
	struct node* G = *pointer, *P = (*pointer)->right,
		 *X = (*pointer)->right->left;
	//rotate
	P->left = X->right;
	G->right = X->left;
	X->right = P;
	X->left = G;
	*pointer = X;
	//dye
	X->color = black;
	G->color = red;
	//change parent
	if (P->left)
	{
		P->left->parent = P;
	}
	if (G->right)
	{
		G->right->parent = P;
	}
	X->parent = G->parent;
	G->parent = X;
	P->parent = X;
	return;
}

void insert(struct node* dummy, int newVal)
{
	insert1(dummy->right, newVal);
	dummy->right->color = black;
}
void insert1(struct node* root,int newVal)
{
	//dye
	if(getColor(root->left) == red && getColor(root->right) == red)
	{
		root->color = red;
		root->left->color = black;
		root->right->color = black;
		//
		if (getColor(root->parent) == red)//then rotate
		{
			if (root->parent->left == root)
			{
				if (root->parent->parent->left == root->parent)//ll
				{
					if (root->parent->parent->parent->left == root->parent->parent->parent)
					{
						llRotate(&(root->parent->parent->parent->left));
					}
					else
					{
						llRotate(&(root->parent->parent->parent->right));
					}
				}
				else//rl
				{
					if (root->parent->parent->parent->left == root->parent->parent->parent)
					{
						rlRotate(&(root->parent->parent->parent->left));
					}
					else
					{
						rlRotate(&(root->parent->parent->parent->right));
					}
				}
			}
			else
			{
				if (root->parent->parent->left == root->parent)//lr
				{
					if (root->parent->parent->parent->left == root->parent->parent->parent)
					{
						lrRotate(&(root->parent->parent->parent->left));
					}
					else
					{
						lrRotate(&(root->parent->parent->parent->right));
					}
				}
				else//rr
				{
					if (root->parent->parent->parent->left == root->parent->parent->parent)
					{
						rrRotate(&(root->parent->parent->parent->left));
					}
					else
					{
						rrRotate(&(root->parent->parent->parent->right));
					}
				}
			}
		}
	}
	////
	if (newVal > root->val)//insert right
	{
		if (root->right)
		{
			insert1(root->right, newVal);
		}
		else
		{
			if (getColor(root) == black)
			{
				root->right = makeNewNode(newVal, root, red);
			}
			else//then rotation
			{
				root->right = makeNewNode(newVal, root, red);
				if (root->parent->right == root)//rrRotate
				{
					if (root->parent->parent->left == root->parent->parent)
					{
						rrRotate(&(root->parent->parent->left));
					}
					else
					{
						rrRotate(&(root->parent->parent->right));
					}
				}
				else//lrRotate
				{
					if (root->parent->parent->left == root->parent->parent)
					{
						lrRotate(&(root->parent->parent->left));
					}
					else
					{
						lrRotate(&(root->parent->parent->right));
					}
				}
			}//
		}
	}
	else if (newVal < root->val)//insert left
	{
		if (root->left)
		{
			insert1(root->left, newVal);
		}
		else
		{
			if (getColor(root) == black)
			{
				root->left = makeNewNode(newVal, root, red);
			}
			else//then rotation
			{
				root->left = makeNewNode(newVal, root, red);
				if (root->parent->left == root)//llRotate
				{
					if (root->parent->parent->left == root->parent->parent)
					{
						llRotate(&(root->parent->parent->left));
					}
					else
					{
						llRotate(&(root->parent->parent->right));
					}
				}
				else//lrRotate
				{
					if (root->parent->parent->left == root->parent->parent)
					{
						lrRotate(&(root->parent->parent->left));
					}
					else
					{
						lrRotate(&(root->parent->parent->right));
					}
				}
			}//
		}
	}
	return;
}

void delete1(struct node* root, int val)
{
 	if (getColor(root) != red)
	{
		//if parent is black
		if (root->parent->color == black)
		{
			struct node **ptr = NULL;
			if (root->parent->parent->left == root->parent)
			{
				ptr = &(root->parent->parent->left);
			}
			else
			{
				ptr = &(root->parent->parent->right);
			}

			if (root->parent->left == root)
			{
				struct node *P = root->parent, *T = root->parent->right;
				T->parent = P->parent;
				P->parent = T;
				if (T->left)
				{
					T->left->parent = P;
				}
				*ptr = T;
				P->right = T->left;
				T->left = P;
				P->color = red;
				T->color = black;
			}
			else
			{
				struct node *P = root->parent, *T = root->parent->left;
				T->parent = P->parent;
				P->parent = T;
				if (T->right)
				{
					T->right->parent = P;
				}
				*ptr = T;
				P->left = T->right;
				T->right = P;
				P->color = red;
				T->color = black;
			}
			delete1(root, val);
			return;
		}

		//rotate to make sure "root" is red
		if (getColor(root->left) == black&&getColor(root->right) == black)
		{
			struct node **ptr = NULL;
			if (root->parent->parent->left == root->parent)
			{
				ptr = &(root->parent->parent->left);
			}
			else
			{
				ptr = &(root->parent->parent->right);
			}


			if (root->parent->left == root)
			{
				struct node *P = root->parent, *T = root->parent->right;
				if (T == NULL)
				{
					P->color = black;
					root->color = red;
				}
				else if (getColor(T->left) == black&&getColor(T->right) == black)
				{
					P->color = black;
					root->color = red;
					T->color = red;
				}
				else if (getColor(T->right) == red)
				{
					struct node *R = T->right;
					T->parent = P->parent;
					P->parent = T;
					if (T->left)
					{
						T->left->parent = P;
					}
					*ptr = T;
					P->right = T->left;
					T->left = P;
					root->color = red;
					P->color = black;
					T->color = red;
					R->color = black;
				}
				else
				{
					struct node *R = T->left;
					R->parent = P->parent;
					P->parent = R;
					T->parent = R;
					if (R->left)
					{
						R->left->parent = P;
					}
					if (R->right)
					{
						R->right->parent = T;
					}
					*ptr = R;
					P->right = R->left;
					T->left = R->right;
					R->left = P;
					R->right = T;
					P->color = black;
					root->color = red;
				}
			}
			else
			{
				struct node *P = root->parent, *T = root->parent->left;
				if (T == NULL)
				{
					P->color = black;
					root->color = red;
				}
				else if (getColor(T->right) == black&&getColor(T->left) == black)
				{
					P->color = black;
					root->color = red;
					T->color = red;
				}
				else if (getColor(T->left) == red)
				{
					struct node *R = T->left;
					T->parent = P->parent;
					P->parent = T;
					if (T->right)
					{
						T->right->parent = P;
					}

					*ptr = T;
					P->left = T->right;
					T->right = P;
					root->color = red;
					P->color = black;
					T->color = red;
					R->color = black;
				}
				else
				{
					struct node *R = T->right;
					R->parent = P->parent;
					P->parent = R;
					T->parent = R;
					if (R->right)
					{
						R->right->parent = P;
					}
					if (R->left)
					{
						R->left->parent = T;
					}

					*ptr = R;
					P->left = R->right;
					T->right = R->left;
					R->right = P;
					R->left = T;
					P->color = black;
					root->color = red;
				}
			}
		}
	}


	//delete leaf
	if (root->left == NULL&&root->right == NULL)
	{
		if (root->val == val)
		{
			if (root->parent->left == root)
			{
				root->parent->left = NULL;
				free(root);
			}
			else
			{
				root->parent->right = NULL;
				free(root);
			}
		}
		return;
	}

	//else
	if (val > root->val)
	{
		delete1(root->right, val);
	}
	else if (val < root->val)
	{
		delete1(root->left, val);
	}
	else
	{
		if (root->left)
		{
			root->val = findmax(root->left);
			delete1(root->left, root->val);
		}
		else
		{
			root->val = findmin(root->right);
			delete1(root->right, root->val);
		}
	}
	return;
}
int findmax(struct node* root)
{
	struct node*p = root;
	while (p->right != NULL)
	{
		p = p->right;
	}
	return p->val;
}
int findmin(struct node* root)
{
	struct node*p = root;
	while (p->left != NULL)
	{
		p = p->left;
	}
	return p->val;
}
void delete(struct node* dummy, int val)
{
	struct node* lesserDummy = makeNewNode(INT_MIN, NULL, 2/*dummy*/);
	lesserDummy->right = dummy;
	dummy->parent = lesserDummy;
	dummy->color = red;

	delete1(dummy->right, val);

	free(lesserDummy);
	dummy->parent = NULL;
	dummy->color = 2/*dummy*/;
	dummy->right->color = black;
}
