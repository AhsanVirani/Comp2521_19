#include <stdio.h>
#include <assert.h>

int 
factorial(int n)
{
	assert(n >= 0);
	// Base case
	if(n == 0 || n == 1)	return 1;
	
	return n * factorial(n-1);
}


int
main(void)
{
	int num = factorial(7);
	printf("%d\n", num);	

	return 0;
}
