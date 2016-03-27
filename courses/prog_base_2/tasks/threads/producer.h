#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "mutex.h"
#include "thread.h"

#define array_size 4


typedef struct numbers_s{
	int position;
	int arr[array_size];
	mutex_t *mutex;
} numbers_t;

typedef struct producer_s* producer_t;

producer_t producer_new(numbers_t* numbers);
void producer_destructor(producer_t producer);
