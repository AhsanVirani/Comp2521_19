#include <stdio.h>
#include <ctype.h>

int
main(void)
{
	char *type;
	int ch;

	ch = getchar();
	type = (isdigit(ch)? "Digit": "Non-Digit");
	printf("%s\n", type);

	return 0;
}
