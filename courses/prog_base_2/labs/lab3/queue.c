#include "queue.h"

struct queue_s{
	int queue[MAX_SIZE];
	int size;
};

queue_t queue_new(void){
	queue_t queue = malloc(sizeof(struct queue_s));
	queue->size = 0;
	return queue;
}

void queue_delete(queue_t self){
	free(self);
}

int queue_add(queue_t self, int elem){
	if (self->size == MAX_SIZE){
		return queue_error;
	}
	self->queue[self->size++] = elem;
	return 1;
}

int queue_remove(queue_t self){
	if (self->size == 0){
		return 0;
	}
	int res = self->queue[0];
	for (int i = 0; i < self->size - 1; i++){
		self->queue[i] = self->queue[i + 1];
	}
	self->size--;
	return res;
}

int queue_peek(queue_t self){
	return (self->size)? self->queue[0] : 0;
}

int queue_getSize(queue_t self){
	return self->size;
}

int queue_isEmpty(queue_t self){
	return (self->size == 0);
}

int queue_deleteTail(queue_t self){
	if (queue_isEmpty(self)) return 0;
	int res = self->queue[self->size - 1];
	self->size--;
	return res;
}

