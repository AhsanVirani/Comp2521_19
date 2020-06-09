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

int
main(void)
{
	// making new tree nodes
	Tree a = Tree_new();
	Tree b = Tree_new();
	Tree c = Tree_new();
	Tree d = Tree_new();
	Tree e = Tree_new();
	Tree f = Tree_new();
	Tree g = Tree_new();
	// setting the data of each node
	set_Tree_node(a, 8); set_Tree_node(b, 5), set_Tree_node(c, 2);
	set_Tree_node(d, 0); set_Tree_node(e, 6); set_Tree_node(f, 7); 
	set_Tree_node(g, 9);
	// connecting nodes as BST
	left(a) = b; right(a) = g;
	left(b) = c; right(b) = e;
	left(c) = d; right(c) = NULL;
	left(d) = right(d) = NULL;
	left(e) = NULL; right(e) = f;
	left(f) = right(f) = NULL;
	left(g) = right(g) = NULL;  

	// Search
	if(TreeContains(a, 4))	printf("Value Found\n");
		else	printf("Value Not Found :(\n");

	// insertion test
	Tree t = TreeInsert(a, 4);
	if(TreeContains(a, 4))	printf("Value Found\n");
		else	printf("Value Not Found :(\n");
	printf("%d\n", a->left->left->right->data);

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
