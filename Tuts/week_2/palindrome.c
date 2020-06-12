#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
	char *cpy = s;
	int j = 0; int i;

	for(i = strlen(s)-1; i > j; i--)
	{
		if(s[i] == cpy[j])	j++;
		else break;
	}

	if(i == j)	return "yes";
	return "no";
}
