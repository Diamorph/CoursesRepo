
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "scientists.h"

typedef struct list_s list_t;

list_t * list_new();
void list_free(list_t * self);
void list_add(list_t * self,scientist_t * scientist);
scientist_t * list_getByID(list_t * self,int index);
int list_getSize(list_t * self);

