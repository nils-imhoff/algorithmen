#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define MAXITEM 1000

int main(int argc, char *argv[])
{
	FILE *in = stdin;
	int c, n;
	char l[MAX];
	char* i;
	int dn;
	char* d[MAXITEM];

	c = 0;

	if(argc > 2)
	{
		fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(argc == 2)
	{
		in = fopen(argv[1], "r");
		if(!in)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}	

	while((i=fgets(l, MAX, in)))
	{
		if(c == MAXITEM){
			printf("zu viele Items");
			exit(EXIT_FAILURE);
		}
		d[c++] = strdup(i);
	}
	for(n=c; n; n--)
	{
		printf("%s", d[n-1]);
	}

	if(in!=stdin)
	{
		fclose(in);
	}
	exit(EXIT_SUCCESS);
}
