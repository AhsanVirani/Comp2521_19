#include <stdio.h>

int
main(void)
{
	char *type;
	char ch;

	type = (isdigit(ch)? "Digit": "Non-Digit");
	printf("%c is of type %s", ch, type);

	return 0;
}
