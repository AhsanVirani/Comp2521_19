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

int
main(void)
{
	// making tree T1
	Tree a = Tree_new();
	Tree b = Tree_new();
	Tree c = Tree_new();
	
	set_Tree_node(a, 10); set_Tree_node(b, 5), set_Tree_node(c, 14);
	
	left(a) = b; right(a) = c;
	left(b) = right(b) = NULL;
	left(c) = right(c) = NULL;

	// making tree T2
	Tree d = Tree_new();
	Tree e = Tree_new();
	Tree f = Tree_new();
	Tree g = Tree_new();

	set_Tree_node(d, 30); set_Tree_node(e, 24); set_Tree_node(f, 32); 
	set_Tree_node(g, 29);

	left(d) = e; right(d) = f;
	left(e) = NULL; right(e) = g;
	left(f) = right(f) = NULL;
	left(g) = right(g) = NULL;  

	Tree joined = tree_join(a, d);
	printf("Root is: %d\n", data(joined));
	printf("LS: parent = %d left child = %d right child = %d\n", data(left(joined)), data(left(left(joined))), data(right(left(joined))));
	printf("RS: parent = %d left child = %d right child = %d\n", data(right(joined)), data(left(right(joined))), data(right(right(joined))));
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



