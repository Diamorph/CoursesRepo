#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int main()
{
   char str1[300] = "jghw";
   char str2[300] = "qwer";
int a = strlen(str1);
   int arr[300];
   int i;
   if (strlen(str1)==strlen(str2)){
   for (i = 0; i < strlen(str1);i++){
   arr[i] = ((str1[i]+str2[i]) % 127);
   printf("%d ", arr[i]);
   }
   }else {
   puts("ERROR");
   }
    return 0;
   }

