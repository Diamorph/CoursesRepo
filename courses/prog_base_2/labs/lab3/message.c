#include "message.h"
#include "subscriber.h"

void message_add(subscriber_t subscriber, int queueNum, int elem){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queue#%d: add %d\n", queueNum, elem);
}

void message_remove(subscriber_t subscriber, int queueNum, int elem){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queue#%d: removed %d\n", queueNum, elem);
}

void message_addTransfer(subscriber_t subscriber, int queueNum, int elem){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queue#%d: FULL, transferred %d to Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}

void message_removeTransfer(subscriber_t subscriber, int queueNum, int elem){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queue#%d: too small, transferred %d from Queue#%d\n", queueNum, elem, (queueNum == 1) ? 2 : 1);
}

void message_processing(subscriber_t subscriber, int queueNum, int num11, int num12, int num13, int num22, int num23){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queues: EMPTY! Filling with new elements: %d,%d,%d to Queue#%d and %d,%d to Queue#%d\n", num11, num12, num13, queueNum, num22, num23, (queueNum == 1) ? 2 : 1);
}

void message_overflow(subscriber_t subscriber, int queueNum, int enqueued1, int enqueued2){
	printf("\nSubscriber :%s\n",subscriber->name);
	printf("Queues: FULL!! Dequeuing first elements: %d from Queue#%d, %d from Queue#%d", enqueued1, queueNum, enqueued2, (queueNum == 1) ? 2 : 1);
}
