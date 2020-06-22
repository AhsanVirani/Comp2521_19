// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Dict.h"
#include "WFreq.h"

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

// Returns the pointer the node containing word if found
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

// Avl tree implementation
static
Link insertAVL(Link root, char *w)
{
	// Base case of Null
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

// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
	assert(w != NULL);
	
	// if Dict rep is null we insert at head
	if(d == NULL)
	{
		d = newDict();
		d->tree = newNode();
		setData(d->tree, w);
		return &(d->tree->data);
	}
	// Check whether already exists
	// If yes then return the WFreq pair
	if(inDict(d->tree, w) != NULL)
	{
		inDict(d->tree, w)->data.freq++;
		return &(inDict(d->tree, w)->data);
	}
	// Avl tree implementation
	// returns the Link to new node inserted
	Link root = insertAVL(d->tree, w);

	return &(inDict(root, w)->data);	
}

// find Word in Dictionary
// return pointer to (word,freq) pair, if found
// otherwise return NULL
WFreq *DictFind(Dict d, char *w)
{
   // TODO
   return NULL;
}

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
   // TODO
   return 0;
}

// print a dictionary
void showDict(Dict d)
{
   // TODO if you need to display Dict's for debugging
   return;
}


int
white_box(void)
{

	Dict d = newDict();
	Link a = newNode();
	Link b = newNode();
	Link c = newNode();
	a->data.word = malloc(sizeof(3));
	a->data.word = "US";
	a->data.freq++;
	d->tree = a;
	b->data.word = malloc(sizeof(8));
	b->data.word = "England";
	b->data.freq++;
	a->right = b;
	c->data.word = malloc(sizeof(9));
	c->data.word = "Pakistan";
	c->data.freq++;
	b->left = c;

	printf("(%s, %d)\n",DictInsert(d, "Pakistan")->word, DictInsert(d, "Pakistan")->freq);
	
	return 0;
}

