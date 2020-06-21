#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "avl_tree.h"

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
	

	return 0;
}
*/

Tree
insertAVL(Tree t, int item)
{
	// empty case
	if(t == NULL)
	{
		t = Tree_new();
		set_Tree_node(t, item);
		return t;
	}
	// case to avoid duplicate
	if(TreeContains(t, item) == true)	return t;
	// if item less than data at current node then insert left
	else if(item < data(t))	left(t) = insertAVL(left(t), item);
	// if item greater than data at current node then insert right	
	else if(item > data(t))	right(t) = insertAVL(right(t), item);
	// We will be at root node here again
	// lets find the height of left and right subtree
	int Lheight = BSTreeHeight(left(t));
	int Rheight = BSTreeHeight(right(t));
	// if (L-R) > 1 we rotate right
	if((Lheight - Rheight) > 1)
	{
		if(item  > data(left(t)))	left(t) = rotateLeft(left(t));
		t = rotateRight(t);
	}
	else if((Rheight - Lheight) > 1)
	{
		if(item < data(right(t)))	right(t) = rotateRight(right(t));
		t = rotateLeft(t);
	}
	return t;
}




