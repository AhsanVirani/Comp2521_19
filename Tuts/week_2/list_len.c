#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _node{
	int data;
	struct _node *next;
} Node;

typedef Node *List;

int length(List);

int
main(void)
{
	List a = malloc(sizeof(*a));
	List b = malloc(sizeof(*b));
	List c = malloc(sizeof(*c));
	List d = malloc(sizeof(*d));
	List e = malloc(sizeof(*e));

	a->data = 1; b->data = 2; c->data = 3; d->data = 3; e->data = 3;
	a->next = b;	b->next = c; c->next = d; d->next = e; e->next = NULL; 
	printf("Size of the list: %d\n", length(a));

	return 0;
}

int 
length(List L)
{
	assert(L != NULL);
	List curr; size_t len = 0;
	for(curr = L; curr != NULL; curr = curr->next)	len++;
	
	return len;
}
