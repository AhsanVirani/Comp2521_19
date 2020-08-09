#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
   
	char line[1000] = "20 50 80 10 |";
	char *results = strtok(line, "|");
	int numbers[10];	

int i;
 while ((results = strtok(i ? NULL : line, " ")) != NULL)
        numbers[i++] = atoi(results);
printf("%d", i);
printf("%d %d %d", numbers[0], numbers[1], numbers[2]);

	return 0;
}
