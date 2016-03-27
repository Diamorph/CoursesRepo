#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "producer.h"
#include "consumer.h"

int main(void){
	srand(time(NULL));

	numbers_t * numbers = numbers_create();                             //consumer.c


	producer_t prod1 = producer_create(numbers);
	consumer_t cons1 = consumer_create(numbers);
	producer_t prod2 = producer_create(numbers);
	consumer_t cons2 = consumer_create(numbers);

	consumer_join(cons2);


	producer_destructor(prod1);
	consumer_destructor(cons1);
	producer_destructor(prod2);
	consumer_destructor(cons2);
	numbers_destructor(numbers);                                        //consumer.c


	return 0;
}
