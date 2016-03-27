#include "consumer.h"


struct consumer_s{
	thread_t* thread;
};

void * consumerFunc(void* args){
	numbers_t *numbers = (numbers_t *)args;
	while (1){
		mutex_lock(numbers->mutex);
		if (numbers->arr[3] == numbers->arr[2] + 1 && numbers->arr[2] == numbers->arr[1] + 1 && numbers->arr[1] == numbers->arr[0] + 1){
			    printf("\n Array:");
			    printf(" [ ");
			for (int i = 0; i < array_size; i++){
				printf("%d ", numbers->arr[i]);
			}
			printf("]");
		}
		mutex_unlock(numbers->mutex);
	}
	return NULL;
}

consumer_t consumer_create(numbers_t* numbers){
	consumer_t consumer = (consumer_t)malloc(sizeof(struct consumer_s));
	consumer->thread = thread_create_args(consumerFunc, numbers);
	return consumer;
}

void consumer_destructor(consumer_t consumer){
	thread_free(consumer->thread);
	free(consumer);
}

void consumer_join(consumer_t consumer){
	thread_join(consumer->thread);
}

numbers_t* numbers_create(void){
	numbers_t* numbers = (numbers_t*)malloc(sizeof(struct numbers_s));
	numbers->position = 0;
	numbers->mutex = mutex_new();
	return numbers;
}

void numbers_destructor(numbers_t* numbers){
	mutex_free(numbers->mutex);
	free(numbers);
}
