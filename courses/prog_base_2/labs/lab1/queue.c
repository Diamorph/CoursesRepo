#include "player.h"
#include "queue.h"


struct queue_s{
    struct command * com;
    int head;
    int tail;
    int size;
    int max_size;
};


queue_t * queue_new(){
    queue_t * q = malloc(sizeof(queue_t));
    q->com = malloc(150*sizeof(struct command));
    q->tail = -1;
    q->head = 0;
    q->size = 0;
    q->max_size = 150;
    return q;
}

void double_queue(queue_t * self){
    self->max_size *=2;
    struct command * command;
    int * players;
    command = malloc((self->max_size)*sizeof(struct command));
    for (int i = 0; i <= self->tail;i++){
        command[i] = self->com[i];
    }
    if (self->head != 0){
        for (int i = self->head;i < self->max_size / 2; i++){
            command[i + self->max_size/2] = self->com[i];
        }
    }
    free(self->com);
    self->com = command;
}

int queue_size(queue_t * self){
    return self->size;
}

queue_status queue_add(queue_t * self, struct command com){
    if (self->tail == self->max_size - 1 && self->head != 0){
        self->tail = -1;
    }  else if(self->size == self->max_size){
            double_queue(self);
    }
    self->com[++(self->tail)] = com;
    self->size++;
    return KK;
}


struct command queue_del(queue_t * self){
    struct command temp = self->com[++(self->head)];
    self->size--;
    return temp;
}


void queue_remove (queue_t ** self)
{
    free((*self)->com);
    free(*self);
    *self = NULL;
}

void queue_print(queue_t * self)
{
    if (self->head < self->tail)
        for (int i = self->head; i <= self->tail; i++)
            printf("%i", self->com[i].command);
        else if(self->tail != self->head)
        {
            for (int i = self->head; i < self->max_size; i++)
                printf("%i", self->com[i].command);
            for (int i = 0; i < self->tail; i++)
                printf("%i", self->com[i].command);
        }
}
