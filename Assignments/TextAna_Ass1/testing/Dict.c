
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
#include "Queue.h"

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')
#define STARTING "*** START OF"
#define ENDING   "*** END OF"
#define STOPWORDS "stopwords"
#define MAXLINE 1000
#define MAXWORD 100

//#include "Queue.h"

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
void fillTopN(Link, WFreq *, int);

static int getHeight(Link);

static
void TreeLevelOrder (Link);


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
	node->data.freq = 0; node->height = 0;
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
Link rotateRight(Link n1)
{
	if (n1 == NULL) return NULL;
	Link n2 = n1->left;
	if (n2 == NULL) return n1;
	n1->left = n2->right;
	n2->right = n1;
	return n2;
}

// Rotate Tree Left
static
Link rotateLeft(Link n2)
{
	if (n2 == NULL) return NULL;
	Link n1 = n2->right;
	if (n1 == NULL) return n2;
	n2->right = n1->left;
	n1->left = n2;
	return n1;
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

static 
int getHeight(Link n )
{
	if( n == NULL )
        return -1;
	return n->height;
}

// Avl tree implementation
static
Link insertAVL(Link root, char *w)
{
	if(root == NULL)
	{
		root = newNode();
		setData(root, w);
		root->height = 0;	// upda height
		return root;
	}

	else if(strcmp(w, root->data.word) > 0)	
	{
		root->left = insertAVL(root->left, w);
		if( getHeight(root->left) - getHeight(root->right) == 2)
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
	// do something with height
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
	//TreeLevelOrder (d->tree);
   return;
}

static
WFreq *makeWFreq(int n)
{
	WFreq *wfs = (WFreq *)malloc(n*sizeof(WFreq));
	for(int i = 0; i < n; i++)
	{
		wfs[i].word = NULL; wfs[i].freq = -1;
	}
	return wfs;

}


// print values in level-order
static
void TreeLevelOrder (Link t)
{
	if (t == NULL)	return;
	// initialise Queue
	Queue q = newQueue ();
	// add T's root node to queue
	QueueJoin (q, t);
	while (!QueueIsEmpty (q))
	{
		t = QueueLeave (q);
		printf ("%d %s\n", t->data.freq,t->data.word);
		if (t->left != NULL)	QueueJoin (q, t->left);
		if (t->right != NULL)	QueueJoin (q, t->right);
	} // TODO
	dropQueue(q);
}


// White Box Testing
int
white_box(void)
{


///////////////////
// Stopwords Dictionary
//////////////////

	Dict stopwordDict = newDict();	// 1 stopword Dict
	FILE *in;
	char line[MAXLINE] = "";
	char word[MAXWORD] = "";


	in = fopen(STOPWORDS, "r");
	if(in == NULL)	
	{	
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}	
	while(fgets(line, MAXWORD, in) != NULL)
	{
		for(int i = 0; i < strlen(line)-1; i++)	word[i] = line[i];
		DictInsert(stopwordDict, word);
		for(int i = 0; i < MAXWORD; i++)	word[i] = '\0';
	}
	fclose(in);
	
	

//////////////////
// Scan File up to start of the text
/////////////////

	Dict gutenburg = newDict();	// 1 gutenburg Dict
	in = fopen("/home/ason/proj/Comp2521_20/Assignments/TextAna_Ass1/data/2600.txt", "r");
	if(in == NULL)
	{
		fprintf(stderr, "Can't open %s\n","2600.txt");
		exit(EXIT_FAILURE);
	}

	while(fgets(line, MAXLINE, in) != NULL)
	{
		if(strncmp(line, STARTING, strlen(STARTING)) == 0)	break;
	}
		
	int j; // to fill word
	int k = 0; // for stemming purpose
	WFreq *results = makeWFreq(50);	// WFreq array
	while(fgets(line, MAXLINE, in) != NULL)										// loop (n)
	{
		if(strcmp(line,"\n"  ) != 0 && strcmp(line,"\r\n") != 0 && strcmp(line,"\0"  ) != 0 && 1)
		{
			if(strncmp(line, ENDING, strlen(ENDING)) == 0)	break;
			
			for(int i = 0; i < strlen(line)-1; i++)								// loop (strlen of line)
			{
				if(line[i] != ' ' && isWordChar(line[i]))
				{
					if(line[i] >= 65 && line[i] <= 90)	
					{				
						word[j] = line[i] + 32;
					}
					else 
					{		
						word[j] = line[i];
					}
					j++;
				}
				else if( ( line[i] == ' ' || !isWordChar(line[i]) ) && j > 1)
				{
					if(DictFind(stopwordDict, word) == NULL) 
					{
						k = stem(word, 0, (strlen(word)-1));
						word[k+1] = '\0';
						DictInsert(gutenburg, word);
					}			
					for(j = 0; j < MAXWORD; j++)	word[j] = '\0';			// loop (strlen of word (100))
					j = 0;
				}
				else	j = 0;
			}
		}	
		else continue;
	}

	fclose(in);
	
	int topN = findTopN(gutenburg, results, 50);
	for(int i = 0; i < topN; i++)	printf("(%s, %d)\n", (*(results+i)).word, (*(results+i)).freq);

	destroyTree(stopwordDict->tree);
	destroyTree(gutenburg->tree);
	destroyDict(stopwordDict);
	destroyDict(gutenburg);
	destoryWFreq(results);

	return 0;
}
