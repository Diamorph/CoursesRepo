#include "producer.h"

struct producer_s{
	thread_t* thread;
};

void * producerFunc(void* args){
	numbers_t * numbers = (numbers_t *)args;
	while (1){
		mutex_lock(numbers->mutex);
		numbers->arr[(numbers->position)++] = rand() % 10;
		if (numbers->position == 4){
            numbers->position = 0;
		}
		mutex_unlock(numbers->mutex);
	}
	return NULL;
}

producer_t producer_create(numbers_t* numbers){
	producer_t producer = (producer_t)malloc(sizeof(struct producer_s));
	producer->thread = thread_create_args(producerFunc, numbers);
	return producer;
}

void producer_destructor(producer_t producer){
	thread_free(producer->thread);
	free(producer);
}
