#include "scientist.h"

struct scientist_s{
	char name[50];
	char surname[50];
	int birthday;
	char key[100];
	char value[100];
};

scientist_t scientist_new(char* name, char* surname, int birthday){
	scientist_t scientist = (scientist_t)malloc(sizeof(struct scientist_s));
	strcpy(scientist->name, name);
	strcpy(scientist->surname, surname);
	scientist->birthday = birthday;
	return scientist;
}

void scientist_free(scientist_t self){
	if (self) free(self);
}

char* scientist_getKey(scientist_t self){
	return self->surname;
}

char* scientist_getValue(scientist_t self){
	int count = sprintf(self->value, "%s %s, %d", self->surname, self->name, self->birthday);
	self->value[count] = '\0';
	return self->value;
}

void scientist_insert(scientist_t self, HWND hWndList){
	SendMessage(hWndList, LB_INSERTSTRING, 0, (LPARAM)scientist_getKey(self));
	SendMessage(hWndList, LB_SETITEMDATA, 0, (LPARAM)scientist_getValue(self));
}

