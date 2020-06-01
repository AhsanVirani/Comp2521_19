#include <stdio.h>

int 
main(void)
{

	char ch = 's';

	// S1
	switch(ch)
	{
		case 'a': printf("eh? "); break;
		case 'e': printf("eee "); break;
		case 'i': printf("eye "); break;
		case 'o': printf("ohh "); break;
		case 'u': printf("you "); break;
		default: printf("Not Found");
	}

	printf("\n");

	return 0;
}
