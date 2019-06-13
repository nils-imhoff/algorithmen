#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXCOLS  256
#define MAXROWS  256




typedef struct labyrinth
{
   char lab[MAXCOLS+2][MAXROWS];
   long costs[MAXCOLS][MAXROWS];
   int maxrow;
   int maxcol;
   int startx;
   int starty;
   int treasurex;
   int treasurey;
}LabCell, *Lab_p;


void findLab(Lab_p lab)
{
   int i,j;
   bool start = false, treasure = false;

   lab->maxcol = 0;
   for(i=0; i< lab->maxrow; i++)
   {
      for(j=0; j<MAXCOLS; j++)
      {
         if((lab->lab[i][j]=='\n') && (j>lab->maxcol))
         {
            lab->maxcol = j;
         }
         
         if(lab->lab[i][j] == 'S')
         {
            if(start)
            {
               fprintf(stderr, "zuviele Starts\n");
               exit(EXIT_FAILURE);
            }
            lab->startx = i;
            lab->starty = j;
            start = true;
         }
         if(lab->lab[i][j] == 'X')
         {
            if(treasure)
            {
               fprintf(stderr, "zuviele Ziele \n");
               exit(EXIT_FAILURE);
            }
            lab->treasurex = i;
            lab->treasurey = j;
            treasure = true;
         }
      }
   }
   if(!start)
   {
      fprintf(stderr, "Kein Start\n");
      exit(EXIT_FAILURE);
   }
   if(!treasure)
   {
      fprintf(stderr, "Kein Ziel\n");
      exit(EXIT_FAILURE);
   }
}



Lab_p readLab(FILE* in)
{
   Lab_p handle = malloc(sizeof(LabCell));
   char  *inp;

   handle->maxrow = 0;

   while((inp=fgets(handle->lab[handle->maxrow], MAXCOLS, in)))
   {
      handle->maxrow++;
      if(handle->maxrow>MAXROWS)
      {
         fprintf(stderr, "\n");
         exit(EXIT_FAILURE);
      }
   }
   return handle;
}



void printLab(FILE* out, Lab_p lab)
{
   int i;

   for(i=0; i<lab->maxrow; i++)
   {
      fprintf(out, "%s", lab->lab[i]);
   }
}


long countLab(Lab_p lab, int move[], int x, int y, bool print)
{
   int i;
   int res;
   char current;

   if(print)
   {
      printLab(stdout, lab);
      printf("X: %d, Y: %d\n", x,y);
   }

   current = lab->lab[x][y];
   switch(current)
   {
   case '#': return 0;
   case '*': return 0;
   case '!': return 0;
   case 'X': return 1;
   default:
         break;
   }
   lab->lab[x][y] = '*';
   for(i=0; move[i] != 42; i=i+2)
   {  

      res = countLab(lab, move, x+move[i], y+move[i+1], print);
      if(res != 0)
      {
         return res+1;
      }
   }
   lab->lab[x][y] = '!';
   return 0;
}




int main(int argc, char *argv[])
{
   FILE *in = stdin;
   Lab_p lab;
   int move[10] = {0,1,0,-1,1,0,-1,0,42,42};
   int  cost;
   int   arg, args=argc,  farg;
   bool  print = false;

   for(arg = 1; arg<argc; arg++)
   {
      if(strcmp(argv[arg], "-p")==0)
      {
        print = true;
         args--;
      }
      else
      {
         farg = arg;
      }
   }

   if(args > 2)
   {
      fprintf(stderr, "Usage: %s [-a] [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if(args == 2)
   {
      in = fopen(argv[farg], "r");
      if(!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }
   lab = readLab(in);
   findLab(lab);
   cost = countLab(lab, move, lab->startx, lab->starty, print) -1;
   if(cost==0)
   {
      printLab(stdout, lab);
      fprintf(stdout, "Kein Weg \n");
   }
   else
   {
      printLab(stdout, lab);
      printf("Kosten: %d\n", cost);
   }
   exit(EXIT_SUCCESS);
}
