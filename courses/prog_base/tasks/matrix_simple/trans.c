#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*void fillRand();
void rotateCW180();
void flipV();
void transposSide();
int main()
{
    fillRand();
    rotateCW180();
    flipV();
    transposSide();
    system("pause");
    return 0;
}*/



void fillRand()
{
    const short N = 4;
    int mas[N][N];
int i, j, p, pp;
srand(time(NULL));
    for( i = 0; i < N; i++)
    {
        for( j = 0; j < N; j++)
        {
            mas[i][j] = rand() % 1999 - 999; // -999 to 999
        }
    }
    //-----------------------------------------------
    for( p = 0; p < N; p++)
    {
        for( pp = 0; pp < N; pp++)
        {
            printf("%i\t", mas[p][pp]);
        }
        printf("\n");
    }
    }



    void rotateCW180()
{ const short N = 4;
    int mas[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
    };
int i,j,work,p,pp;
for ( i = 0; i < 4; i++)
    {
work = mas[i][0];
mas[i][0] = mas [i][3];
mas[i][3] = work;
}
for ( i = 0; i < 4; i++)
    {
work = mas[i][1];
mas[i][1] = mas [i][2];
mas[i][2] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mas[0][j];
mas[0][j] = mas [3][j];
mas[3][j] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mas[1][j];
mas[1][j] = mas [2][j];
mas[2][j] = work;
}
//-----------------
for( p = 0; p < N; p++)
    {
        for( pp = 0; pp < N; pp++)
        {
            printf("%i\t", mas[p][pp]);
        }
        printf("\n");
    }
}



void flipV()
{const short N = 4;
    int mas[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
    };
    int j,work,p,pp;
for ( j = 0; j < 4; j++)
    {
work = mas[0][j];
mas[0][j] = mas [3][j];
mas[3][j] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mas[1][j];
mas[1][j] = mas [2][j];
mas[2][j] = work;
}
//-----------------
for( p = 0; p < N; p++)
    {
        for( pp = 0; pp < N; pp++)
        {
            printf("%i\t", mas[p][pp]);
        }
        printf("\n");
    }
}



void transposSide()
{
const short N = 4;
    int mas[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
    };
int i,j,t,t1,t2,t3,t4,t5,t6,p,pp;
    t = mas [0][0];
    mas[0][0] = mas[3][3];
    mas [3][3] = t;
    t1 = mas[1][0];
    mas[1][0] = mas[3][2];
    mas[3][2] = t1;
    t2 = mas[2][0];
    mas[2][0] = mas[3][1];
    mas[3][1] = t2;
    t3 = mas[0][1];
    mas[0][1] = mas[2][3];
    mas[2][3] = t3;
    t4 = mas[1][1];
    mas[1][1] = mas[2][2];
    mas[2][2] = t4;
    t5 = mas[0][2];
    mas[0][2] = mas[1][3];
    mas[1][3] = t5;
//-----------------
for( p = 0; p < N; p++)
    {
        for( pp = 0; pp < N; pp++)
        {
            printf("%i\t", mas[p][pp]);
        }
        printf("\n");
    }
}
