#include <stdio.h>
#include <assert.h>

int
sum_list(int a[], int len)
{
	assert(a != NULL);
	if(len == 1)	return a[0];
	len -= 1;
	int sum = a[len];
	return sum + sum_list(a, len);
}

int 
main(void)
{
	int a[5] = {1, 2, 3, 4, 5};
	printf("%d\n", sum_list(a, 5));
	return 0;
}
