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
	char *monthName;
	
	switch(num)
	{
	case 1: monthName = "Jan"; break;
	case 2: monthName = "Feb"; break;
	case 3: monthName = "Mar"; break;	
	case 4: monthName = "Apr"; break;
	case 5: monthName = "May"; break;
	case 6: monthName = "Jun"; break;
	case 7: monthName = "Jul"; break;
	case 8: monthName = "Aug"; break;
	case 9: monthName = "Sep"; break;
	case 10: monthName = "Oct"; break;
	case 11: monthName = "Nov"; break;
	case 12: monthName = "Dec"; break;
	default: monthName = "January"; break;
	}

	return monthName;
}

void
giveUp(char *progName)
{
	fprintf(stderr, "Usage: %s 1..12\n", progName);
	exit(EXIT_FAILURE);
}
