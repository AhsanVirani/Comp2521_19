
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
	else {
		if(strcmp(w, root->data.word) > 0)	root->left = insertAVL(root->left, w);
		else if(strcmp(w, root->data.word) < 0)	root->right = insertAVL(root->right, w);
	} /*
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
*/
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
		wfs[i].word = NULL; wfs[i].freq = -1;
	}
	
	fillTopN(d->tree, wfs, n);
	
	int member = 0;
	for(int i = 0; i < n && wfs[i].word != NULL && wfs[i].freq != -1; i++)	member++;
	
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


///////////////////
// Stopwords Dictionary
//////////////////

	Dict stopwordDict = newDict();
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
	
	//showDict(stopwordDict);
//////////////////
// Scan File up to start of the text
/////////////////

	Dict gutenburg = newDict();
	in = fopen("0011.txt", "r");
	if(in == NULL)
	{
		fprintf(stderr, "Can't open %s\n","0011.txt");
		exit(EXIT_FAILURE);
	}

	while(fgets(line, MAXLINE, in) != NULL)
	{
		if(strncmp(line, STARTING, strlen(STARTING)) == 0)	break;
	}
		
	int j; // to fill word
	int k = 0; // for stemming purpose
	WFreq *isstop;	// To check whether stopword matches word extracted from file
	WFreq *printstr;
	while(fgets(line, MAXLINE, in) != NULL)
	{
		// Line has content so do something
		if(strcmp(line,"\n"  ) != 0 && strcmp(line,"\r\n") != 0 && strcmp(line,"\0"  ) != 0 && 1)
		{
			// If line reads ENDING point then break
			if(strncmp(line, ENDING, strlen(ENDING)) == 0)	break;
			
			// takes characters from line and form word. apply relevant checks.
			
			for(int i = 0; i < strlen(line)-1; i++)
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
				{	// got the word here

					isstop = DictFind(stopwordDict, word);
					if(isstop == NULL) 
					{
						k = stem(word, 0, (strlen(word)-1));
						word[k+1] = '\0';
						printstr = DictInsert(gutenburg, word);
						printf("(%s, %d)\n", printstr->word, printstr->freq);
					}			
					
		
					for(j = 0; j < MAXWORD; j++)	word[j] = '\0';
					j = 0;
				}
		
				else	j = 0;
			}
		}
		// Line is empty so skip to next line
		
		else continue;
	}


/*






	///////STOPWORDICT//////////////
	FILE * s;
	int i;
	char arr[50] = "";
	s = fopen("stopwords", "r");
	if(s == NULL)	
	{	
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}	
	Dict stopwordDict = newDict();
	while(fscanf(s, "%s", arr) != EOF)	DictInsert(stopwordDict, arr);
	fclose(s);




	
	char line[1000] = "";
	char word[100] = "";
	FILE *in;		
	in = fopen("0011.txt", "r");
	int j;
	WFreq *rem;
	WFreq *results;
	int k = 0;
	Dict gutenburgDict = newDict();

	assert(in != NULL);
	while(fgets(line, 1000, in) != NULL)
	{
		if(strncmp(line, STARTING, 12) == 0) break;
		for(i = 0; i < strlen(line); i++)	{line[i] = '\0';}
	}


	while(fgets(line, 1000, in) != NULL)
	{
		if(strncmp(line, ENDING, 10) == 0)	break;
		j = 0;
		for(int i = 0; i < strlen(line); i++)
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
			if(line[i] == ' ' || !isWordChar(line[i]))
			{
				rem = DictFind(stopwordDict, word);
				if(rem == NULL && j > 0)	
				{
					k = stem(word, 0, (strlen(word)-1));
					word[k+1] = '\0';
					rem = DictInsert(gutenburgDict, word);
					printf("(%s, %d)\n", rem->word, rem->freq);
				}				
				for (int k = 0; k < j; k++)
				{
					word[k+1] = '\0';
				}
				j = 0;
			}
		
		}
		for(i = 0; i < strlen(line); i++)	line[i] = '\0';
	}
	//int topN = findTopN(gutenburgDict, results, 10);
	//for(int i = 0; i < topN; i++)	printf("(%s, %d)\n", results->word, results->freq);



	fclose(in);

*/

	//destroyTree(stopwordDict->tree);
	//destroyTree(gutenburgDict->tree);
	//destroyDict(stopwordDict);
	//destroyDict(gutenburgDict);
	return 0;
}