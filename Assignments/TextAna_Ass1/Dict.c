
// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Dict.h"
#include "WFreq.h"
//#include "Queue.h"

typedef struct _DictNode *Link;

typedef struct  _DictNode {
   WFreq  data;
   Link   left;
   Link   right;
} DictNode;

struct _DictRep {
   Link tree;
};

// Static Function Declarations

static
Link newNode();

static
Link inDict(Link, char *);

static
void setData(Link, char *);

static
Link insertAVL(Link, char *);

static
Link rotateRight(Link);

static
Link rotateLeft(Link);

static
int treeHeight(Link);

static
int max(int, int);

static
void preorderTraversal(Link);

static
void destoryTree(Link);

static
void destroyDict(Dict);

static
void fillTopN(Link, WFreq *, int);


// create new empty Dictionary
Dict newDict()
{
	Dict root = malloc(sizeof(struct _DictRep));
	assert(root != NULL);
	root->tree = NULL;
   return root;
}

// create new empty node
static
Link newNode()
{
	Link node = malloc(sizeof(DictNode));
	assert(node != NULL);
	node->data.word = NULL;	
	node->data.freq = 0;
	node->left = node->right = NULL;
	return node;
}

// Returns the pointer of the node containing word if found
// NULL otherwise
static
Link inDict(Link root, char *w)
{
	assert(w != NULL);

	if(root == NULL)	return NULL;
	Link found = NULL;
	if(strcmp(w, root->data.word) == 0)	return root;
	else if(strcmp(w, root->data.word) > 0)	found = inDict(root->left, w);
	else if(strcmp(w, root->data.word) < 0)	found = inDict(root->right, w);
	
	return found;
}

// Set the data of the node
static
void setData(Link node, char *w)
{
	assert(node != NULL && w != NULL);
	node->data.word = strdup(w);
	node->data.freq++;
}

// Rotate Tree Right
static
Link rotateRight(Link node)
{
	if(node == NULL || node->left == NULL)	return node;
	Link tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}

// Rotate Tree Left
static
Link rotateLeft(Link node)
{
	if(node == NULL || node->right == NULL)	return node;
	Link tmp = node->right;
	node->right = node->left;
	tmp->left = node;
	return tmp;
}

// Find height of tree
static
int treeHeight(Link node) 
{
	if(node == NULL) return -1;	
	return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

// Returns of maximum height of subtree
static
int max(int a, int b)
{
	return a > b? a : b;
}

// Print tree in preorder traversal i.e. NLR
static
void preorderTraversal(Link root)
{
	if(root == NULL)	return;	
	printf("(%s, %d)\n", root->data.word, root->data.freq);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Destroy Dictionary
static
void destroyTree(Link root)
{
	if(root == NULL)	return;
	destroyTree(root->left);
	destroyTree(root->right);	
	free(root->data.word); free(root);	return;
}

// Destroy Dict Rep
static
void destroyDict(Dict d)
{
	free(d);
	return;
}


static
void fillTopN(Link root, WFreq *wfs, int n)
{
	if(root == NULL)	return;
	fillTopN(root->left, wfs, n);
	fillTopN(root->right, wfs, n);
	
	for(int i = 0; i < n; i++)
	{
		if(root->data.freq >= wfs[i].freq)
		{
			WFreq tmp = wfs[i];
			wfs[i] = root->data;
	
			for(int j = n-2; j >= i+1; j--)
			{
				wfs[j+1] = wfs[j];
			}
			if(i+1 < n && tmp.word != NULL)	wfs[i+1] = tmp;
			break;
		}
	}

}


// Avl tree implementation
static
Link insertAVL(Link root, char *w)
{
	if(root == NULL)
	{
		root = newNode();
		setData(root, w);
		return root;
	}
	else if(strcmp(w, root->data.word) > 0)	root->left = insertAVL(root->left, w);
	else if(strcmp(w, root->data.word) < 0)	root->right = insertAVL(root->right, w);

	int Lheight = treeHeight(root->left);
	int Rheight = treeHeight(root->right);

	if((Lheight - Rheight) > 1)
	{	
		if(strcmp(w, root->left->data.word) < 0)	root->left = rotateLeft(root->left);
		root = rotateRight(root);
	}
	else if((Rheight - Lheight) > 1)
	{
		if(strcmp(w, root->right->data.word) > 0)	root->right = rotateRight(root->right);
		root = rotateLeft(root);
	}

	return root;
}

// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
	assert(d != NULL && w != NULL);
	
	Link exist = inDict(d->tree, w);
	if(exist != NULL)
	{
		exist->data.freq++;
		return &(exist->data);
	}
	d->tree = insertAVL(d->tree, w);
	
	return &(inDict(d->tree, w)->data);	
}

// find Word in Dictionary
// return pointer to (word,freq) pair, if found
// otherwise return NULL
WFreq *DictFind(Dict d, char *w)
{
   assert(d != NULL && w != NULL);
	
   return &(inDict(d->tree, w)->data);
}

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
	assert(d != NULL && wfs != NULL);

	// Call a function to fill the array
	fillTopN(d->tree, wfs, n);
		

   return 0;
}

// print a dictionary
// Showing Dict in preorder traversal order
void showDict(Dict d)
{
	// Pre order traversal
	preorderTraversal(d->tree);	

   return;
}

// White Box Testing
int
white_box(void)
{
	////////////// Testing Insertion /////////////
	// Passing Empty Dict
	// Test 1: Fail Assertion	
	//WFreq *n1 = DictInsert(NULL, "US");	
	// Test 2: Add single Node
	Dict d = newDict();	
	WFreq *n2 = DictInsert(d, "US");
	// Test 3: Add to the right of root
	WFreq *n3 = DictInsert(d, "England");
	// Test 4: Add to the left of right of root. AVL tree will be root: Pakistan LC: US RC: England
	WFreq *n4 = DictInsert(d, "Pakistan");
	// Test 5: Adding Same node again
	WFreq *n5 = DictInsert(d, "Pakistan");
	// Test 6: Adding Same node again
	WFreq *n6 = DictInsert(d, "US");

	// allocate space for array
	WFreq *wfs = (WFreq *)malloc(3*sizeof(WFreq));
	for(int i = 0; i < 3; i++)
	{
		wfs[i].word == NULL; wfs[i].freq = -1;
	}

	findTopN(d, wfs, 3);

	

	destroyTree(d->tree);
	destroyDict(d);
	
	return 0;
}

