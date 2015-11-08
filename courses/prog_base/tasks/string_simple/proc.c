#include <string.h>

char * process(char * resultStr, const char * textLines[],
               int linesNum, const char * extraStr) {
    int i,j;
    int res = 0,res1 = 0,ress = 0,res2 = 0;
    char * line;
    char str[100];
    char * pstr = &str;
    puts("=== Text ===");
    for(i = 0; i < linesNum; i++) {
        line = textLines[i];
        puts(line);
    }
    for (i = 0; i < linesNum; i++){
		res1 = 0;
		for (j = 0; j < linesNum; j++){
			if (((strcmp(textLines[i], textLines[j]) == 0) || (strcmp(textLines[i], extraStr) == 0)) && (i != j)){
				res1 = 1;
			}
		}
		if (res1 == 0){
			res++;
		}
    }
    for (i = 0; i < linesNum; i++){
        if (strcmp(textLines[i], extraStr) == 0){
        res2 = 1;
    }
    }
    sprintf(pstr, " %i ", res);
    puts("=== Extra string ===");
    puts(extraStr);
    sprintf(pstr, " %i ", res);
    if (res2 != 0){
            sprintf(resultStr,"%s %s" , pstr, "NULL");
    } else{
        sprintf(resultStr,"%s %s", pstr, extraStr);
    }
    return resultStr;
}
