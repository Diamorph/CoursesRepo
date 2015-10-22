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



void fillRand(int mat[4][4])
{
int i, j, p, pp;
srand(time(NULL));
    for( i = 0; i < 4; i++)
    {
        for( j = 0; j < 4; j++)
        {
            mat[i][j] = rand() % 1999 - 999; // -999 to 999
        }
    }
    }



    void rotateCW180(int mat[4][4])
{
int i,j,work,p,pp;
for ( i = 0; i < 4; i++)
    {
work = mat[i][0];
mat[i][0] = mat [i][3];
mat[i][3] = work;
}
for ( i = 0; i < 4; i++)
    {
work = mat[i][1];
mat[i][1] = mat[i][2];
mat[i][2] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mat[0][j];
mat[0][j] = mat[3][j];
mat[3][j] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mat[1][j];
mat[1][j] = mat[2][j];
mat[2][j] = work;
}
}



void flipV(int mat[4][4])
{
    int j,work,p,pp;
for ( j = 0; j < 4; j++)
    {
work = mat[0][j];
mat[0][j] = mat [3][j];
mat[3][j] = work;
}
for ( j = 0; j < 4; j++)
    {
work = mat[1][j];
mat[1][j] = mat [2][j];
mat[2][j] = work;
}
}



void transposSide(int mat[4][4])
{
int i,j,t,t1,t2,t3,t4,t5,t6,p,pp;
    t = mat[0][0];
    mat[0][0] = mat[3][3];
    mat[3][3] = t;
    t1 = mat[1][0];
    mat[1][0] = mat[3][2];
    mat[3][2] = t1;
    t2 = mat[2][0];
    mat[2][0] = mat[3][1];
    mat[3][1] = t2;
    t3 = mat[0][1];
    mat[0][1] = mat[2][3];
    mat[2][3] = t3;
    t4 = mat[1][1];
    mat[1][1] = mat[2][2];
    mat[2][2] = t4;
    t5 = mat[0][2];
    mat[0][2] = mat[1][3];
    mat[1][3] = t5;
}
