#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node *Tree;

struct Node{
	int data;
	Tree left, right;
} Node;

#define data(node) ((node)->data)
#define left(node) ((node)->left)
#define right(node) ((node)->right)

bool
TreeContains(Tree, int);

int
main(void)
{
	Tree a = malloc(sizeof(struct Node));
	Tree b = malloc(sizeof(struct Node));
	Tree c = malloc(sizeof(struct Node));
	Tree d = malloc(sizeof(struct Node));
	Tree e = malloc(sizeof(struct Node));
	Tree f = malloc(sizeof(struct Node));
	Tree g = malloc(sizeof(struct Node));

	data(a) = 8; data(b) = 5, data(c) = 2; data(d) = 0; data(e) = 6;
	data(f) = 7; data(g) = 9;
	left(a) = b; right(a) = g;
	left(b) = c; right(b) = e;
	left(c) = d; right(c) = NULL;
	left(d) = right(d) = NULL;
	left(e) = NULL; right(e) = f;
	left(f) = right(f) = NULL;
	left(g) = right(g) = NULL;  


	if(TreeContains(a, 6))	printf("Value Found\n");
		else	printf("Value Not Found :(\n");

	return 0;
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
