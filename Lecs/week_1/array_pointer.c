#include <stdio.h>

int
find_key(int a[], int len)	// int a[] == int *a
{
	return a[4];
}

int
main(void)
{
	int a[5] = {1, 2, 3, 4, 5};
	int x = find_key(a, 5);	
	printf("%d\n", x);
	return 0;
}


