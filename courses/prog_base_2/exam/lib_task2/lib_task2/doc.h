#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "list.h"

typedef struct doc_s doc_t;
typedef struct user_s user_t;


typedef enum {
    doc_ALLOWED,
    doc_NOTALLOWED
} doc_state_t;
