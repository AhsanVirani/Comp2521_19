#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heaps.h"

// Static function declarations
static void fixDown(Item a[], int, int);
static void fixUp(Item a[], int);

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

static
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

// Deletion from heap (always remove root)
Item HeapDelete(Heap h)
{
	Item top = h->Items[1];
	// overwrite first by last
	h->Items[1] = h->Items[h->nitems];
	h->nitems--;
	// move new root to correct position
	fixDown(h->Items, 1, h->nitems);
	return top;	
}

// a[i] is the new root. Need to put it into correct postion
static
void fixDown(Item a[], int i, int N)
{
	while(2*i <= N) {
		// compute address of left child
		int j = 2*i;
		// choose the larger of two children
		if(j < N && (a[j] < a[j+1]))
			j++;
		if(!(a[i] < a[j]))
			break;
		swap(a, i, j);
		// move one level down
		i = j;
	}	
}


void white_box()
{
	return;	
}


