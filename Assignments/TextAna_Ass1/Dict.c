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

// Checks whether a word is in the Dict
// returns booleon
static
bool inDict(Link root, char *w)
{
	assert(w != NULL);
	if(root == NULL)	return false;
	bool found;
	// if found
	if(strcmp(w, root->data.word) == 0)	return true;
	// w < data.word so find in left subtree
	else if(strcmp(w, root->data.word) > 0)
	{
		found = inDict(root->left, w);
	}
	// w > data.word so find in right subtree
	else if(strcmp(w, root->data.word) < 0)
	{
		found = inDict(root->right, w);
	}
	// Not Found
	return found;
}

// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
	// Using AVL Tree Implementation to keep the tree balanced

	// Dict is NULL
	if(d == NULL)
	{
		d = newDict();
		d->tree = newNode();
		d->tree->data.word = strdup(w);	d->tree->data.freq++;
	}
	// word already in Dict
	else if(inDict(d->tree, w) == true)
	{
		wordLoc->data.freq++;
	}   
	// if not in Dict then AVL insert

	if(inDict(d->tree, w) == true)	printf("TRUE\n");
	else if(inDict(d->tree, w) == false)	printf("FALSE\n");

   return NULL;
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
	Dict root = newDict();
	Link a = newNode();
	Link b = newNode();
	Link c = newNode();	
	a->data.word = malloc(sizeof(3));
	a->data.word = "US";
	b->data.word = malloc(sizeof(8));
	b->data.word = "England";
	c->data.word = malloc(sizeof(9));
	c->data.word = "Pakistan";
	root->tree = a;
	a->right = b;
	b->left = c;

	if(inDict(a, "Pakistan") == true)	printf("TRUE\n");
	if(inDict(a, "China") == false)	printf("FALSE\n");

	return 0;
}

