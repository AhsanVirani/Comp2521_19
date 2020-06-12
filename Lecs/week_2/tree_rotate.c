#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node *Tree;

struct Node{
	int data;
	Tree left, right;
} Node;

#define data(node) ((node)->data)
#define left(node) ((node)->left)
#define right(node) ((node)->right)

Tree
Tree_new();

bool
TreeContains(Tree, int);

Tree
TreeInsert(Tree, int);

void
set_Tree_node(Tree, int);

void
tree_preorder(Tree);

void
tree_inorder(Tree);

void
tree_postorder(Tree);

Tree
tree_join(Tree, Tree);

Tree
rotateLeft(Tree);

Tree
rotateRight(Tree);

int
main(void)
{
	// making tree T1
	Tree a = Tree_new();
	Tree b = Tree_new();
	Tree c = Tree_new();
	Tree d = Tree_new();
	Tree e = Tree_new();	

	set_Tree_node(a, 8); set_Tree_node(b, 6), set_Tree_node(c, 4);
	set_Tree_node(d, 7);  set_Tree_node(e, 10);
	
	left(a) = b; right(a) = e;
	left(b) = c; right(b) = d;
	left(c) = right(c) = NULL;
	left(d) = right(d) = NULL;
	left(e) = right(e) = NULL;

	//printf("root: %d LS: par = %d c1 = %d c2 = %d RS: %d\n", data(l), data(left(l), data(left(left(l))), data(left(right(l))), data(right(l)));
	Tree l = rotateRight(a);
	printf("The Right Rotation is:\n");
	printf("root: %d LS: %d RS: par = %d c1 = %d c2 = %d\n", data(l), data(left(l)), data(right(l)), data(left(right(l))), data(right(right(l))));

	Tree r = rotateLeft(l);
	printf("The Left Rotation is:\n");
	printf("%d %d %d %d %d\n", r->data, r->left->data, r->left->left->data, r->left->right->data, r->right->data);

	return 0;
}

// Create a new tree
Tree
Tree_new()
{
	Tree T = malloc(sizeof(struct Node));
	assert(T != NULL);
	set_Tree_node(T, 0);
	T->left= T->right = NULL;
	
	return T;
}

void
set_Tree_node(Tree T, int key)
{
	assert(T != NULL);
	T->data = key;
}

// Searching in BSTs
bool
TreeContains(Tree T, int key)
{
	if(T == NULL)	return false;
	if(key < data(T))	return TreeContains(left(T), key);
		else if(key > data(T))	return TreeContains(right(T), key);
		else	return true;
}

Tree
TreeInsert(Tree T, int key)
{
	if(T == NULL)
	{
		T = Tree_new();
		set_Tree_node(T, key);
		return T;
	}

		else if(key < data(T))
		{	
			left(T) = TreeInsert(left(T), key);
			return T;
		}
		else if(key > data(T))	
		{		
			right(T) = TreeInsert(right(T), key);
			return T;
		}		
		else	return T;	// avoids duplicate
}

void
tree_preorder(Tree T)
{
	if(T == NULL)	return;
	printf("%d\n", data(T));
	tree_preorder(left(T));
	tree_preorder(right(T));
}

void
tree_inorder(Tree T)
{
	if(T == NULL)	return;
	tree_inorder(left(T));
	printf("%d\n", data(T));
	tree_inorder(right(T));
}

void
tree_postorder(Tree T)
{
	if(T == NULL) return;
	tree_postorder(left(T));
	tree_postorder(right(T));
	printf("%d\n", data(T));		
}

Tree
tree_join(Tree T1, Tree T2)
{
	assert(T1 && T2 != NULL);
	// if one null, return the other
	if(T1 == NULL)	return T2;
		else if(T2 == NULL)	return T1;
	
	Tree curr = T2;
	Tree parent = NULL;
	while(left(curr) != NULL)
	{
		parent = curr;
		curr = left(curr);
	}
	// case of one node
	if(parent == NULL)	left(curr) = T1;
		else
		{
			left(parent) = right(curr);
			right(curr) = NULL;
			left(curr) = T1; right(curr) = T2;
		}

	return curr;
}

Tree
rotateRight(Tree T)
{
	if(T == NULL || left(T) == NULL)	return T;
	Tree tmp = left(T);
	left(T) = right(tmp);
	right(tmp) = T;
	return tmp;
}

Tree
rotateLeft(Tree T)
{
	if(T == NULL || right(T) == NULL)	return T;
	Tree tmp = right(T);
	right(T) = left(tmp);
	left(tmp) = T;
	return tmp;
}

