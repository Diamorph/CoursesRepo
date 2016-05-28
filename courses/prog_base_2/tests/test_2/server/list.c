#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "scientists.h"
#define MAX_ARRAY_SIZE 100

struct list_s {
scientist_t * arr[MAX_ARRAY_SIZE];
int size;
};

list_t * list_new()
{
list_t * self = malloc(sizeof(struct list_s));
self->size = 0;
return self;
}

void list_add(list_t * self,scientist_t * scientist){
self->arr[self->size] = scientist;
self->size++;
}
/*void list_free(list_t * self)
{
for (int i = 0; i < self->size; i++){
scientist_free(self->arr[i]);
}
}*/

scientist_t * list_getByID(list_t * self,int index)
{
return self->arr[index];
}
int list_getSize(list_t * self)
{
return self->size;
}
