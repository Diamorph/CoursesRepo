#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "scientist.h"
#include "parse.h"





int main(void) {
	FILE * fr = fopen("scientist.json", "r");
    char text[100000];
    char line[100];
    scientist * s[3];

    for (int i = 0; i < 3; i++){
    s[i] = scientist_create();
    }
    while(fgets(line, 100, fr) != NULL) {
        strcat(text, line);
    }
    parse(text,s);
	for (int i = 0; i < 3; i++){
    printf("\nScientist %d:\n",i);
	scientist_print(s[i]);
	}
	for (int i = 0; i < 3; i++){
    scientist_free(s[i]);
    }
	return 0;
}
