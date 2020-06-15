#include <stdio.h>

int
func1(int x)
{
	x = -1;
	return x;
}

int
main(void)
{
	int x = 0;
	printf("%d\n", func1(x));

	return 0;
}
