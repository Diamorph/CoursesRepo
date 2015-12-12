#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <windows.h>
//did not have time
/*void open(){
FILE * fp;
fp = fopen ("input.txt" , "r");
if (fp == NULL) perror ("Error opening file");
FILE * f;
f = fopen ("output.txt" , "r+w");
if (f == NULL) perror ("Error opening file");
}

void calculate(FILE * fp){
double sum = 0;
   char *estr;
   char *ptr;
   char str [100];
   while (1)
   {
estr = fgets (str,sizeof(str),fp);
      if (estr == NULL)
      {
         if ( feof (fp) != 0)
         {
            break;
         }
         else
         {
            printf ("\nError reading from file\n");
            break;
         }
      }
      printf ("    %s",str);
      ptr= strtok(str, " ");
while (ptr!= 0)
{
if (atof(ptr)!= 0 && atof(ptr) > 3 ){
    sum+= atof(ptr);
}
ptr = strtok(NULL, " ");
}
   }
    printf("%f",sum);
}

void add(FILE * fp,FILE * f){
    fprintf(f, "%f", sum);
    fclose (f);
    fclose (fp);
}*/
//did not have time

int main(void)
{
   FILE *f;
   FILE * fp;
   double sum = 0;
   char *estr;
   char *ptr;
   char str [100];
   f = fopen ("output.txt" , "r+w");
   if (f == NULL) perror ("Error opening file");
   fp = fopen ("input.txt" , "r");
   if (fp == NULL) perror ("Error opening file");
while (1)
   {
estr = fgets (str,sizeof(str),fp);
      if (estr == NULL)
      {
         if ( feof (fp) != 0)
         {
            break;
         }
         else
         {
            printf ("\nError reading from file\n");
            break;
         }
      }
      printf ("    %s",str);
      ptr= strtok(str, " ");
while (ptr!= 0)
{
if (atof(ptr)!= 0 && atof(ptr) > 3 ){
    sum+= atof(ptr);
}
ptr = strtok(NULL, " ");
}
   }
    printf("%f",sum);
    fprintf(f, "%f", sum);
    fclose (f);
    fclose (fp);
    return 0;
}
