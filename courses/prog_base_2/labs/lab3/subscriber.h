#include "headers.h"
#include "message.h"

#define MAX_Subs 10

struct subscriber_s{
	char name[20];
	message_addPrint_cb addPrint;
	message_removePrint_cb removePrint;
	message_addTransfer_cb addPrint_transfer;
	message_removeTransfer_cb removePrint_transfer;
	message_fullProcessing_cb fullProcessing;
	message_fullOverflow_cb fullOverflow;
};

subscriber_t subscriber_new(char* name);
void subscriber_delete(subscriber_t self);

void subscriber_setNotifiers(subscriber_t self, message_addPrint_cb addPrint,
                             message_removePrint_cb removePrint, message_addTransfer_cb addPrint_transfer,
                             message_removeTransfer_cb removePrint_transfer, message_fullProcessing_cb fullProcessing,
                             message_fullOverflow_cb fullOverflow);
