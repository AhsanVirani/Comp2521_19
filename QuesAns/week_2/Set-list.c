// Set.c ... Set ADT implementation
// Written by John Shepherd, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "Set.h"

// concrete data structure
typedef struct Node *Link;

typedef struct Node {
	int  value;
	Link next;
} Node;

struct SetRep {
	int  nelems;
	Link elems;
};

// Local functions

// check whether Set looks plausible
bool isValid(Set s)
{
	if (s == NULL) return false;
	if (s->nelems < 0) return false;
	if (s->nelems > 0 && s->elems == NULL) return false;
	return true;
// OR
//  return (s != NULL && s->nelems >= 0);
}

// Interface functions

// create new empty set
Set newSet()
{
	Set new = malloc(sizeof(struct SetRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// free memory used by set
void dropSet(Set s)
{
	// assert(isValid(s));
	Node *curr, *next;
	curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(s);
}

// make a copy of a set
Set SetCopy(Set s)
{
	// assert(isValid(s));
	Set new = newSet();
	Node *curr;
	curr = s->elems;
	while (curr != NULL) {
		SetInsert(new, curr->value);
		curr = curr->next;
	}
	return new;
}

// add value into set
void SetInsert(Set s, int n)
{
	// assert(isValid(s));
	if (SetMember(s,n)) return;
	Node *new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = n;
	new->next = s->elems;
	s->elems = new;
	s->nelems++;
}

// remove value from set
void SetDelete(Set s, int n)
{
	// assert(isValid(s));
	if (s->nelems == 0) return;
	Node *curr, *prev = NULL;
	for (curr = s->elems; curr != NULL; curr = curr->next) {
		if (curr->value == n) break;
		prev = curr;
	}
	// curr points at item to delete; prev points at prior Node
	if (curr == NULL) return;
	if (prev == NULL)
		s->elems = curr->next;
	else
		prev->next = curr->next;
	free(curr);
	s->nelems--;
}

// set membership test
bool SetMember(Set s, int n)
{
	// assert(isValid(s));
	Node *curr = s->elems;
	while (curr != NULL) {
		if (curr->value == n) return true;
		curr = curr->next;
	}
	return false;
}

// union c = a U b
Set SetUnion(Set a, Set b)
{
	// assert(isValid(a) && isValid(b));
	Set c = newSet();
	Node* curr;
	for (curr = a->elems; curr != NULL; curr = curr->next)
		SetInsert(c, curr->value);
	for (curr = b->elems; curr != NULL; curr = curr->next)
		SetInsert(c, curr->value);
	return c;
}

// intersection, c = a /\ b
Set SetIntersect(Set a, Set b)
{
	// assert(isValid(s) && isValid(t));
	Set c = newSet();
	Node *curr;
	for (curr = a->elems; curr != NULL; curr = curr->next) {
		if (SetMember(b,curr->value)) {
			SetInsert(c, curr->value);
		}
	}
	return c;
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
	Node *cur;
	for (cur = s->elems; cur != NULL; cur = cur->next) {
		printf("%d", cur->value);
		if (cur->next != NULL) printf(",");
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
