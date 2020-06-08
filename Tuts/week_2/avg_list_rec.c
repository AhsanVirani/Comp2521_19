#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _node {
   int data;
   struct _node *next;
} Node;
typedef Node *List;


float
mean(List L);

int
sum(List L);

int
list_size(List L);

int
main(void)
{
	List a = malloc(sizeof(*a));
	List b = malloc(sizeof(*b));
	List c = malloc(sizeof(*c));
	List d = malloc(sizeof(*d));
	List e = malloc(sizeof(*e));

	a->data = 10; b->data = 100; c->data = 40; d->data = 50; e->data = 50;
	a->next = b;	b->next = c; c->next = d; d->next = e; e->next = NULL; 
	printf("Average of the list: %0.0f\n", mean(a));
	return 0;
}

float
mean(List L)
{
	assert(L != NULL);	
	List curr = L;
	return (float)sum(curr)/list_size(curr);
}

int
sum(List L)
{
	if(L->next == NULL)	return L->data;
	return L->data + sum(L->next);
}

int
list_size(List L)
{
	if(L->next == NULL)	return 1;
	return 1+ list_size(L->next);
}
