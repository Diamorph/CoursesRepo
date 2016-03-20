#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void(*checkCallback)(char* Str, char* extraStr, int index);

void containsCB(char* Str, char* extraStr, int index);

void reversedCB(char* Str, char* extraStr, int index);

static void reverseString(char* string){
	int lenght = strlen(string);
	for (int i = 0; i < lenght / 2; i++){
		char temp = string[i];
		string[i] = string[lenght - 1 - i];
		string[lenght - 1 - i] = temp;
	}
}

void containsCB(char* Str, char* extraStr, int index){
    printf(">> %d\n", index);
}


void reversedCB(char* Str, char* extraStr, int index){
    printf(">> %d\n", index);
}


int check(char* Str, char* extraStr, checkCallback containsCB, checkCallback reversedCB){
    char* flag;
	int index = 0;
	if (NULL == containsCB || NULL == reversedCB)
    {
        return -1;
    }
	printf("Main String: %s\n", Str);
	printf("Extra String: %s\n", extraStr);
	reverseString(extraStr);
	printf("Reverse Extra Srting: %s\n", extraStr);
	reverseString(extraStr);
	printf("\n");
	printf("\nIndex of containsCB :\n");
	while ((flag = strstr(Str + index, extraStr)) != NULL){
		index = flag - Str;
		containsCB(Str, extraStr, index++);
	}
	printf("\n");
	printf("\nIndex of reverseCB :\n");
	reverseString(extraStr);
	index = 0;
	while ((flag = strstr(Str + index, extraStr)) != NULL){
		index = flag - Str;
		reversedCB(Str, extraStr, index++);
	}
	return 0;
}

int main(void){
char bigStr[] = "12abcd21abcd12abcd21";
	char smallStr[] = "12";
	check(bigStr, smallStr, containsCB, reversedCB);
    system("pause");
	return 0;
}
