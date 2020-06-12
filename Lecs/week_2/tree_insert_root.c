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

Tree
insert_root(Tree, int);

int
main(void)
{
	// making tree T1
	Tree a = Tree_new();
	Tree b = Tree_new();
	Tree c = Tree_new();
	Tree d = Tree_new();
	Tree e = Tree_new();
	Tree f = Tree_new();	

	set_Tree_node(a, 10); set_Tree_node(b, 5), set_Tree_node(c, 14);
	set_Tree_node(d, 30);  set_Tree_node(e, 29); set_Tree_node(f, 32);
	
	left(a) = b; right(a) = c;
	left(b) = right(b) = NULL;
	left(c) = NULL; right(c) = d;
	left(d) = e; right(d) = f;
	left(e) = right(e) = NULL;
	left(f) = right(f) = NULL;

	Tree t = insert_root(a, 24);
	printf("root: %d\n", t->data);
	printf("LS: %d %d %d\n", t->left->data, t->left->left->data, t->left->right->data);
	printf("RS: %d %d %d\n", t->right->data, t->right->left->data, t->right->right->data);

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

Tree
insert_root(Tree T, int it)
{
	// base case
	if(T == NULL)
	{
		return TreeInsert(T, it);
	}
		else if(it < data(T))
		{
			// Recursively call
			left(T) = insert_root(T->left, it);
			//if found node on left then rotate right right puts in on top
			T = rotateRight(T); 
		}
		else if(it > data(T))
		{
			// Recursively call
			right(T) = insert_root(T->right, it);
			//if found node on right then rotate left puts in on top
			T = rotateLeft(T); 
		}
	
	return T;
}

