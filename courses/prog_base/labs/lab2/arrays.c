#include <time.h>
#include <math.h>

void printMatrix(int arr[], int size) {
   int i;
     printf("\n{ ");
    for (i = 0; i < size; i++) {
        printf("%i,  ", arr[i]);
}
 printf("}");
}
void Rand2(int arr[], int size)
{
int i;
srand(time(NULL));
    for( i = 0; i < size; i++)
    {
            arr[i] = rand() %511 - 255; /* 511 - 255*/
    }
    }

int checkRand2(int arr[], int size){
int i,check;
for (i = 0; i < size; i++){
    if (arr[i]>= -255 && arr[i] <= 255){
        check = 1;
    } else {
    check = 0;
    break;
    }
}
return check;
}
float meanValue(int arr[], int size){
int i,sum = 0;
    float mean;
    for (i = 0; i < size; i++){
        sum = arr[i] + sum;
    }
    mean = sum / i;
return mean;
}


int maxValue(int arr[], int size){
    int i,max = arr[0];
    for (i = 0; i < size; i++){
        if ( arr[i] >= max){
            max = arr[i];
        }
    }
return max;
}
int meanIndex(int arr[], int size){
    int i,j,sum = 0,min;
    int dif[size];
    float mean,difference;
    for (i = 0; i < size; i++){
        sum = arr[i] + sum;
    }
    mean = sum / i;
    for (i = 0; i < size; i++){
            dif[i] = arr[i] - mean;
            dif[i] = abs(dif[i]);
        }
    min = dif[0];
    for (i = 0; i < size; i++){
            if ( dif[i] <= min){
            min = dif[i];
            j = i;
    }
}
return j;
}


int maxIndex(int arr[], int size){
int i,j,max = arr[0];
    for (i = 0; i < size; i++){
        if ( arr[i] >= max){
            max = arr[i];
            j = i;
        }
    }
return j;
}


int maxOccurance(int arr[], int size){
    int i,j;
int max = arr[0], cmax = 0, rmax = 0;
for (i = 0; i < size; i++) {
		if (cmax == rmax && arr[i-1]>max) { //якщо кількість повторень попередньої моди(rmax) співпадає с теперішньою модою(cmax) і значення теперішньої більше від попереднього
            max = arr[i - 1]; 		//замінюємо значення моди на максимальне
		}
		if (cmax > rmax) {     //якщо кількість повторень теперішньої моди більше ніж попередньої
            rmax = cmax;		// замінюємо rmax і max на актуальны значення
			max = arr[i - 1];
		}
		cmax = 0;
        for (j = i; j < size; j++) //цикл для знаходження кількості повторень певного елемента у послідовності з позиції j
           if (arr[j] == arr[i]) //якщо наший елемент співпадає
              cmax++;        // додаємо до його значення кількості +1
    }
    return max;
}


int diff(int arr1[], int arr2[], int res[], int size){
int i,j;
    for (i = 0; i < size; i++){
            res[i] = arr1[i] - arr2[i];
             if (res[i] != 0){
                j = 0;
                break;
            } else {
                j = 1;
            }
        }
return j;
}



void div1(int arr1[], int arr2[], int res[], int size){
    int i;
    for (i = 0; i < size; i++){
            res[i] = arr1[i] / arr2[i];
        }
     printf("\n{ ");
    for (i = 0; i < size; i++) {
        printf("%i,  ", res[i]);
}
 printf("}");
    }

int gt(int arr1[], int arr2[], int size){
int i,j;
for (i = 0; i < size; i++){
 if (arr1[i] > arr2[i]){
    j = 1;
 } else{
     j = 0;
     break;
 }
}
return j;
}


void lor(int arr1[], int arr2[], int res[], int size){
int i;
for(i = 0; i < size; i++){
    if ((arr1[i] >= 0 && arr1[i] <= 1) || (arr2[i] >= 0 && arr2[i] <= 1)){
        res[i] = 1;
    } else {
        res[i] = 0;
    }
}
 printf("\n{ ");
    for (i = 0; i < size; i++) {
        printf("%i,  ", res[i]);
}
 printf("}");
}
