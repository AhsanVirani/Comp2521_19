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
	switch(num)
	{
	case 1: return "Jan"; 
	case 2: return "Feb"; 
	case 3: return "Mar"; 	
	case 4: return "Apr"; 
	case 5: return "May"; 
	case 6: return "Jun"; 
	case 7: return "Jul"; 
	case 8: return "Aug"; 
	case 9: return "Sep"; 
	case 10: return "Oct"; 
	case 11: return "Nov"; 
	case 12: return "Dec"; 
	default: return "January"; 
	}
}

void
giveUp(char *progName)
{
	fprintf(stderr, "Usage: %s 1..12\n", progName);
	exit(EXIT_FAILURE);
}
