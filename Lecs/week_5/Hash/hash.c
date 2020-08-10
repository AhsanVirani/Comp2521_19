#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"

typedef int Item;
// Heaps structure definition
typedef struct HashTableRep {
	Item **items;	// array of (Items *)
	int N;			// size of array
	int nitems;		// #items in array
} HashTableRep;

HashTable newHashTable(int N)
{
	HashTable new = malloc(sizeof(HashTableRep));
	new->items = malloc(sizeof(Item *) * N);
	new->N = N;
	new->nitems = 0;
	for(int i = 0; i < N; i++)
		new->items[i] = NULL;	
	return new;
}

void HashDelete(HashTable ht, Key k)
{

}

void white_box()
{
	return;	
}


