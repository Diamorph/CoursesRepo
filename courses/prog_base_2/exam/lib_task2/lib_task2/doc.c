#include "doc.h"




struct user_s {
   // int memory;
   // int RAM;
    //list_t * subscribers;
    char name;

};






struct doc_s {
    doc_state_t state;
    //doc_type_t type;
    char name;
    list_t * users;
    //int memory;
};


doc_t * doc_new() {
    doc_t * self = malloc(sizeof(doc_t));
    //self->type = type;
    //self->RAM = (PROGRAM_WORK == type) ? WORK_PROGRAM_RAM : GAME_PROGRAM_RAM;
    //self->memory = (PROGRAM_WORK == type) ? WORK_PROGRAM_memory : GAME_PROGRAM_memory;
    self->name = NULL;
    return self;
};

void doc_free(doc_t * self) {
    free(self);
};

/*void DOC_addUser(OC_t * self, doc_t * user) {
    /*if (__getTotalMemory(self) >= self->memory){
        printf("MEMORY IS FULL, PLEASE DELETE SOME PROGRAMS");
    }*/
   /* list_push_back(self-users, user);
}*/

void DOC_addUsers(DOC_t * self, user_t * user) {
    list_push_back(self->users, user);
}


list_t * DOC_getUsersList(doc_t * self) {
    list_t * copy = list_new_copy(self->users);
    return copy;
}
