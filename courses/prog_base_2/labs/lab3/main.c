#include "queue.h"
#include "queue_func.h"


int main(void){
	srand(time(NULL));
	queueSet_t set = queueSet_new();
	queueSet_initialize(set);
	subscriber_t sub1 = subscriber_new("Anton");
	subscriber_setNotifiers(sub1, message_add, message_remove, message_addTransfer, message_removeTransfer, message_processing, message_overflow);
	queueSet_addSubscriber(set, sub1);
	queueSet_endlessIOLoop(set);

	subscriber_delete(sub1);
	queueSet_delete(set);

    return 0;
}


static void new_queue_zeroSize(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_getSize(queue), 0);
	queue_delete(queue);
}

static void add_oneElemToQueue_sizeOne(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_int_equal(queue_getSize(queue), 1);
	queue_delete(queue);
}

static void add_QueueIsFull_returnERROR(void **state){
	queue_t queue = queue_new();
	for (int i = 0; i < MAX_SIZE; i++){
		queue_add(queue, i);
	}
	assert_int_equal(queue_add(queue, 100), queue_error);
	queue_delete(queue);
}

static void remove_QueueIsNotEmpty_returnElem(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_int_equal(queue_remove(queue), 10);
	queue_delete(queue);
}

static void remove_fromQueue_correctSize(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	queue_add(queue, 15);
	queue_remove(queue);
	assert_int_equal(queue_getSize(queue), 1);
	queue_delete(queue);
}

static void remove_QueueIsEmpty_returnERROR(void **state){
	queue_t queue = queue_new();
	assert_int_equal(queue_remove(queue), queue_error);
	queue_delete(queue);
}

static void getSize_QueueIsEmpty_zeroSize(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 15);
	queue_remove(queue);
	assert_int_equal(queue_getSize(queue), 0);
	queue_delete(queue);
}

static void isEmpty_QueueIsNotEmpty_false(void **state){
	queue_t queue = queue_new();
	queue_add(queue, 10);
	assert_false(queue_isEmpty(queue));
	queue_delete(queue);
}

/*int main(void){
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test(new_queue_zeroSize),
		cmocka_unit_test(add_oneElemToQueue_sizeOne),
		cmocka_unit_test(add_QueueIsFull_returnERROR),
		cmocka_unit_test(remove_QueueIsNotEmpty_returnElem),
		cmocka_unit_test(remove_fromQueue_correctSize),
		cmocka_unit_test(remove_QueueIsEmpty_returnERROR),
		cmocka_unit_test(remove_fromQueue_correctSize),
		cmocka_unit_test(getSize_QueueIsEmpty_zeroSize),
		cmocka_unit_test(isEmpty_QueueIsNotEmpty_false),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}*/
