#include <stdio.h>
#include <stdlib.h>

// implementation of realloc to increase the size of an array. Good to use 

int
main(void)
{
	int *array = malloc(3*sizeof(int));
	array[0] = 0;
	array[1] = 1;
	array[2] = 2;

	printf("%d %d %d\n", array[0], array[1], array[2]);

	array = realloc(array, 5);
	array[3] = 3;
	array[4] = 4;
	printf("%d %d\n", array[3], array[4]);
	
	return 0;
}
