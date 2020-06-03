#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Node
{
	int value;
	struct _Node *next;
} Node;

typedef Node *List;

List
make_node()
{
	List l = malloc(sizeof(*l));
	l->value = 0;
	l->next = NULL;

	return l;
}

void
set_values(List l, int value, List next)
{
	l->value = value;
	l->next = next;
}

int
sum_val_list(List l)
{
	int sum = 0;
	List temp = l;
	for(temp; temp != NULL; temp = temp->next)
	{
		sum+=temp->value;
		//temp = temp->next;
	}
	return sum;
}

int
sum_val_list_rec(List l)
{
	assert(l != NULL);
	List temp = l;
	if(temp->next == NULL)	return temp->value;
	
	return temp->value + sum_val_list_rec(temp->next);
}

int 
main(void)
{
	List a = make_node();
	List b = make_node();
	List c = make_node();

	set_values(a, 10, b);
	set_values(b, 15, c);
	set_values(c, 20, NULL);

	int sum = sum_val_list_rec(a);
	printf("%d\n", sum);	

	// Free pointers
	a->next, b->next, c->next = NULL;
	free(a); free(b); free(c);
	a, b, c = NULL;

	return 0;
}
