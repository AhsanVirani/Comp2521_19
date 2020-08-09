#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heaps.h"

typedef int Item;
// Heaps structure definition
typedef struct HeapRep {
	Item *Items;	// array of Items
	int nitems;		// #items in array
	int nslots;		// #elements in array
} HeapRep;

Heap newHeap(int N)
{
	Heap new = malloc(sizeof(HeapRep));
	Item *a = malloc(sizeof(Item) * (N+1));
	assert(new != NULL && a != NULL);
	new->Items = a;	// no initialisaton needed
	new->nitems = 0;	// counter and index
	new->nslots = N;	// index range 1...N

	return new;
}

void HeapInsert(Heap h, Item it)
{
	// is there space in the array? realloc otherwise
	assert(h->nitems < h->nslots);
	h->nitems++;
	// add new item at end of array
	h->Items[h->nitems] = it;
	// move new item to its correct place
	fixUp(h->Items, h->nitems);
}

void fixUp(Item a[], int i)
{
	// Work until reach root. No node above so stop
	// if parent is less than child then swap
	// make i the parent
	while(i > 1 && (a[i/2] < a[i])) {
		swap(a,i, i/2);
		i = i/2;
	}
}

void swap(Item a[], int i, int j)
{
	Item tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void white_box()
{
	return;	
}
