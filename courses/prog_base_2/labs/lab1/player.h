#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player_s player_t;


typedef enum {
OK = 0,
WRONG_Command
} player_status;


typedef enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    FIRE
} player_cmd;

player_t * player_new(char u, char d, char r, char l, char f);
char * player_get_moves (player_t * pl);
void player_remove (player_t ** self);



#endif
