#include <stdio.h>

#include "avl_tree.h"


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

	set_Tree_node(a, 5);
	set_Tree_node(b, 2);
	set_Tree_node(c, 1);
	set_Tree_node(d, 4);
	set_Tree_node(e, 3);
	set_Tree_node(f, 8);
	set_Tree_node(g, 7);

	left(a) = b; right(a) = f;
	left(b) = c; right(b) = d;
	left(c) = NULL; right(c) = NULL;
	left(d) = e; right(d) = NULL;
	left(e) = NULL; right(e) = NULL;
	left(f) = g; right(f) = NULL;
	left(g) = NULL; right(g) = NULL;

	a = insertAVL(a, 6);
	printf("%d\n", data(left(right(a))));

	return 0;
}
