#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main(int argc, char *argv[])
{
	FILE *in = stdin;
	char l[MAX];
	char* i;
	int dn;

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
		int dn = 2* atoi(l);
		printf("%d\n", dn);
	}


	if(in!=stdin)
	{
		fclose(in);
	}
	exit(EXIT_SUCCESS);
}
