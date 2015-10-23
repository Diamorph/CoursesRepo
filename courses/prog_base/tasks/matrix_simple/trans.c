#include <time.h>


/*void fillRand(int mat[4][4]);
void rotateCW180(int mat[4][4]);
void flipV(int mat[4][4]);
void transposSide(int mat[4][4]);
void printMatrix(int mat[4][4]);
int main()
{ int mat[4][4];
    fillRand(mat);
    printMatrix(mat);

    rotateCW180(mat);
    printMatrix(mat);

    flipV(mat);
    printMatrix(mat);

    transposSide(mat);
    printMatrix(mat);

    system("pause");
    return 0;
}

void printMatrix(int mat[4][4]) {
   int i, j;
    int n = 4;
    printf("{ ");
    for (i = 0; i < n; i++) {
        printf("{");
        for (j = 0; j < n; j++) {
            printf("%5i, ", mat[i][j]);
        }
        printf("}");
        if ( i < n - 1)
            printf("\n  ");
    }
    printf(" };\n");
}
*/
void fillRand(int mat[4][4])
{
int i, j;;
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
int i,j,p,pp;
int mat1[4][4];
for (i = 0; i < 4; i++)
{
    for (j = 0; j < 4; j++){
        mat1[i][j] = mat[i][j];
    }
}

for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
        p = 3 - i;
        pp = 3 - j;
        mat[i][j] = mat1[p][pp];
                }
            }
}


void flipV(int mat[4][4])
{
    int i,j,c;
    int mat1[4][4];
for (i = 0; i < 4; i++)
{
    for (j = 0; j < 4; j++){
        mat1[i][j] = mat[i][j];
    }
}
for (i = 0; i < 4; i++)
{
    for (j = 0; j < 4; j++){
        c = 3 - i;
        mat[i][j] = mat1[c][j];
    }
}
}


void transposSide(int mat[4][4])
{
int i, j, c, d;
int mat1[4][4];
    for (i = 0; i < 4; i++)
{
    for (j = 0; j < 4; j++){
        mat1[i][j] = mat[i][j];
    }
}
    for (i = 0; i < 4; i++)
        {
        for (j = 0; j < 4; j++){
            c = 3 - j;
            d = 3 - i;
            mat[i][j] = mat1[c][d];
        }
    }
}



