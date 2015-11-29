#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fprocess(const char * pread, const char * pwrite){
int coordinates[6];
char str[500];
double a1,a2;
int i;
FILE *fread = fopen(pread, "r");
FILE *fwrite = fopen(pwrite, "w");
for (i = 1; i < 17; i++){
        fgets(str, 500, fread);
}
fscanf(fread, "%d %d %d %d %d %d", &coordinates[0],&coordinates[1],&coordinates[2],&coordinates[3],&coordinates[4],&coordinates[5]);
a1 = sqrt(pow(coordinates[0] - coordinates[4], 2) + pow(coordinates[1] - coordinates[5], 2));
a2 = sqrt(pow(coordinates[2] -coordinates[4], 2) + pow(coordinates[3] - coordinates[5], 2));
if (a1 < a2){
        fprintf(fwrite, "%d %d", coordinates[0], coordinates[1]);

}else  fprintf(fwrite, "%d %d", coordinates[2], coordinates[3]);
fclose(fread);
fclose(fwrite);
}
