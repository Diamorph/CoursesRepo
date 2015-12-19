#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include "head.h"

int main(void)
{
     int check =1;
    while (check)
    {
        system("cls");
        int i;
        char str[100];
        JumpTo(30,2);
        printf("Commands: ");
        JumpTo(30,3);
        printf("1. Add new student (add)");
        JumpTo(30,4);
        printf("2. List of students (students)");
        JumpTo(30,5);
        printf("3. Change student (change)");
        JumpTo(30,6);
        printf("4. Exit (exit)");
        enter();
        gets(str);
        if (strcmp(str, "students")==0)
        {
            Students();
        }
        else if (strcmp(str, "change")==0)
        {
            change();
        }
        else if (strcmp(str, "add")==0)
        {
            create();
        }
        else if (strcmp(str, "exit")==0)
        {
            check = 0;
        }
        else
        {
            system("cls");
            JumpTo(30,2);
            printf("ERROR, Wrong Command");
            JumpTo(0,20);
            system("pause");
        }
    }


    //start();
    return 0;
}
