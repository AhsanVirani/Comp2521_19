#include <stdio.h>
#include <assert.h>

// A function that converts num into Day
char *
numToDay(int n)
{
	assert(0 <= n && n <= 6);
	char *day;
	if(n == 0)	day = "Sun";
		else if(n == 1)	day = "Mon";
		else if(n == 2)	day = "Tue";
		else if(n == 3)	day = "Wed";
		else if(n == 4)	day = "Thu";
		else if(n == 5)	day = "Fri";
		else if(n == 6)	day = "Sat";
	
	return day;
}

char *
alternate_1(int n)
{
	assert(0 <= n && n <= 6);

	char *day;
	switch(n)
	{
		case 0: return day = "Sun"; break;
		case 1: return day = "Mon"; break;
		case 2: return day = "Tue"; break;
		case 3: return day = "Wed"; break;
		case 4: return day = "Thu"; break;
		case 5: return day = "Fri"; break;
		case 6: return day = "Sat"; break;
	}

}

int
main(void)
{

	char *day = alternate_1(5);
	printf("%s\n", day);	

	return 0;
}
