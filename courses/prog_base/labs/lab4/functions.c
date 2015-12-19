#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include "head.h"

void JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

void readFile(int n, struct student Student[n])
{
    int i;
    FILE *input = fopen("students.txt", "r");
    char str[100];
    fgets(str, 100, input);
    n = str[0] - '0';
    for (i = 0; i < n; i++)
    {
        fgets(str, 100, input);
        strcpy(Student[i].name, str);

        fgets(str, 100, input);
        strcpy(Student[i].surname, str);

        fgets(str, 100, input);
        strcpy(Student[i].group, str);

        fgets(str, 100, input);
        Student[i].mark1 = str[0] - '0';

        fgets(str, 100, input);
        Student[i].mark2 = str[0] - '0';

        fgets(str, 100, input);
        Student[i].mark3 = str[0] - '0';

        fgets(str, 100, input);
        Student[i].mark4 = str[0] - '0';

        fgets(str, 100, input);
        Student[i].mark5 = str[0] - '0';
    }
    fclose(input);
}
int getN()
{
    FILE *input = fopen("students.txt", "r");
    char str[100];
    int n,i;
    fgets(str, 100, input);
    for(i  = strlen(str) - 1;i >= 0;i--)
    {
        n += str[i]*pow(10,strlen(str)-i-1);
    }
    n = str[0] - '0';
    fclose(input);
    return n;
}

void saveFile(int n, struct student Student[n])
{
    FILE *output = fopen("students.txt", "w");
    char str[100];
    int i;
    fprintf(output, "%i\n", n);
    for (i = 0; i < n; i++)
    {
        if (Student[i].name[ strlen(Student[i].name) - 1 ]=='\n')
            fprintf(output, "%s", Student[i].name);
        else
            fprintf(output, "%s\n", Student[i].name);

             if (Student[i].surname[ strlen(Student[i].surname) - 1 ]=='\n')
            fprintf(output, "%s", Student[i].surname);
        else
            fprintf(output, "%s\n", Student[i].surname);

        if (Student[i].group[ strlen(Student[i].group)-1 ]=='\n')
            fprintf(output, "%s", Student[i].group);
        else
            fprintf(output, "%s\n", Student[i].group);


        fprintf(output, "%i\n", Student[i].mark1);
        fprintf(output, "%i\n", Student[i].mark2);
        fprintf(output, "%i\n", Student[i].mark3);
        fprintf(output, "%i\n", Student[i].mark4);
        fprintf(output, "%i\n", Student[i].mark5);
    }
    fclose(output);
        }

