#include <stdio.h>

int 
main(void)
{

	char ch = 'e';

	// S1
	switch(ch)
	{
		case 'a': printf("eh? "); 
		case 'e': printf("eee "); 
		case 'i': printf("eye "); 
		case 'o': printf("ohh "); 
		case 'u': printf("you "); 
		default: printf("Not Found");
	}

	printf("\n");


	return 0;
}
