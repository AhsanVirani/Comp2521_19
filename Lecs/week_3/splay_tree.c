#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "tree.h"

typedef struct Node *Tree;

struct Node{
	int data;
	Tree left, right;
} Node;

#define data(node) ((node)->data)
#define left(node) ((node)->left)
#define right(node) ((node)->right)

static
Tree
splay(Tree, int);

int
main(void)
{
	// making tree 
	Tree a = Tree_new();
	Tree b = Tree_new();
	Tree c = Tree_new();
	Tree d = Tree_new();
	Tree e = Tree_new();
	Tree f = Tree_new();	
	Tree g = Tree_new();	
	Tree h = Tree_new();	

	// Setting tree nodes
	set_Tree_node(a, 14); set_Tree_node(b, 11), set_Tree_node(c, 10);
	set_Tree_node(d, 12);  set_Tree_node(e, 31); set_Tree_node(f, 22);
	set_Tree_node(g, 26);  set_Tree_node(h, 35); 
	
	a->left = b; a->right = e;
	b->left = c; b->right = d;
	c->left = NULL; c->right = NULL;
	d->left = NULL; d->right = NULL;
	e->left = f; e->right = h;
	f->left = NULL; f->right = g;
	g->left = NULL; g->right = NULL;
	h->left = NULL; h->right = NULL;

	Tree t = search_splay(a, 22);
	if(t == NULL)	printf("Node not found\n");
	else	printf("%d %d %d %d %d\n", t->data, t->left->data, t->left->left->data, t->right->data, t->right->left->data);

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

// Set node in a tree
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

// Insert a node with key in a tree
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
	else	return T;	
}

// print in pre-order 
void
tree_preorder(Tree T)
{
	if(T == NULL)	return;
	printf("%d\n", data(T));
	tree_preorder(left(T));
	tree_preorder(right(T));
}

// print in-order
void
tree_inorder(Tree T)
{
	if(T == NULL)	return;
	tree_inorder(left(T));
	printf("%d\n", data(T));
	tree_inorder(right(T));
}

// print post-order
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

	if(T1 == NULL)	return T2;
	else if(T2 == NULL)	return T1;
	
	Tree curr = T2;
	Tree parent = NULL;
	while(left(curr) != NULL)
	{
		parent = curr;
		curr = left(curr);
	}
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
	if(T == NULL)	return TreeInsert(T, it);
	else if(it < data(T))
	{
		left(T) = insert_root(T->left, it);
		T = rotateRight(T); 
	}
	else if(it > data(T))
	{
		right(T) = insert_root(T->right, it);
		T = rotateLeft(T); 
	}
	
	return T;
}


Tree
tree_partition(Tree t, int i)
{
	int m = size_leftSubtree(t->left);
	if(i < m)
	{
		left(t) = tree_partition(left(t), i);
		t = rotateRight(t);
	}
	else if(i > m)
	{
		right(t) = tree_partition(right(t), i-m-1);
		t = rotateLeft(t);
	}

	return t;
}

int
size_leftSubtree(Tree t)
{
	if(t == NULL)	return 0;
		return 1 + size_leftSubtree(left(t)) + size_leftSubtree(right(t));
}

int 
BSTreeNumNodes(Tree t)
{
	if(t == NULL)	return 0;
	return 1 + BSTreeNumNodes(left(t)) + BSTreeNumNodes(right(t));
}

int 
BSTreeHeight(Tree t) 
{
	if(t == NULL) return -1;	
	return 1 + max(BSTreeHeight(left(t)), BSTreeHeight(right(t)));
}

int
max(int a, int b)
{
	return a > b? a : b;
}

int 
countInternal(Tree t)
{
	if(t == NULL) return 0;
	else if(left(t) && right(t) != NULL)	return 1 + countInternal(left(t)) + countInternal(right(t));
	else if(left(t) != NULL)	return 1 + countInternal(left(t));
	else if(right(t) != NULL)	return 1 + countInternal(right(t));
	else return 0;
}

int 
nodeDepth(Tree t, int key)
{
	if(TreeContains(t, key) == false)	return -1;
	else if(key < t->data)	return 1 + nodeDepth(left(t), key);
	else if(key > t->data)	return 1 + nodeDepth(right(t), key);
	else	return 0;
}

int 
BSTWidth(Tree t)
{
	if(t == NULL)	return 0;
	return 3 + BSTWidth(left(t)) + BSTWidth(right(t));
}

// insertion in a splay tree
Tree
insertSplay(Tree t, int item)
{
// if empty, make new and return
	if(t == NULL)
	{
		t = Tree_new();
		set_Tree_node(t, item);
		return t;
	}
	else if(TreeContains(t, item) == true)	return t;
	// Left Subtree
	else if(item < data(t))
	{
		if(left(t) == NULL)
		{
			left(t) = Tree_new();
			set_Tree_node(left(t), item);
		}
		else if(item < data(left(t)))
		{
		//	Case 1: left of left
		//	insert into left subtree, rotate right, rotate right 
			t->left->left = insertSplay(t->left->left, item);
			t = rotateRight(t);
		}
		else if(item > data(left(t)))
		{
		// Case 2: right of left
		//	insert into left subtree, rotate left, rotate right
			t->left->right = insertSplay(t->left->right, item);
			t->left = rotateLeft(t->left);
		}
		return rotateRight(t);
	}
	// Right Subtree
	else if(item > data(t))
	{
		if(right(t) == NULL)
		{
			right(t) = Tree_new();
			set_Tree_node(right(t), item);
		}

		else if(item < data(right(t)))
		{
		// Case 3: left of right
		// insert into right subtree, rotate right, rotate left
			t->right->left = insertSplay(t->right->left, item);
			t->right = rotateRight(t->right);
		}
		else
		{
		// Case 4: right of right
		//	insert into right subtree, rotate left, rotate left 
			t->right->right = insertSplay(t->right->right, item);
			t = rotateLeft(t);
		}
		return rotateLeft(t);	
	}
}

// address of the item if found else NULL
Tree
search_splay(Tree t, int item)
{
	if(t == NULL)	return t;
	else if(TreeContains(t, item) == false)	return NULL;
	else	return splay(t, item);
	
}

// if item found in splay tree makes it node. Just a complement function for search_splay
static
Tree
splay(Tree t, int item)
{
	// Left Subtree
	if(item < data(t))
	{
		
		if(item < data(left(t)))
		{
		//	Case 1: left of left
		//	insert into left subtree, rotate right, rotate right 
			t->left->left = splay(t->left->left, item);
			t = rotateRight(t);
		}
		else if(item > data(left(t)))
		{
		// Case 2: right of left
		//	insert into left subtree, rotate left, rotate right
			t->left->right = splay(t->left->right, item);
			t->left = rotateLeft(t->left);
		}
		return rotateRight(t);
	}
	// Right Subtree
	else if(item > data(t))
	{
		if(item < data(right(t)))
		{
		// Case 3: left of right
		// insert into right subtree, rotate right, rotate left
			t->right->left = splay(t->right->left, item);
			t->right = rotateRight(t->right);
		}
		else if(item > data(right(t)))
		{
		// Case 4: right of right
		//	insert into right subtree, rotate left, rotate left 
			t->right->right = splay(t->right->right, item);
			t = rotateLeft(t);
		}
		return rotateLeft(t);	
	}
	else return t;
}


