#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "mutex.h"
#include "thread.h"
#include "producer.h"

typedef struct consumer_s* consumer_t;

consumer_t consumer_new(numbers_t* numbers);
void consumer_delete(consumer_t consumer);
void consumer_join(consumer_t consumer);

numbers_t* numbers_create(void);
void numbers_delete(numbers_t* numbers);
