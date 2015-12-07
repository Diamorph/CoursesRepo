#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define SIDE_SIZE 8
#define SIDE_SIZE1 79
void Color();
void JumpTo(int x, int y);
void Enterstring();
void Getcmd(char* cmd);

void JumpTo(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

void Color(){
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int fmt = BACKGROUND_GREEN;
    SetConsoleTextAttribute(hConsole, fmt);
     int i, j;
    /* top */
    for ( i = 0; i < SIDE_SIZE1; i++ )
        putchar('  ');
    putchar('\n');
    /* middle */
    for ( i = 0; i < SIDE_SIZE - 2; i++ ){
        putchar('  ');
        for ( j = 0; j < SIDE_SIZE1 - 2; j++ )
            putchar('  ');
        putchar('  ');
        putchar('\n');
    }
    /* bottom */
    for ( i = 0; i < SIDE_SIZE1; i++ )
        putchar('  ');
    putchar('\n');
}

void start(char *str, char* cmd){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    JumpTo(30,1);
    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
    printf("Enter your string:\n");
    JumpTo(30,2);
    gets(str);
    JumpTo(30,1);
    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
    puts("                                                                            ");
    JumpTo(30,1);
    printf("Your string:\n");
    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
    JumpTo(30,2);
    puts(str);
    JumpTo(0,9);
    SetConsoleTextAttribute(hConsole,7);
    printf("Enter your command:\n");
    //getcmd(cmd);
}

void Cleanhelp(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
for (int i = 1; i<=12; i++){
    JumpTo(0, 10+i);
    SetConsoleTextAttribute(hConsole,7);
    puts ("                                                                                                       ");
}
}

void CleanCons(){
JumpTo(0,10);
puts("                                                                                ");
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
JumpTo(30,3);
puts("                                      ");
JumpTo(30,4);
puts("                                      ");
JumpTo(30,5);
puts("                                      ");
JumpTo(30,6);
puts("                                      ");
JumpTo(30,7);
puts("                                      ");
JumpTo(30,3);
}
