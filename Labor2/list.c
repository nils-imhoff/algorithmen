#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX  256


typedef struct lin_list
{
   char            *payload; 
   struct lin_list *next;    
}LinListCell, *LinList_p;


LinList_p LinListAllocCell(char* payload)
{
   LinList_p cell = malloc(sizeof(LinListCell));

   cell->payload = strdup(payload);
   cell->next    = NULL;

   return cell;
}


void LinListFreeCell(LinList_p junk)
{
   free(junk->payload);
   free(junk);
}


void LinListFree(LinList_p *junk)
{
   if(*junk)
   {
      LinListFree(&(*junk)->next);
      LinListFreeCell(*junk);
      *junk = NULL;
   }
}




LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell)
{
   newcell->next = *anchor;
   *anchor = newcell;

   return newcell;
}



LinList_p LinListExtractFirst(LinList_p *anchor)
{
   LinList_p res = *anchor;

   if(res)
   {
      *anchor = res->next;
      res->next = NULL;
   }
   return res;
}



void Revert(LinList_p *anchor)
{
   LinList_p newlist = NULL, handle;

   while(*anchor)
   {
      handle = LinListExtractFirst(anchor);
      LinListInsertFirst(&newlist, handle);
   }
   *anchor = newlist;
}




void Print(FILE* out, LinList_p list)
{
   while(list)
   {
      fprintf(out, "%s", list->payload);
      list = list->next;
   }
}


int main(int argc, char *argv[])
{
   FILE *in = stdin;
   char line[MAX];
   LinList_p list = NULL, handle;
   char* inp;

   if(argc > 2)
   {
      fprintf(stderr, "\n", argv[0]);
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
   while((inp = fgets(line, MAX, in)))
   {
      handle = LinListAllocCell(line);
      LinListInsertFirst(&list, handle);
   }

   fprintf(stdout, "Umgekehrt\n=============\n");
   Print(stdout, list);

   Revert(&list);

   fprintf(stdout, "Liste\n==============\n");
   Print(stdout, list);

   LinListFree(&list);

   if(in!=stdin)
   {
      fclose(in);
   }

   exit(EXIT_SUCCESS);
}

