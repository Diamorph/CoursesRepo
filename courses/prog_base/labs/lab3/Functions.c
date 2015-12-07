#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int WordCount(char  str[])           // КІЛЬКІСТЬ СЛІВ В СТРОКІ
{
    Cleanhelp();
    CleanCons();
    int space=0;
    for (int i = 1; i<= strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            space++;
        }
    }
    return space+1;
}

int dovg(char str[]){               // ДОВЖИНА СТРОКИ
    Cleanhelp();
    CleanCons();
return strlen(str);
}

void extrastr(char* str, char* extra){
     Cleanhelp();
     CleanCons();
     JumpTo(30,3);
     printf("Enter your ExtraStr:\n");
     JumpTo(30,4);
     gets(extra);
     int ext = numOfEntry(str, extra);
     JumpTo(30,5);
     printf("count =  %d\n", ext);
}
int numOfEntry(char* str, char* extra){                     //ВИВЕСТИ К-СТЬ ВХОДЖЕННЬ РОБОЧОЇ СТРОКИ У ВВЕДЕНУ
	int res = 0, pointer = 0;
	while (strstr(str + pointer, extra) != NULL){
		res++;
		pointer = (strstr(str + pointer, extra) + strlen(extra)) - str;
	}
	return res;
}
void deletestr(char str[]){
    Cleanhelp();
    CleanCons();
int i = 0;
for (i = 0; i < strlen(str); i ++){
    str[i] = 0;
}
    JumpTo(30,2);
    puts("                    ");
}

void DeleteSpaces(char str[], char extra[]){
    Cleanhelp();
    CleanCons();
    int i, j;
    for(i = j = 0; str[i] != '\0'; i++)
        if(str[i] != ' ')
            extra[j++] = str[i];
    extra[j] = '\0';
    for (i = 0 ; extra[i] != '\0'; i++){
        str[i] = extra[i];
    }
    JumpTo(30,2);
    puts("                    ");
    JumpTo(30,2);
    puts(str);
}


void flipViceVersa(char* str){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
    Cleanhelp();
    CleanCons();
	char t;
	for (int i = 0; i < strlen(str) / 2 ; i++){
		t = str[i];
		str[i] = str[strlen(str) - i - 1];
		str[strlen(str) - i - 1] = t;
	}
	JumpTo(30,2);
	puts(str);
}

void LongestWord(char str[]){
    Cleanhelp();
    CleanCons();
   char * pch = strtok (str," "),  // получаем первое слово
         * word = 0; // самое длинное слово

    int length = strlen(pch);          // определяем длинну первого слова

    int maxLen = 0; // самое длинное слово

      while (pch != NULL)                         // пока есть слова
      {
          length = strlen(pch);        // определяем длинну слова

          if (maxLen < length )        // определяем самое длинное слово
          {
              maxLen = length;
              word = pch;              // сохраняем указатель на текущее слово
          }

          pch = strtok (NULL, " "); // получаем следующее слово
      }
      printf ( "Longest Word is : %s\n",word);
      JumpTo(30,4);
      printf ( "lenght = %d\n", maxLen );
}

void Random(char str[]){
    Cleanhelp();
    CleanCons();
	srand((unsigned)time(NULL));
	for (int i = 0; i < strlen(str); i++){
		str[i] = rand() % 94 + 33;
	}
	JumpTo(30,2);
	puts("                                          ");
	JumpTo(30,2);
	puts(str);
}

void NewStr(char str[]){
Cleanhelp();
CleanCons();
printf("Enter new string:\n");
JumpTo(30,4);
gets(str);
JumpTo(30,2);
puts("                                                                                                            ");
JumpTo(30,2);
puts(str);
JumpTo(30,3);
puts("                  ");
JumpTo(30,4);
puts("                                                                                                                                            ");
}

void words(char str[]){
char* ptr;
int i;
ptr = strtok(str, " ");
    while(ptr!= NULL);
     for ( i = 0; i < strlen(ptr); ++i){
        printf("%s \n", ptr);
                break;
     }
     ptr = strtok(NULL, " ");
}
void getWords(char* string, char* words[], int* wNum){
	static char copy[1000];
	int word = 1;
	strcpy(copy, string);
	for (int i = 0; i < strlen(string); i++){
		if (!(((copy[i] >= 65) && (copy[i] <= 90)) || ((copy[i] >= 97) && (copy[i] <= 122))))
			copy[i] = '*';
	}
	words[0] = strtok(copy, "*");

	while (words[word - 1] != NULL)
	{
		words[word] = strtok(NULL, "*");
		word++;
	}
	*wNum = word - 1;
}

int letters(char* str){
    Cleanhelp();
    CleanCons();
	int res = 0;
	for (int i = 0; i < strlen(str); i++){
		if (isalpha(str[i])) res++;
	}
	return res;
}
void Exit(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    for(int i=0; i<80; i++)
        for(int j=0; j<35; j++)
        {
            JumpTo(i,j);
            SetConsoleTextAttribute(hConsole,7);
            printf(" ");
        }
}

void getcmd(char cmd[]){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
JumpTo(0,10);
gets(cmd);
}

double doublepower(char* str, double power){
char * ptr;
double d1 = 0;
d1 = strtod(str, &ptr);
double result = pow(d1, power);
return result;
}
