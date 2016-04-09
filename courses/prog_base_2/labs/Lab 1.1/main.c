#include "player.h"
#include "queue.h"
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka_pbc.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main(void)
{
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
                if(i == 0) printf("\nplayer 1:");
                else printf("\nplayer 2:");
                for (int i = 0; i < 5; i++)
                    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = players[i];
                        queue_add(queue, com);
                        if (i == 1) printf("up");
                        if (i == 2) printf("down");
                        if (i == 3) printf("left");
                        if (i == 4) printf("right");
                        if (i == 5) printf("fire");
                        }

            }
        }
        while(clock() - start < CLOCKS_PER_SEC/30);
    }
    puts("");
    queue_print(queue);
}


static void Create__new__queue(void **queue){
    queue_t * q = queue_new();
    assert_int_equal(queue_size(q),0);
    queue_remove(&q);
}

static void Add__to__queue(void **queue, void **player){
    struct command com;
    queue_t * q = queue_new();
    player_t * pl[1];
    pl[0] = player_new('w', 's', 'd', 'a', 'f');
    char index = 'w';
    char * moves;
    moves = player_get_moves(pl[0]);
    for (int i = 0; i < 5; i++){
    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = pl[i];
                        assert_int_equal(queue_add(q, com),KK);
                    }
    }
    queue_remove(&q);
    player_remove(&pl);
}

static void Queue__size(void **queue, void **player){
    struct command com;
    queue_t * q = queue_new();
    player_t * pl[1];
    pl[0] = player_new('w', 's', 'd', 'a', 'f');
    char index = 'w';
    char * moves;
    moves = player_get_moves(pl[0]);
    for (int i = 0; i < 5; i++){
    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = pl[i];
                        queue_add(q, com);
                    }
    }
    assert_int_equal(queue_size(q),1);
    queue_remove(&q);
    player_remove(&pl);
}

static void Double__queue(void **queue, void **player){
    struct command com;
    queue_t * q = queue_new();
    player_t * pl[1];
    pl[0] = player_new('w', 's', 'd', 'a', 'f');
    char index = 'w';
    char * moves;
    moves = player_get_moves(pl[0]);
    for (int a = 0; a < 200; a++){
    for (int i = 0; i < 5; i++){
    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = pl[i];
                        queue_add(q, com);
                    }
    }
    }
    assert_int_equal(queue_size(q),200);
    queue_remove(&q);
    player_remove(&pl);
}

static void Queue__del(void **queue, void **player){
   struct command com;
    queue_t * q = queue_new();
    player_t * pl[1];
    pl[0] = player_new('w', 's', 'd', 'a', 'f');
    char index = 'w';
    char * moves;
    moves = player_get_moves(pl[0]);
    for (int a = 0; a < 100; a++){
    for (int i = 0; i < 5; i++){
    if (moves[i] == index)
                    {
                        i++;
                        com.command = i;
                        com.players = pl[i];
                        queue_add(q, com);
                    }
    }
    }
    queue_del(q);
    assert_int_equal(queue_size(q),99);
    queue_remove(&q);
    player_remove(&pl);
}


/*int main(void){
    struct command com;
const struct CMUnitTest tests[] =
    {
    cmocka_unit_test(Create__new__queue),
    cmocka_unit_test(Add__to__queue),
    cmocka_unit_test(Queue__size),
    cmocka_unit_test(Double__queue),
    cmocka_unit_test(Queue__del),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}*/