void Students()
{
    system("cls");
    int n = getN();
    struct student Student[n];
    readFile(n, Student);
    double rating;
    JumpTo(0,0);
    printf("Students:");
    JumpTo(1,2);
    int i;
    for (i = 0; i < n; i++)
    {
        rating = (Student[i].mark1 + Student[i].mark2 + Student[i].mark3 + Student[i].mark4 + Student[i].mark5)/5;
        printf("ID : %i \nSurname: %s", i+1, Student[i].surname);
        printf("Name: %s", Student[i].name);
        printf("Group: %s", Student[i].group);
        printf(" Ukrainian language: %i \n Linear algebra: %i \n Mathematical Analysis: %i \n Computer Discrete Mathematics :%i \n Fundamentals of Programming :%i " , Student[i].mark1, Student[i].mark2, Student[i].mark3, Student[i].mark4, Student[i].mark5);
     if (Student[i].mark1 < 3 || Student[i].mark2 < 3 || Student[i].mark3 < 3 || Student[i].mark4 < 3 || Student[i].mark5 < 3){
        printf("\n kick out");
      }else if (rating >= 3 && rating < 4){
      printf("\n no scholarship");
      } else if (rating >= 4 && rating < 5){
                printf("\n scholarship");
      }else if  (rating == 5){
                printf("\n bigger scholarship");
      }
           printf("\n");
    }
    printf("\n");
    system("pause");
}
void enter()
{
    JumpTo(40,0);
    printf("Enter: ");
}
void changeStudent(struct student *s)
{
    int check =0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
    while(check == 0)
    {
        system("cls");
        JumpTo(0,1);
        printf("Name: %s", s->name);
        JumpTo(0,2);
        printf("Surname: %s", s->surname);
        JumpTo(0,3);
        printf("Group: %s", s->group);
        JumpTo(0,4);
        printf("Ukrainian language: %i\n", s->mark1);
        printf("Linear algebra: %i\n", s->mark2);
        printf("Mathematical Analysis: %i\n", s->mark3);
        printf("Computer Discrete Mathematics: %i\n", s->mark4);
        printf("Fundamentals of Programming: %i\n", s->mark5);
        JumpTo(10,13);
        printf("Edit: \n name \n surname \n group \n Ukrainian language(mark1) \n Linear algebra(mark2) \n Mathematical Analysis(mark3) \n Computer Discrete Mathematics(mark4) \n Fundamentals of Programming(mark5) \n Exit");
        enter();
        char str[100];
        gets(str);
        if (strcmp(str, "name")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("New name: ");
            gets(str);
            strcpy(s->name, str);
        }
         else if (strcmp(str, "surname")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("New surname: ");
            gets(str);
            strcpy(s->surname, str);
        }
        else if (strcmp(str, "group")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("New group: ");
            gets(str);
            strcpy(s->group, str);
        }
        else if (strcmp(str, "mark1")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("Ukrainian language: ");
            gets(str);
            if ((str[0]-'0'<=5) && (str[0]-'0'>=1) && (strlen(str) == 1))
                s->mark1 = str[0]- '0';
        }
        else if (strcmp(str, "mark2")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("Linear algebra: ");
            gets(str);
            if ((str[0]-'0'<=5) && (str[0]-'0'>=1) && (strlen(str)==1))
                s->mark2= str[0]- '0';
        }
        else if (strcmp(str, "mark3")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("Mathematical Analysis: ");
            gets(str);
            if ((str[0]-'0'<=5) && (str[0]-'0'>=1) && (strlen(str)==1))
                s->mark3= str[0]- '0';
        }
         else if (strcmp(str, "mark4")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("Computer Discrete Mathematics: ");
            gets(str);
            if ((str[0]-'0'<=5) && (str[0]-'0'>=1) && (strlen(str)==1))
                s->mark4 = str[0]- '0';
        }
         else if (strcmp(str, "mark5")==0)
        {
            check = 1;
            system("cls");
            JumpTo(20,10);
            printf("Fundamentals of Programming: ");
            gets(str);
            if ((str[0]-'0'<=5) && (str[0]-'0'>=1) && (strlen(str)==1))
                s->mark5= str[0]- '0';
        }
        else if (strcmp(str, "exit")==0)
        {
            check = 1;
        }
        else{}
    }
        system("cls");
        JumpTo(0,1);
        printf("Name: %s", s->name);
        JumpTo(0,2);
        printf("Surname: %s", s->surname);
         JumpTo(0,3);
        printf("Group: %s", s->group);
         JumpTo(0,4);
        printf("Ukrainian language: %i\n", s->mark1);
        printf("Linear algebra: %i\n", s->mark2);
        printf("Mathematical Analysis: %i\n", s->mark3);
        printf("Computer Discrete Mathematics: %i\n", s->mark4);
        printf("Fundamentals of Programming: %i\n", s->mark5);
         JumpTo(10,13);
        system("pause");

}
void change()
{

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int n;
    char str[100];
    while(1)
    {
        system("cls");
         JumpTo(30,10);
        if (getN()==1)
            printf("There is only 1 student. Confirm(1)");
        else
            printf("Please, choose student's id(1-%i)", getN());
        enter();
        gets(str);
        n = str[0] -'0';
        if (strlen(str)>1)          // если число имеет больше 1 цифры
            continue;
        if ((n >= 1) && (n <= getN()))
            break;
    }
    struct student Student[getN()];
    readFile(getN(), Student);
    changeStudent(&Student[n-1]);
    saveFile(getN(), Student);
}
void createStudent(struct student *Student)
{
    system("cls");
    JumpTo(30,10);
    char str = (char*)malloc(100*sizeof(char));

    int n;
    printf("Name: ");
    gets(str);
    strcpy(Student->name, str);
    system("cls");
    printf("Surname: ");
    gets(str);
    strcpy(Student->surname, str);

    system("cls");
    JumpTo(30,10);
    printf("Group: ");
    gets(str);
    strcpy(Student->group, str);


    n = 0;

    while((n < 1) || (n > 5))
    {
        system("cls");
        JumpTo(30,10);
        printf("Ukrainian language:");
        gets(str);
        if (strlen(str)!=1)
            continue;
        n = str-'0';
    }
    Student->mark1 = str - '0';

    n = 0;

    while((n < 1) || (n > 5))
    {
        system("cls");
        JumpTo(30,10);
        printf("Linear algebra: ");
        gets(str);
        if (strlen(str) != 1)
            continue;
        n = str -'0';
    }
    Student->mark2 = str - '0';
    n = 0;

    while(( n < 1) || (n > 5))
    {
        system("cls");
        JumpTo(30,10);
        printf("Mathematical Analysis: ");
        gets(str);
        if (strlen(str)!= 1)
            continue;
        n = str - '0';
    }
    Student->mark3 = str-'0';
    n = 0;


     while(( n < 1) || (n > 5))
    {
        system("cls");
        JumpTo(30,10);
        printf("Computer Discrete Mathematics: ");
        gets(str);
        if (strlen(str)!=1)
            continue;
        n = str -'0';
    }
    Student->mark4 = str-'0';
    n = 0;

     while(( n < 1) || (n > 5))
    {
        system("cls");
        JumpTo(30,10);
        printf("Fundamentals of Programming: ");
        gets(str);
        if (strlen(str)!=1)
            continue;
        n = str -'0';
    }
    Student->mark5 = str-'0';
}
void create()
{
    struct student s[getN()+1];
    readFile(getN(), s);
    createStudent(&s[getN()]);
    system("cls");
    JumpTo(0,0);
    printf("Name:\n%\nSurname:\n%s\nGroup: %s\n",s[getN()].name, s[getN()].surname, s[getN()].group);
    printf("Ukrainian language: %i. Linear algebra: %i. Mathematical Analysis: %i. Computer Discrete Mathematics: %i. Fundamentals of Programming: %i. \n", s[getN()].mark1, s[getN()].mark2, s[getN()].mark3, s[getN()].mark4, s[getN()].mark5);
    system("pause");
    saveFile(getN()+1, s);
}
void start()
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
        printf("4. Exit(exit)");
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
}
