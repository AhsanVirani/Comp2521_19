#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
	int i, j, *a;
	int N = 0;

	// initialisation
	assert(argc > 1);
	sscanf(argv[1], "%d", &N);
	assert(N > 0);
	a = malloc(N*sizeof(int));
	assert(a != NULL);

	for(i = 2; i < N; i++)	a[i] = 1;
	
	// computation
	for(i = 2; i < N; i++)
	{
		if(a[i])
		{
			for(j = i; i*j < N; j++)	a[i*j] = 0;		
		}
	}

	// Results
	for(i = 2; i < N; i++)
	{
		if(a[i]) printf("%d\n", i);
	}

	return 0;
}

