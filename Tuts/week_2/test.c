#include <stdio.h>

int
main(void)
{
	char *c = "ABC";
	printf("%c\n", *c);
	*c='a';	
	printf("%c\n", c);
	return 0;
}
