#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "list.h"

#define MAX_NAME 50

typedef struct doc_s doc_t;
typedef struct user_s *user_t;

typedef enum {
    USER_SIMPLY,
    USER_ADMIN,
} user_type_t;


user_t user_new (char * nam);
doc_t * doc_new(const char *name);
void doc_free(doc_t * self);
char* DOC_getName(doc_t * self);
void DOC_addUser(doc_t * self, user_t * user);
list_t * DOC_getUsersList(doc_t * self);
