#include <stdlib.h>
#include <time.h>
#include "list.h"

typedef struct program_s program_t;
typedef struct OC_s OC_t;

typedef enum {
    PROGRAM_STOPPED,
    PROGRAM_RUNNING
} program_state_t;

typedef enum {
    PROGRAM_GAME,
    PROGRAM_WORK,
} program_type_t;

program_t * program_new(program_type_t type);
void program_free(program_t * self);

OC_t * OC_new();
void OC_free(OC_t * self);
void OC_addProgram(OC_t * self, program_t * program);

program_t * OC_removeProgram(OC_t * self);
list_t * OC_getProgramsList(OC_t * self);

int __getTotalRAM(OC_t * self);
int __getTotalMemory(OC_t * self);

int OC_getAllProgramsCount(OC_t * self);

typedef struct start_event_args_s {
    time_t startTime;
    size_t numPrograms;
    int totalRAM;
} start_event_args_t;

typedef void (*start_fn)(
    void * listener,
    OC_t * sender,
    start_event_args_t * args);

    void program_subscribeStart(OC_t * self, void * listener, start_fn callback);
    void program_unsubscribeStart(OC_t * self, void * listener, start_fn callback);
    void program_start(program_t * self,OC_t * oc);
    void program_stop(program_t * self);
    program_state_t program_getState(program_t * self);
    int getAllMemory(OC_t * self);
    int getAllRAM(OC_t * self);
