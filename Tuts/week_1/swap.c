#include <stdio.h>

void
swap(int *a, int i, int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}


int
main(void)
{
	int array[5] = {1,2,3,4,5};
	swap(array, 4, 3);
	printf("%d %d\n", array[4], array[3]);
	return 0;
}
