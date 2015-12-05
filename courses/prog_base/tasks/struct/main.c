#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TOWN{
	char name[100];
	double x; //latitude
	double y; //longtitude
};

void print(int size, struct TOWN* town){
	for (int i = 0; i < size; i++){
		printf("%d. %s\n", i + 1, town[i].name);
		printf("Latitude: %.2f \n", town[i].x);
		printf("Longtitude: %.2f \n", town[i].y);
	}
}

void count(int size, struct TOWN town[]){
	int count = 0;
	for (int i = 1; i < size; i++){
		double distance = sqrt(pow(town[i].x,2)+pow(town[i].y,2));
		if (distance < 50){
			count++;
		}
	}
	printf("Towns which are no further than 50 km from (0,0) : %d\n", count);
	}

void change(struct TOWN *town, const char* newVal){
	strcpy(town->name, newVal);
}

int main(void)
{
    struct TOWN town[3] = { "Kyiv",5, 49.3, "Cherkasy", 32, 27.98, "Chernihiv",50, 3.3};
	int size = sizeof(town) / (100+2*sizeof(double));
	char Name[100];
	char command[30];
	int Change, result;
	print(size, town);
	count(size, town);
	printf ("Type Name if you want to change name of town: \n");
    scanf("%s",command);
    if(strcmp(command,"Name") == 0){
	do {
		printf("Print number of the town and it's new name:\n");
		result = scanf("%d %s", &Change, Name);
		if (Change < 1 || Change > size) {
                puts("ERROR!!! Try again");
        }
	} while (Change < 1 || Change > size);
    change(&(town[Change-1]), Name);
	print(size,town);}
	getchar();
	return EXIT_SUCCESS;
}
