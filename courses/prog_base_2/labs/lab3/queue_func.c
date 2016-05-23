#include "queue_func.h"

struct queueSet_s{
	queue_t queue1;
	queue_t queue2;
	subscriber_t subscribers[MAX_Subs];
	int numOfSubscribers;
};

static int getRandomInt(void){
	int randNum = rand() % 199 - 99;
	if (!randNum) randNum += (int)pow(-1, rand() % 2);
	return randNum;
}

queueSet_t queueSet_new(void){
	queueSet_t set = malloc(sizeof(struct queueSet_s));
	set->queue1 = queue_new();
	set->queue2 = queue_new();
	set->numOfSubscribers = 0;
	return set;
}

void queueSet_delete(queueSet_t self){
	queue_delete(self->queue1);
	queue_delete(self->queue2);
	free(self);
}

void queueSet_initialize(queueSet_t self){
	for (int i = 0; i < 3; i++){
		queue_add(self->queue1, abs(getRandomInt()));
		queue_add(self->queue2, abs(getRandomInt()));
	}
}

void queueSet_addSubscriber(queueSet_t self, subscriber_t subscriber){
	self->subscribers[self->numOfSubscribers++] = subscriber;
}


void queueSet_endlessIOLoop(queueSet_t self){
	while (1){
		if (_kbhit()){
			char c = _getch();
			if (c == VK_ESCAPE) {
				queueSet_delete(self);
				break;
			}
		}
		int queueNum = rand() % 2 + 1;
		queue_t queue = (queueNum == 1) ? self->queue1 : self->queue2;
		queue_t anotherQueue = (queueNum == 1) ? self->queue2 : self->queue1;
		int num = getRandomInt();
		if (num > 0){
			queue_add(queue, num);
			for (int i = 0; i < self->numOfSubscribers; i++){
				if (self->subscribers[i]->addPrint) self->subscribers[i]->addPrint(self->subscribers[i], queueNum, num);
			}
			if (queue_getSize(queue) > 10){
				if (queue_getSize(anotherQueue) < 9){
					Sleep(30);
					int prevElem = queue_remove(queue);
					queue_add(anotherQueue, prevElem);
					for (int i = 0; i < self->numOfSubscribers; i++){
						if (self->subscribers[i]->addPrint_transfer) self->subscribers[i]->addPrint_transfer(self->subscribers[i], queueNum, prevElem);
					}
				}
				else{
					//removing last elements
					int enqueueMain = queue_remove(queue);
					int enqueueAnother = queue_remove(anotherQueue);
					for (int i = 0; i < self->numOfSubscribers; i++){
						if (self->subscribers[i]->fullOverflow) self->subscribers[i]->fullOverflow(self->subscribers[i], queueNum, enqueueMain, enqueueAnother);
					}
				}

			}
		}
		else{
			int prevNum = queue_remove(queue);
			for (int i = 0; i < self->numOfSubscribers; i++){
				if (self->subscribers[i]->removePrint) self->subscribers[i]->removePrint(self->subscribers[i], queueNum, prevNum);
			}
			if (queue_getSize(anotherQueue) >= 2){
				Sleep(300);
				int transNum = queue_remove(anotherQueue);
				queue_add(queue, transNum);
				for (int i = 0; i < self->numOfSubscribers; i++){
					if (self->subscribers[i]->removePrint_transfer) self->subscribers[i]->removePrint_transfer(self->subscribers[i], queueNum, transNum);
				}
			}
			else{
				int num11 = abs(getRandomInt());
				int num12 = abs(getRandomInt());
				int num13 = abs(getRandomInt());
				int num22 = abs(getRandomInt());
				int num23 = abs(getRandomInt());
				queue_add(queue, num11);
				queue_add(queue, num12);
				queue_add(queue, num13);
				queue_add(anotherQueue, num22);
				queue_add(anotherQueue, num23);
				for (int i = 0; i < self->numOfSubscribers; i++){
					if (self->subscribers[i]->fullProcessing) self->subscribers[i]->fullProcessing(self->subscribers[i], queueNum, num11, num12, num13, num22, num23);
				}
			}

		}
		Sleep(300);
	}
}
