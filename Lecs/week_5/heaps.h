// Heaps H File

#ifndef HEAPS_H
#define HEAPS_H

typedef struct HeapRep *Heap;
typedef int Item;

Heap newHeap(int);
void HeapInsert(Heap, Item);
void fixUp(Item a[], int);
void swap(Item a[], int, int);

void white_box();

#endif
