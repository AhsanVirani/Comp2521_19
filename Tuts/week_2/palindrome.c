#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// Complexity of Algo worst case n/2

char *
palindrome(char *);

int
main(int argc, char *argv[])
{
	assert(argc == 2);
	printf("%s\n", palindrome(argv[1]));

	return 0;
}

char *
palindrome(char *s)
{
	assert(s != NULL);

	int j = 0; int i;	//O(1) assignment
	for(i = strlen(s)-1; i > j; i--)	// loop until mid point reached O(n/2)
	{
		if(s[i] == s[j])	j++;	// O(n/2)
		else break;	// O(1)
	}

	if(i == j)	return "yes";	// O(1)
	return "no";	// O(1)
}
