#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "splay_tree.h"

/*
static int
test(void)
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
*/

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
	return t;
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


