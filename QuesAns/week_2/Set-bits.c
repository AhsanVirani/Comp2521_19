// Set.c ... Set ADT implementation
// Written by John Shepherd, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "Bits.h"
#include "Set.h"

// concrete data structure
struct SetRep {
	int  nelems;
	BitS bits;    // Word bits[NWORDS];
};

// Local functions

// check whether Set looks plausible
bool isValid(Set s)
{
	return (s != NULL);
}

// Interface functions

// create new empty set
Set newSet()
{
#if 0
	// cheeky ... might work
	Set new = calloc(1+NWORDS,sizeof(int));
	assert(new != NULL);
#else
	Set new = malloc(sizeof(struct SetRep));
	assert(new != NULL);
	new->nelems = 0;
	for (int i = 0; i < NWORDS; i++) new->bits[i] = 0;
#endif
	return new;
}

// free memory used by set
void dropSet(Set s)
{
	assert(isValid(s));
	free(s);
}

// make a copy of a set
Set SetCopy(Set s)
{
	Set new = newSet();
	new->nelems = s->nelems;
	for (int i = 0; i < NWORDS; i++)
		new->bits[i] = s->bits[i];
	return new;
}

// add value into set
void SetInsert(Set s, int n)
{
	assert(0 <= n && n <= NBITS-1);
	setBit(s->bits, n);
	s->nelems++;
}

// remove value from set
void SetDelete(Set s, int n)
{
	assert(0 <= n && n <= NBITS-1);
	unsetBit(s->bits, n);
	s->nelems--;
}

// set membership test
bool SetMember(Set s, int n)
{
	assert(0 <= n && n <= NBITS-1);
	return getBit(s->bits, n);
}

// union
Set SetUnion(Set s, Set t)
{
	Set new = newSet();
	BitUnion(s->bits, t->bits, new->bits);
	return new;
}

// intersection
Set SetIntersect(Set s, Set t)
{
	// assert(isValid(s) && isValid(t));
	Set new = newSet();
	BitIntersect(s->bits, t->bits, new->bits);
	return new;
}

// cardinality (#elements)
int SetCard(Set s)
{
#if 1
	// assert(isValid(s))
	return s->nelems;
#else
	int i, nbits = 0;
	for (i = 0; i < NBITS; i++) {
		if (getBit(s->bits,i)) nbits++;
	}
	return nbits;
#endif
}

// display set as {i1,i2,i3,...iN,}
// Note: trailing comma; exercise: don't print it
void showSet(Set s)
{
	// assert(isValid(s));
	int i;
	printf("{");
    for (i = 0; i < NBITS; i++) {
		if (getBit(s->bits,i)) break;
	}
	printf("%d",i); 
    for (i++; i < NBITS; i++) {
		if (getBit(s->bits,i)) printf(",%d",i);
	}
	printf("}");
}

// read+insert set values
void readSet(FILE *in, Set s)
{
	// assert(isReadable(in) && isValid(s));
	int n;
	while (fscanf(in,"%d",&n) == 1) {
		SetInsert(s, n);
	}
}
