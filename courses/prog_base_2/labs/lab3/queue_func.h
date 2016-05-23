#include "headers.h"
#include "queue.h"
#include "subscriber.h"



queueSet_t queueSet_new(void);
void queueSet_delete(queueSet_t self);

void queueSet_initialize(queueSet_t self);
void queueSet_addSubscriber(queueSet_t self, subscriber_t subscriber);
void queueSet_endlessIOLoop(queueSet_t self);

