#include <stdio.h>
#include <ctype.h>

int 
main(void)
{
	int ch;
	char *type;
	ch = getchar();

	if(isdigit(ch)) type  = "Digit";
		else	type = "non-Digit";

	printf("%s\n", type);
	
	return 0;
}
