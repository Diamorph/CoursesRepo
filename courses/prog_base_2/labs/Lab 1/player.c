#include "player.h"
#include "queue.h"

#define MAX_SIZE 25


struct player_s {
    char ** name;
    int index;
    char command[5];


};
char * player_get_moves (player_t * pl)
{
    static char mas[5];
    for (int i = 0; i < 5; i++)
        mas[i] = pl->command[i];
    return mas;
}
player_t * player_new(char u, char d, char r, char l, char f){
    static int i = 0;
    i++;
    player_t * pl = malloc(sizeof(player_t));
    pl->name = malloc(MAX_SIZE*sizeof(char *));
    pl->index = i;
    pl->command[1] = d;
    pl->command[3] = r;
    pl->command[0] = u;
    pl->command[2] = l;
    pl->command[4] = f;
    return pl;
}
