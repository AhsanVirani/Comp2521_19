#include <stdio.h>

int
main(void)
{
// WHICH WHILE LOOP IS EQUI-VALENT
/*
	char ch;
	for (ch = getchar(); ch != EOF; ch = getchar())
	{
		putchar(ch);
	}
*/
	char ch;
	ch = getchar();
	while(ch != EOF)
	{
		putchar(ch);
		ch = getchar();
	}

	return 0;
}
