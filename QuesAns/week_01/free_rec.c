#include <stdio.h>

void
dofreenodes(IntListNode *n)
{
	if(n == NULL)	return;
		else	{dofreenodes(n->next);	free(n);}
}

void
freeIntList (IntList L)
{
	// recursively free all the nodes
	dofreenodes(L->first);
	// free the list rep at the end
	free(L);
}

int
main(void)
{

	return 0;
}
