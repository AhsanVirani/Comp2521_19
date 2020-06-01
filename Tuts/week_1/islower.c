#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int 
main(void)
{
	char ch = 's';	

	assert(islower(ch));
	if(ch == 'a' || ch == 'e' || ch == 'i' ||
		ch == 'o' || ch == 'u')	printf("vowel\n");
		else	printf("consonant\n");

	return 0;
}
