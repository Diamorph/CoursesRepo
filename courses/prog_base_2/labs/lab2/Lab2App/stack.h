#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 50
#define MAX_STRING_SIZE 300
typedef struct stack_s* stack_t;

typedef int(*check_cb)(stack_t self, char* input);
typedef void(*reaction_cb)(stack_t self, char* input);

stack_t stack_new(void);
void stack_free(stack_t self);

int stack_getCount(stack_t self);

void stack_push(stack_t self, char* val);
char* stack_pop(stack_t self);

char* stack_peek(stack_t self);

void stack_print(stack_t self);

