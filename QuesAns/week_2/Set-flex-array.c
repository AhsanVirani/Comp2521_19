// Set.c ... Set ADT implementation
// Written by John Shepherd, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "Set.h"

#define INIT_ELEMS 10

// concrete data structure
struct SetRep {
	int nelems;
	int maxelems;
	int *elems;   // pointer to first element in the array
};

// check whether Set looks plausible
bool isValid(Set s)
{
	if (s == NULL) return false;
	if (s->nelems < 0) return false;
	if (s->maxelems < INIT_ELEMS) return false;
	if (s->elems == NULL) return false;
	return true;
}

// create new empty set
Set newSet()
{
	Set s;
	if ((s = malloc(sizeof(struct SetRep))) == NULL) {
		fprintf(stderr, "Insufficient memory for Set\n");
		exit(EXIT_FAILURE);
	}
	if ((s->elems = malloc(INIT_ELEMS*sizeof(int))) == NULL) {
		fprintf(stderr, "Insufficient memory for Set\n");
		exit(EXIT_FAILURE);
	}
	s->nelems = 0;
	s->maxelems = INIT_ELEMS;
	// assert(isValid(s));
	return s;
}

// free memory used by set
void dropSet(Set s)
{
	// assert(isValid(s));
	free(s->elems);
	free(s);
}

// make a copy of a set
Set SetCopy(Set s)
{
	// assert(isValid(s));
	Set new = newSet();
#if 1 
	for (int i = 0; i < s->nelems; i++)
		SetInsert(new, s->elems[i]);
#endif
#if 0
	// assumes |s| <= INIT_ELEMS
	for (int i = 0; i < s->nelems; i++)
		new->elems[i] = s->elems[i];
#endif
#if 0
	// assumes |s| <= INIT_ELEMS
	memcpy(new->elems, s->elems, s->nelems*sizeof(int));
#endif
	// assert(isValid(new));
	return new;
}

// add value into set
void SetInsert(Set s, int n)
{
	// assert(isValid(s));
	if (SetMember(s,n)) return;
	if (s->nelems == s->maxelems) {
		// set array full, make a bigger one
		//s->maxelems = 133*s->maxelems/100;
		int newmaxelems = 2*s->maxelems;
		//s->maxelems++;
		s->elems = realloc(s->elems, newmaxelems*sizeof(int));
		/*
		int *new = malloc(newmaxelems*sizeof(int));
		memcpy(new, s->elems, newmaxelems*sizeof(int));
		free(s->elems);
		s->elems = new;
		*/
		s->maxelems = newmaxelems;
		assert(s->elems != NULL);
	}
	s->elems[s->nelems] = n;
	s->nelems++;
	// assert(isValid(s));
}

// remove value from set
void SetDelete(Set s, int n)
{
	// assert(isValid(s));
	int i;
	for (i = 0; i < s->nelems; i++)
		if (s->elems[i] == n) break;
	if (i < s->nelems) {
		// overwrite i'th element with last
		s->elems[i] = s->elems[s->nelems-1];
		s->nelems--;
	}
}

// set membership test
bool SetMember(Set s, int n)
{
	// assert(isValid(s));
	for (int i = 0; i < s->nelems; i++)
		if (s->elems[i] == n) return true;
	return false;
}

// union
Set SetUnion(Set s, Set t)
{
	// assert(isValid(s) && isValid(t));
	Set new = SetCopy(s);
	for (int i = 0; i < t->nelems; i++)
		SetInsert(new,t->elems[i]);
	return new;
}

// intersection
Set SetIntersect(Set s, Set t)
{
	// assert(isValid(s) && isValid(t));
	Set new = newSet();
	for (int i = 0; i < s->nelems; i++) {
		if (SetMember(t, s->elems[i]))
			SetInsert(new, s->elems[i]);
	}
	return new;
}

// cardinality (#elements)
int SetCard(Set s)
{
	// assert(isValid(s));
	return s->nelems;
}

// display set as {i1,i2,i3,...iN}
void showSet(Set s)
{
	// assert(isValid(s));
	printf("{");
	int i;
	for (i = 0; i < s->nelems; i++) {
		printf("%d", s->elems[i]);
		if (i < s->nelems-1) printf(",");
	}
	printf("}");
}

// read+insert set values
void readSet(FILE *in, Set s)
{
	// assert(isReadable(in) && isValid(s));
	int val;
	while (fscanf(in, "%d", &val) == 1)
		SetInsert(s, val);
}
