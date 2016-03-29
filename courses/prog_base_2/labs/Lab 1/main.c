
#include "player.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main(void)
{
    struct command com;
    player_t * pl[5];
    pl[0] = player_new('w', 's', 'd', 'a', 'f');
    pl[1] = player_new('i','k','l','j',' ');
    queue_t * q = queue_new();
    scan(pl, 2, q);
    return 0;
}


void scan(player_t ** players, int numbOfPlayers, queue_t * queue){
    clock_t start;
    char * moves;
    char index;
    struct command com;
    while(index != '+')
    {
        start = clock();
        if (kbhit()){
            index = getch();
            for (int i = 0; i < numbOfPlayers; i++)
            {
                moves = player_get_moves(players[i]);
                for (int i = 0; i < 5; i++)
                    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = players[i];
                        queue_add(queue, com);
                        printf("%i", i);
                    }

            }
        }
        while(clock() - start < CLOCKS_PER_SEC/30);
    }
    puts("");
    queue_print(queue);
}
