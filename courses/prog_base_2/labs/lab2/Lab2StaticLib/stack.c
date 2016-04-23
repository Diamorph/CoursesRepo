#include "stack.h"
struct stack_s{
	char* strings[MAX_STACK_SIZE];
	int count;
};

stack_t stack_new(void){
	stack_t stack = (stack_t)malloc(sizeof(struct stack_s));
	stack->count = 0;
	return stack;
}
void stack_free(stack_t self){
	for (int i = 0; i<self->count; i++){
		free(self->strings[i]);
	}
	free(self);
}

int stack_getCount(stack_t self){
	return self->count;
}

void stack_push(stack_t self, char* val){
	if (self->count >= MAX_STACK_SIZE) return;
	self->strings[self->count] = (char*)malloc(MAX_STRING_SIZE*sizeof(char));
	strcpy(self->strings[self->count++], val);
}

static void strClean(char* str){
	int length = strlen(str);
	for (int i = length - 1; i >= 0; i--){
		str[i] = '\0';
	}
}

char* stack_pop(stack_t self){
	if (self->count == 0) return;
	static char popValue[MAX_STRING_SIZE];
	strClean(popValue);
	strcpy(popValue, self->strings[self->count - 1]);
	free(self->strings[self->count - 1]);
	self->count--;
	return popValue;
}

char* stack_peek(stack_t self){
	if (self->count == 0) return NULL;
	static char peekValue[MAX_STRING_SIZE];
	strClean(peekValue);
	strcpy(peekValue, self->strings[self->count - 1]);
	return peekValue;
}

void stack_print(stack_t self){
	for (int i = self->count - 1; i >= 0; i--){
		printf("%s\n", self->strings[i]);
	}
}
