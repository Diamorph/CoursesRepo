#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <windows.h>

struct Start
{
    char nameSt[100];
};

struct Founder
{
    char name[100];
    char surname[100];
    char age[20];
    char money[20];
    struct Start * pStart;
};

void createFounder(struct Founder *pVar,struct Start *pSVar ){
    puts("Type name of founder");
    fflush(stdin);
    gets(pVar->name);
    puts("Type surname of founder");
    fflush(stdin);
    gets(pVar->surname);
    puts("Type age of founder");
    fflush(stdin);
    gets(pVar->age);
    puts("Type money of founder");
    fflush(stdin);
    //scanf("%d",pVar->money);
    gets(pVar->money);
    puts("Type name of startup");
    fflush(stdin);
    gets(pSVar->nameSt);
}

void printFounder(struct Founder *pVar,struct Start *pSVar)
{
printf("\n%s %s %s %s Startup: %s",pVar->name,pVar->surname,pVar->age,pVar->money,pSVar->nameSt);
}

int main(void)
{
    int i = 0;
    struct Founder founder[2];
    struct Start start[2];
    for (i = 0; i < 2; i++){
        printf("Founder %d \n",i+1);
    createFounder(&founder[i],&start[i]);
   }
   for (i = 0; i < 2; i++){
        printf("\n Founder %d \n",i+1);
    printFounder(&founder[i],&start[i]);
   }

   getch();
    return 0;
}
