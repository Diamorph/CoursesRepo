#ifndef LIST_H_INCLUDED1
#define LIST_H_INCLUDED1


#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue_s queue_t;

struct command {
    player_cmd command;
    //player_t * players;
};

typedef enum {
    KK = 0,
    ERROR
} queue_status;


queue_t * queue_new();
queue_status queue_add(queue_t * self, struct command com);
void double_queue(queue_t * self);
struct command queue_del(queue_t * self);
void queue_remove (queue_t ** self);


#endif
