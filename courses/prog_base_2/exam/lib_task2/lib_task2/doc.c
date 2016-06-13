
#include <strings.h>
#include <stdlib.h>
#include <stdlib.h>

#include "doc.h"



struct user_s {
    user_type_t type;
    char name[MAX_NAME];
};

user_t user_new (char * nam) {
    user_t self = malloc (sizeof(struct user_s));
    strcpy(self->name, nam);
    return self;
}
/*user_t user_new(user_type_t type,const char * name) {
    user_t self = malloc(sizeof(struct user_s));
    strcpy(self->name,name);
    return self;
};*/

void user_free(user_t * self) {
    free(self);
};

struct doc_s {
    char * name;
    list_t * users;
};


doc_t * doc_new(const char *name) {
    doc_t * self = malloc(sizeof(doc_t));
    sprintf(self->name,name);
    return self;
};

void doc_free(doc_t * self) {
    free(self);
};

void DOC_addUsers(doc_t * self, user_t * user) {
    list_push_back(self->users, user);
}


list_t * DOC_getUsersList(doc_t * self) {
    list_t * copy = list_new_copy(self->users);
    return copy;
}


user_t * DOC_removeUser(doc_t * self) {
    user_t * user = (user_t *)list_pop_back(self->users);
    return user;
}

char* DOC_getName(doc_t * self){
    //puts(self->name);
    char * res = self->name;
    return res;
}

