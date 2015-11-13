#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc (int n, int m);
void Rand2(int arr[], int size);
void printMatrix(int arr[], int size);
int checkRand2(int arr[], int size);
float meanValue(int arr[], int size);
int maxValue(int arr[], int size);
int meanIndex(int arr[], int size);
int maxIndex(int arr[], int size);
int maxOccurance(int arr[], int size);
int diff(int arr1[], int arr2[], int res[], int size);
void div1(int arr1[], int arr2[], int res[], int size);
int gt(int arr1[], int arr2[], int size);
void lor(int arr1[], int arr2[], int res[], int size);
int run(int moves[], int movesLen, int res1[], int resLen);


int main(){
    int size = 4, check, max, index, mean, meanvalue, dif, gt1,oc;
    int arr[size];
    int arr1[4] = {1,0,3,4};
    int arr2[4] = {1,4,8,4};
    int res[4] = {0,0,0,0};
    int moves[4] = {9,7,27,17};
    int movesLen = sizeof(moves)/sizeof(moves[0]);
    int res1[20];
    int resLen = sizeof(res)/sizeof(res[0]);
int n = 5, m = 2;
double result;
result = calc(n, m);

//printf("%f", result);

/*Rand2(arr, size);
printMatrix(arr, size);

check = checkRand2(arr, size);
printf("\ncheckRand2 = %i", check);

meanvalue = meanValue(arr, size);
printf("\nmeanValue = %i", meanvalue);

max = maxValue(arr, size);
printf("\nmaxValue = %i", max);

mean = meanIndex(arr, size);
printf("\nmeanIndex = %i", mean);

index = maxIndex(arr, size);
printf("\nmaxIndex = %i", index);

oc = maxOccurance(arr, size);
printf("\nmaxOccurance = %i", oc);


dif = diff(arr1, arr2, res, size);
printf("\ndiff = %i", dif);

div1(arr1, arr2, res, size);

gt1 = gt(arr1, arr2, size);
printf("\ngt = %i", gt1);

lor(arr1, arr2, res, size);*/

printMatrix(moves, size);
    int output = run(moves, movesLen, res1, resLen);
    printf("\n res =  %i", output);
return 0;
}


