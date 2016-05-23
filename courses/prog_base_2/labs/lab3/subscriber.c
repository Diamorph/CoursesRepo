#include "subscriber.h"


subscriber_t subscriber_new(char* name){
	subscriber_t l = malloc(sizeof(struct subscriber_s));
	strcpy(l->name, name);
	printf("\n");
	printf("New Subscriber: %s\n", name);
	return l;
}

void subscriber_delete(subscriber_t self){
	free(self);
}

void subscriber_setNotifiers(subscriber_t self, message_addPrint_cb addPrint, message_removePrint_cb removePrint,
                             message_addTransfer_cb addPrint_transfer, message_removeTransfer_cb removePrint_transfer,
                             message_fullProcessing_cb fullProcessing, message_fullOverflow_cb fullOverflow){
	self->addPrint = addPrint;
	self->removePrint = removePrint;
	self->addPrint_transfer = addPrint_transfer;
	self->removePrint_transfer = removePrint_transfer;
	self->fullProcessing = fullProcessing;
	self->fullOverflow = fullOverflow;
}
