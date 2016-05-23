#include "headers.h"
typedef void(*print_cb)(subscriber_t subscriber, int queueNum, int num);
void message_add(subscriber_t subscriber, int queueNum, int elem);
typedef void(*message_addPrint_cb)(subscriber_t subscriber, int queueNum, int num);
void message_remove(subscriber_t subscriber, int queueNum, int elem);
typedef void(*message_removePrint_cb)(subscriber_t subscriber, int queueNum, int num);
void message_addTransfer(subscriber_t subscriber, int queueNum, int elem);
typedef void(*message_addTransfer_cb)(subscriber_t subscriber, int queueNum, int num);
typedef void(*message_removeTransfer_cb)(subscriber_t subscriber, int queueNum, int num);
void message_removeTransfer(subscriber_t subscriber, int queueNum, int elem);
typedef void(*message_fullProcessing_cb)(subscriber_t subscriber, int queueNum, int num11, int num12, int num13, int num22, int num23);
void message_processing(subscriber_t subscriber, int queueNum, int num11, int num12, int num13, int num22, int num23);
typedef void(*message_fullOverflow_cb)(subscriber_t subscriber, int queueNum, int enqueued1, int enqueued2);
void message_overflow(subscriber_t subscriber, int queueNum, int enqueued1, int enqueued2);

