#include <stdio.h>
#include <stdlib.h>

// Func Declarations

void giveUp(char *);
char *monthName(int);

int 
main(int argc, char *argv[])
{
	if(argc < 2)	giveUp(argv[0]);
	int n = atoi(argv[1]);
	if(n < 1 || n > 12)	giveUp(argv[0]);

	// Compute and print name
	printf("%s\n", monthName(n));

	exit(EXIT_SUCCESS);
}

char *
monthName(int num)
{
	char *monthName[13] = {"???", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
									"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		
	return monthName[num];
}

void
giveUp(char *progName)
{
	fprintf(stderr, "Usage: %s 1..12\n", progName);
	exit(EXIT_FAILURE);
}
