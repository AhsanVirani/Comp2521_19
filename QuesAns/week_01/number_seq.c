#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

///////////
// Suedo Code
//////////

	// check # arg
	// if 1 arg ... max = $1, min = 1, step = 1
	// if 2 args ... range between min = $1 and max = $2 and step = 1
	// if 3 args ... min = $1, step = $2, max = $3
	//	otherwise print usage message	

/*
	for(i = min; i <= max; i += step)
		print i

	possible errors
	#args isn't 1, 2, 3 ... fatal error ...-> HANDLED BY USAGE MESSAGE ABOVE
	some arg isn't a number ... fatal error
	step + min > max	
	max < min ... 

*/

// So I could check for errors
int 
get_value(char *argv[])
{
	assert(argv != NULL);	
	int val = atoi(argv[1]);
	if(isdigit(val) == 0)	return val;

	fprintf(stderr, "Not a Digit\n");
	exit(EXIT_FAILURE);	
}

void
show_values(int start, int step, int finish)
{	
		if(start <= finish && step >= 0)		
			{for(start; start <= finish; start+=step)	printf("%d\n", start);}
			else if(start < finish && step < 0)
			{	fprintf(stderr, "Step must be positive in this case\n");
				 exit(EXIT_FAILURE);
			}
			else if(start == finish && step <0)
				{printf("%d\n", start);}
			else if(start >= finish && step <= 0)		
				{for(start; start >= finish; start+=step)	printf("%d\n", start);}
			else
			{
				fprintf(stderr, "Step must be negative in this case\n");
				exit(EXIT_FAILURE);			
			}
		
}


int
main(int argc, char *argv[])
{
	assert(2<= argc && argc<=4);
	int start, finish;
	int step = 1;

	switch(argc)
	{	
		case 2:
			start = 1;
			finish = get_value(argv);
			break;

		case 3:
			start = get_value(argv);
			finish = get_value(argv+1);
			break;

		case 4:
			start = get_value(argv);
			step = get_value(argv+1);					
			finish = get_value(argv+2);
			break;
		default:
			fprintf(stderr, "Usage: %s [start] [step] [finish]\n", argv[0]);
			exit(EXIT_FAILURE);
			break;
	}

	show_values(start, step, finish);
	

	return 0;  
}
