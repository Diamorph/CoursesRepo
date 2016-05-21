#include "OC.h"
const int MEMORY_OC = 40000;
const int RAM_OC = 4000;
const int WORK_PROGRAM_RAM = 400;
const int GAME_PROGRAM_RAM = 1400;
const int WORK_PROGRAM_memory = 2500;
const int GAME_PROGRAM_memory = 15000;

struct program_s {
    program_state_t state;
    program_type_t type;
    int RAM;
    int memory;
};

program_t * program_new(program_type_t type) {
    program_t * self = malloc(sizeof(program_t));
    self->type = type;
    self->RAM = (PROGRAM_WORK == type) ? WORK_PROGRAM_RAM : GAME_PROGRAM_RAM;
    self->memory = (PROGRAM_WORK == type) ? WORK_PROGRAM_memory : GAME_PROGRAM_memory;
    return self;
};

void program_free(program_t * self) {
    free(self);
};

struct OC_s {
    int memory;
    int RAM;
    list_t * subscribers;
    list_t * programs;
};

typedef struct subscriber_s {
    void * listener;
    start_fn callback;
} subscriber_t;

OC_t * OC_new() {
    OC_t * self = malloc(sizeof(OC_t));
    self->memory = MEMORY_OC;
    self->RAM = RAM_OC;
    self->subscribers = list_new();
    self->programs = list_new();
    return self;
}


void OC_free(OC_t * self) {
    list_free(self->subscribers);
    list_free(self->programs);
    free(self);
}

void program_subscribeStart(OC_t * self, void * listener, start_fn callback) {
    subscriber_t * sub = malloc(sizeof(subscriber_t));
    sub->listener = listener;
    sub->callback = callback;
    list_push_back(self->subscribers, sub);
}

void program_unsubscribeStart(OC_t * self, void * listener, start_fn callback) {
    for (int i = 0; i < list_getSize(self->subscribers); i++) {
        subscriber_t * subs = (subscriber_t *)list_get(self->subscribers, i);
        if ((subs->listener == listener) && (subs->callback == callback)) {
            list_remove(self->subscribers, i);
            break;
        }
    }
}


void OC_addProgram(OC_t * self, program_t * program) {
    if (__getTotalMemory(self) >= self->memory){
        printf("MEMORY IS FULL, PLEASE DELETE SOME PROGRAMS");
    }
    list_push_back(self->programs, program);
}


program_t * OC_removeProgram(OC_t * self) {
    program_t * program = (program_t *)list_pop_back(self->programs);
    return program;
}

list_t * OC_getProgramsList(OC_t * self) {
    list_t * copy = list_new_copy(self->programs);
    return copy;
}

int getAllMemory(OC_t * self){
    return self-> memory;
}

int getAllRAM(OC_t * self){
    return self-> RAM;
}

int __getTotalRAM(OC_t * self) {
    int RAM = 0;
    for (int i = 0; i < list_getSize(self->programs); i++) {
        program_t * program = list_get(self->programs, i);
        RAM += program->RAM;
    }
    return RAM;
}

int __getTotalMemory(OC_t * self) {
    int memory = 0;
    for (int i = 0; i < list_getSize(self->programs); i++) {
        program_t * program = list_get(self->programs, i);
        memory += program->memory;
    }
    return memory;
}

void program_start(program_t * self,OC_t * oc) {
    const int totalRAM = __getTotalRAM(oc);
    const int MAX_RAM = 4000;
    if (totalRAM <= MAX_RAM) {
        self->state = PROGRAM_RUNNING;
        start_event_args_t args;
        time(&(args.startTime));
        args.numPrograms = list_getSize(oc->programs);
        args.totalRAM = totalRAM;
        for (int i = 0; i < list_getSize(oc->subscribers); i++) {
            subscriber_t * sub = (subscriber_t *)list_get(oc->subscribers, i);
            sub->callback(sub->listener, oc, &args);
        }
    }
}


void program_stop(program_t * self) {
    self->state = PROGRAM_STOPPED;
}


program_state_t program_getState(program_t * self) {
    return self->state;
}


int OC_getAllProgramsCount(OC_t * self) {
    int count = 0;
    for (int i = 0; i < list_getSize(self->programs); i++) {
        count++;
    }
    return count;
}
