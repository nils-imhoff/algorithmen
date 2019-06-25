#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 256
#define MAXITEM 100000

void insert(int* array, int elemente) {
   int index,smallIndex,smallValue;

   
   for(index=1; index< elemente; index++) {
      
      smallValue=array[index];
      
      for( smallIndex=index;
           array[smallIndex-1] > smallValue&&smallIndex > 0;
           smallIndex-- )
      
         array[smallIndex] = array[smallIndex-1];
      
      array[smallIndex]=smallValue;
   }
}





void printArray(int* arr, int elements) {
   int i;
   for(i=0;i<elements; i++)

      printf("%d\n",arr[i]);
}


void quicksort(int *target, int left, int right) {
  if(left >= right) return;
  int i = left, j = right;
  int tmp, pivot = target[i];
  for(;;) {
    while(target[i] < pivot) i++;
    while(pivot < target[j]) j--;
    if(i >= j) break;
    tmp = target[i]; target[i] = target[j]; target[j] = tmp;
    i++; j--;
  }
  quicksort(target, left, i-1);
  quicksort(target, j+1, right);
}

int cmpInteger(const void *wert1, const void *wert2) {
   return (*(int*)wert1 - *(int*)wert2);
}

int main(int argc, char *argv[]) {
    FILE *in = stdin;
	char l[MAX];
	char* i;
    int d[MAXITEM];
    int e[MAXITEM];
    int f[MAXITEM];
    int c = 0;
    clock_t start,ende;


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
	
         d[c++] = atoi(l);
         //c++;
	}
    for(int k = 0; k < c; k++) {
        e[k] = d[k];
        f[k] = d[k];
   }
  
   start = clock();
   quicksort(d, 0, c-1);
   ende = clock();
   //if(c <100) printArray(d, c);
   printf("Quick-Sort: %.10f\n",
      (float)(ende-start) / (float)CLOCKS_PER_SEC);

    start = clock();
    insert(e, c);
    ende = clock();
    //if(c <100) printArray(e, c);
      printf("Insert Sort: %.10f\n",
      (float)(ende-start) / (float)CLOCKS_PER_SEC);

   start = clock();
   qsort(f, c, sizeof(int), cmpInteger);
   ende = clock();
   if(c <100) printArray(f, c);
   printf("qsort() %.10f\n",
      (float)(ende-start) / (float)CLOCKS_PER_SEC);


	if(in!=stdin)
	{
		fclose(in);
	}
	exit(EXIT_SUCCESS);
}

