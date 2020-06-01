#include <stdio.h>

int 
main(void)
{
	int x, y;
	char *c, *d, *e, *f;

	x = y = 2;
	//c = d = "abc";
	e = "xyz"; f = "xyz"; 

	printf("memory after first Assignments");
	printf("memory of x: %p\n", &x);	
	printf("memory of y: %p\n", &y);	
	printf("memory of c: %p\n", c);	
	printf("memory of d: %p\n", d);	
	printf("memory of e: %p\n", e);	
	printf("memory of f: %p\n", f);	

	x++;
	printf("State of memory after x++: %p\n", &x);

	c = "abc";
	d = c;
	printf("c points to: %p\nd points to: %p\n", c, d);

	return 0;

}

