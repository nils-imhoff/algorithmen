#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int main(int argc, char *argv[])
{
	int c, i;
	int  r;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	c = atoi(argv[1]);

	srand(time(NULL));

	for(i=0; i<c; i++)
	{
		r = rand() % MAX; 
		printf("%d\n", r);
	}
	exit(EXIT_SUCCESS);
}
