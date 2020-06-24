
// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
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

// Defintion of static Function used

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

static
void destoryWFreq(WFreq *);


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

// Free WFreq array
static
void destoryWFreq(WFreq *wfs)
{
	free(wfs);
	return;
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

// fill top N by frequency in WFreq array
// Support func for findTopN
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
	
			for(int j = n-2; j > i; j--)	wfs[j+1] = wfs[j];
			
			if(i+1 < n && tmp.word != NULL)	wfs[i+1] = tmp;	
			break;
		}
	}
}

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
	assert(d != NULL && wfs != NULL && n > 0);
	
	wfs = (WFreq *)malloc(n*sizeof(WFreq));
	for(int i = 0; i < n; i++)
	{
		wfs[i].word == NULL; wfs[i].freq = -1;
	}
	
	fillTopN(d->tree, wfs, n);
	
	int member = 0;
	for(int i = 0; i < n && wfs[i].word != NULL && wfs[i].freq != -1; i++)	member++;
	destoryWFreq(wfs);
   return member;
}

// Show WFreq

// print a dictionary
// Showing Dict in preorder traversal order
void showDict(Dict d)
{
	preorderTraversal(d->tree);	

   return;
}

// White Box Testing
int
white_box(void)
{
	////////////// Testing Insertion /////////////
	// Passing NULL Dict
	//printf("%d\n", findTopN(NULL, wfs, 10));
	// Passing Null wfs
	Dict d = newDict();
	WFreq *wfs;	
	// Case of 2 node
	WFreq *n1 = DictInsert(d, "US");
	WFreq *n2 = DictInsert(d, "England");
	WFreq *n3 = DictInsert(d, "England");
	WFreq *n4 = DictInsert(d, "England");
	WFreq *n5 = DictInsert(d, "England");
	WFreq *n6 = DictInsert(d, "England");
	WFreq *n7 = DictInsert(d, "Pakistan");
	WFreq *n8 = DictInsert(d, "Pakistan");
	WFreq *n9 = DictInsert(d, "Pakistan");
	WFreq *n10 = DictInsert(d, "US");
	WFreq *n11 = DictInsert(d, "US");
	WFreq *n12 = DictInsert(d, "Afghanistan");
	WFreq *n13 = DictInsert(d, "Afghanistan");
	WFreq *n14 = DictInsert(d, "Australia");
	WFreq *n15 = DictInsert(d, "Australia");
	printf("%d\n", findTopN(d, wfs, 2));
	


	destroyTree(d->tree);
	destroyDict(d);
	return 0;
}

