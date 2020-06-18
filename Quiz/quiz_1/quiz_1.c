#include <stdio.h>


int myFunction(int n);
int factorial(int n);

long power(int x, unsigned int n);

int
main(void)
{
	printf("%d\n", myFunction(100));
	printf("%d\n", factorial(100));
	printf("%ld\n", power(5, 10));

	return 0;
}

int 
myFunction(int n)
{
	int i = 0;
	while(n > 0)
	{
		i++;
		n = n/2;
	}
	return i;
}

int factorial(int n)
{
   long product = 1;
	int counter = 0;
   for (int i = 1; i <= n; i++)
	{      
		product *= i;
		counter++;
	}   
	return counter;
}


long 
power(int x, unsigned int n)
{
	long raised = x;
	for(int i = 0; i <= n; i++)	raised *= i;
	
	return raised;
}

