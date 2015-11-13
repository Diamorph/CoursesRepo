#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
enum direct{UP = 2,DOWN};
int goDown = 0;
COORD diagonal(COORD pos, enum direct direction){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = 0;
	Position.Y = 0;
	while (1){
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, Color(pos.X, pos.Y));
		printf("*");
		if (goDown == 0){
			goDown = 1;
			SetConsoleCursorPosition(hConsole, Position);
		}

		SetConsoleCursorPosition(hConsole, pos);
		Sleep(5);
		if (direction == UP){
			if ((pos.X  == 79) || (pos.Y  == 0)) break;
			pos.X++;
			pos.Y--;
		}
		else if (direction == DOWN){
			if ((pos.X  == 0) || (pos.Y  == 24)) break;
			pos.X--;
			pos.Y++;
		}
	}
	return pos;
}
int Color(int x, int y){
	int colourcursor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int background, resultcolor;
 switch ( abs( x - y)% 12){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 9:
    case 10:
    case 11:
         background = BACKGROUND_GREEN;
     break;
    case 5:
    case 8:
        background = BACKGROUND_BLUE;
     break;
    case 6:
    case 7:
        background = BACKGROUND_BLUE | BACKGROUND_GREEN ;
     break;
 }
	resultcolor = colourcursor | background | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
	return resultcolor;
}
int main(void){
	int i;
	COORD pos;
	pos.X = 79;
	pos.Y = 24;
	for (i = 1; i <= 52; i++){
		pos = diagonal(pos,UP);
		if ((pos.X == 79) && (pos.Y != 0)){
			pos.Y--;
		}
		if (pos.Y == 0){
			pos.X--;
		}
		pos = diagonal(pos, DOWN);
		if ((pos.Y == 24) && (pos.X != 0)){
			pos.X--;
		}
		 if (pos.X == 0){
			pos.Y--;
		}
	}
	getchar();
	return EXIT_SUCCESS;
}
