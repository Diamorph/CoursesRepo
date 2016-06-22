#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "Freelanser.h"
#include "cJSON.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

void server_answer(http_request_t, socket_t *,scientist_t  **);
void server_GET_all(http_request_t, socket_t *,scientist_t **);
void server_GET_id(http_request_t,socket_t *t,scientist_t **);
void server_DELETE_all(http_request_t,socket_t *,scientist_t **);
void server_DELETE_id(http_request_t,socket_t *,scientist_t **);
void server_POST(http_request_t,socket_t *,scientist_t **);


const char * http_request_getArg(http_request_t *, const char *);
http_request_t http_request_parse(const char * const request);
const char * keyvalue_toString(keyvalue_t * self);


#endif
