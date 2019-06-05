#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX  256


typedef struct lin_list
{
   char            *payload;
   struct lin_list *next;    
}ListCell, *List_P;





List_P allocCell(char* payload)
{
   List_P cell = malloc(sizeof(ListCell));
   
   cell->payload = strdup(payload);
   cell->next    = NULL;

   return cell;
}



void freeCell(List_P junk)
{
   free(junk->payload);
   free(junk);
}




void freeList(List_P *junk)
{
   if(*junk)
   {
      freeList(&(*junk)->next);
      freeCell(*junk);
      *junk = NULL;
   }
}






List_P insertFirst(List_P *anchor, List_P newcell)
{
   newcell->next = *anchor;
   *anchor = newcell;

   return newcell;
}



List_P extractFirst(List_P *anchor)
{
   List_P res = *anchor;
   
   if(res)
   {
      *anchor = res->next;
      res->next = NULL;
   }
   return res;
}

List_P extractLast(List_P *anchor)
{
   List_P h;
   
   if(!*anchor)
   {
      return NULL;
   }
   while((*anchor)->next)
   {
      anchor = &((*anchor)->next);
   }
   h = *anchor;
   *anchor = NULL;
   return h;
}



List_P inserLast(List_P *anchor, List_P cell)
{
   List_P h = *anchor;
   
   while(*anchor)
   {
      anchor = &((*anchor)->next);
   }
   *anchor = cell;

   return h;
}



List_P listFind(List_P list, char *payload)
{
   while(list)
   {
      if(strcmp(list->payload, payload)==0)
      {
         return list;
      }
      list = list->next;
   }
   return NULL;
}



List_P revertList(List_P *anchor)
{
   List_P l=NULL, h;

   while(*anchor)
   {
      h = extractFirst(anchor);
      insertFirst(&l, h);
   }
   *anchor =l;
   return l;
}



void printList(FILE* out, List_P list)
{
   while(list)
   {
      fprintf(out, "%s", list->payload);
      list = list->next;
   }
}



List_P sortList(List_P list)
{
   List_P l1 = NULL, l2 = NULL, h;
   
   if(!list ||  !list->next)
   {
      return list;
   }
   while(list)
   {
      h = extractFirst(&list);
      insertFirst(&l1, h);
      if(!list)
      {
         break;
      }
      h = extractFirst(&list);
      insertFirst(&l2, h);
   }
   l1 = sortList(l1);
   l2 = sortList(l2);
   
   while(l1 || l2)
   {
      if(!l2)
      {
         h = extractFirst(&l1);
      }
      else if(!l1)
      {
         h = extractFirst(&l2);
      }
      else if(strcmp(l1->payload, l2->payload)<0)
      {
         h = extractFirst(&l1);
      }
      else
      {
         h = extractFirst(&l2);
      }
      insertFirst(&list, h);
   }
   revertList(&list);
   return list;
}

void printCount(FILE* out, List_P list)
{
   char *current;
   int  count;

   while(list)
   {
      count = 1;
      current = list->payload;
      while(list->next && (strcmp(current, list->next->payload)==0))
      {
         count++;
         list = list->next;
      }     
      fprintf(out, "%2d %s", count, current);
      list = list->next;
   }
}

void lastList(List_P *anchor)
{
   List_P  h;
   List_P l = NULL;

   while(*anchor)
   {
      h = extractLast(anchor);

      printf("extract %s", h->payload);
      h->next = NULL;
      inserLast(&l, h);
   }   
   printList(stdout, l);
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   char line [MAX];
   List_P l1 = NULL, h;
   char* inp; 
   
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
   while((inp = fgets(line, MAX, in)))
   {
         h = allocCell(line);
         insertFirst(&l1, h);
   }
   //revertList(&l1);
   printf("Output:\n=======\n");
   printList(stdout, l1);

  /* 
  printf("Test: \n=====\n");
  lastList(&l1); 
   */

   printf("Sort: \n======\n");
   l1 = sortList(l1);
   printList(stdout, l1);

   printf("Output:\n=======\n");

   printCount(stdout, l1);

   freeList(&l1);

   if(in!=stdin)
   {
      fclose(in);
   }
   
   exit(EXIT_SUCCESS);
}


