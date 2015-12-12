#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void print(int arr[],int res[200],int size)
{
    int i = 0, j = 0;
    int s,e,mas[200];
    for(i = 0; i < 200; i++)
    {
        res[i] = 0;
    }
    for(i = 0; i < size; i++)
        res[arr[i]] = 1;

    for(i = 0; i < 200; i++)
    {
        if(res[i] == 1)
        {
            mas[j] = i;
            j++;
        }
    }
    s = mas[0];
    e = mas[0];
    printf("\n{");
    for(i = 1; i <= j; i++)
    {

        while(1)
        {
            if(mas[i] == (mas[i-1]+1))
            {
                e = mas[i];
                i++;
            }
            else
                break;
        }
        if(s == e)
        {
            printf("%i ",e);
            s = mas[i];
            e = mas[i];
        }
        else
        {
            printf("%i-%i ", s, e);
            s = mas[i];
            e = mas[i];
        }
    }
    printf("}\n");
}

int main(void)
{
    int pA[200];
    int pB[200];
    int pC[200];
    int pD[200];
    int A[] = {0,24,65,66,67,89};
    int size =  sizeof(A) / sizeof(int);
    print(A,pA,size);
    int B[] = {2,22,23,24,25,26};
    size =  sizeof(B) / sizeof(int);
    print(B,pB,size);
    int C[] = {4,55,56,57,58,63};
    size =  sizeof(C) / sizeof(int);
    print(C,pC,size);
    int D[200];
for (int i = 0; i < 6; i++){
    D[i] = C[i] &(~B[i] | A[i]);
    printf ("%d ", D[i]);
}
    return 0;
}
