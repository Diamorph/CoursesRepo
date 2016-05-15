#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct scientist_s* scientist_t;

scientist_t scientist_new(char* name, char* surname, int birthday);
void scientist_free(scientist_t self);

char* scientist_getKey(scientist_t self);
char* scientist_getValue(scientist_t self);
void scientist_insert(scientist_t self, HWND hWndList);


