// By Ahsan Muhammad (z5188798)
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
#include "stemmer.h"


typedef struct _DictNode *Link;

typedef struct  _DictNode {
   WFreq  data;
   Link   left;
   Link   right;
	int height;
} DictNode;

struct _DictRep {
   Link tree;
};

// Defintion of static Functions used

static
Link newNode();

static
void setData(Link, char *);

static
Link inDict(Link, char *);

static
Link insertAVL(Link, char *);

static
Link rotateRight(Link);

static
Link rotateLeft(Link);

static
int getHeight(Link);

static
int max(int, int);

static
void preorderTraversal(Link);

static
void fillTopN(Link, WFreq *, int);


// create a new empty Dictionary
Dict newDict()
{
	Dict root = malloc(sizeof(struct _DictRep));
	assert(root != NULL);
	root->tree = NULL;

   return root;
}

// create a new empty node
static
Link newNode()
{
	Link node = malloc(sizeof(DictNode));
	assert(node != NULL);
	node->data.word = NULL;	
	node->data.freq = 0; node->height = 0;
	node->left = node->right = NULL;

	return node;
}

// Set the data struct inside of the node
static
void setData(Link node, char *w)
{
	assert(node != NULL && w != NULL);
	node->data.word = strdup(w);
	node->data.freq++;
}

// Returns the pointer of the node containing word if found
// NULL otherwise
// Helper function for DictFind
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

// Rotates the Tree Right
static
Link rotateRight(Link n1)
{
	if (n1 == NULL) return NULL;
	Link n2 = n1->left;
	if (n2 == NULL) return n1;
	n1->left = n2->right;
	n2->right = n1;
	// updating heights here
	n2->right->height = max(getHeight(n2->right->left), getHeight(n2->right->right)) + 1;
	n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;

	return n2;
}

// Rotates the Tree Left
static
Link rotateLeft(Link n2)
{
	if (n2 == NULL) return NULL;
	Link n1 = n2->right;
	if (n1 == NULL) return n2;
	n2->right = n1->left;
	n1->left = n2;
	// updating heights here
	n1->left->height = max(getHeight(n1->left->left), getHeight(n1->left->right)) + 1;
	n1->height = max(getHeight(n1->left), getHeight(n1->right)) + 1;

	return n1;
}

// Returns the height of a given node
// -1 if NULL
static 
int getHeight(Link n)
{
	if( n == NULL )	return -1;
	return n->height;
}

// Returns maximum of two integer types
// Helper function for calculating height of a Tree
static
int max(int a, int b)
{
	return a > b? a : b;
}

// Print tree in preorder traversal i.e. (NLR)
// Helper function for showDict
static
void preorderTraversal(Link root)
{
	if(root == NULL)	return;	
	printf("(%s, %d)\n", root->data.word, root->data.freq);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Avl tree implementation
static
Link insertAVL(Link root, char *w)
{
	if(root == NULL)
	{
		root = newNode();
		setData(root, w);
		root->height = 0;	
		return root;
	}

	else if(strcmp(w, root->data.word) > 0)	
	{
		root->left = insertAVL(root->left, w);
		if(getHeight(root->left) - getHeight(root->right) == 2)
		{
			if(strcmp(w, root->left->data.word) < 0)	root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}	
	}	
	else if(strcmp(w, root->data.word) < 0)	
	{		
		root->right = insertAVL(root->right, w);
		if( getHeight(root->right) - getHeight(root->left) == 2)
		{		
			if(strcmp(w, root->right->data.word) > 0)	root->right = rotateRight(root->right);
			root = rotateLeft(root);
		}
	}
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	
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
		if(root->data.freq > wfs[i].freq || (root->data.freq == wfs[i].freq && strcmp(root->data.word, wfs[i].word) < 0))
		{
			WFreq tmp = wfs[i];
			wfs[i] = root->data;
			for(int j = n-2; j > i; j--)	wfs[j+1] = wfs[j];

			if(i+1 < n && tmp.word != NULL)	wfs[i+1] = tmp;	
			break;
		}
		else if((root->data.freq == wfs[i].freq && strcmp(root->data.word, wfs[i].word) > 0) && (i+1) < n)
		{
			if(wfs[i+1].word != NULL && strcmp(root->data.word, wfs[i+1].word) > 0)	continue;
			WFreq tmp = wfs[i+1];
			wfs[i+1] = root->data;
			for(int j = n-2; j > i+1; j--)	wfs[j+1] = wfs[j];

			if(i+2 < n)	wfs[i+2] = tmp;
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
	
	fillTopN(d->tree, wfs, n);
	int member = 0;
	for(int i = 0; i < n && wfs[i].word != NULL && wfs[i].freq != -1; i++)	member++;
	
   return member;
}

// print a dictionary
// Showing Dict in preorder traversal order
void showDict(Dict d)
{
	preorderTraversal(d->tree);	
   return;
}

