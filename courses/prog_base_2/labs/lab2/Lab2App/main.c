#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "stack.h"

typedef struct dynamic_s {
    HANDLE hLib;
    check_f check;
    reaction_f reaction;
} dynamic_t;

const char * userChoice();
dynamic_t * dynamic_init(const char * dllName);

int main(void) {
    stack_t stack = stack_new();
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->check) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->reaction) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");


    while (1){
        char input[50];
		gets(input);
		if (dll->check(stack, input)){
            dll->reaction(stack, input);
            continue;
		}
		char cmd[50];
		char value[50];
        sscanf(input, "%s", cmd);
        if (strcmp(cmd, "pop") == 0){
            printf("Pop: %s\n", stack_pop(stack));
        }
        else if (strcmp(cmd, "count") == 0){
            printf("count: %d\n", stack_getCount(stack));
        }
		else if (strcmp(input, "exit") == 0 ) return 0;
		else if (strlen(input)>0){
            sscanf(input, "%s", value);
            stack_push(stack, value);
            printf("Push: %s\n", value);
		}
		fflush(stdin);
	}
    return 0;
}

const char * userChoice(void) {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        fflush(stdin);
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n >>> ");
        scanf("%i", &dllNum);
        fflush(stdin);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->check = NULL;
    dyn->reaction = NULL;
    if (NULL != dyn->hLib) {
        dyn->check = (check_f)GetProcAddress(dyn->hLib, "check");
        dyn->reaction = (reaction_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}
