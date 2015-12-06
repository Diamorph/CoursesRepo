#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char * str = (char *)malloc(sizeof(char) * 50);
    char * Symbol = (char *)malloc(sizeof(char));
    char * Symbol2 = (char *)malloc(sizeof(char));
    char * Number = (char *)malloc(sizeof(char));
    char * Number2 = (char *)malloc(sizeof(char));
    int * i = (int *)malloc(sizeof(int));
    if (NULL == str || NULL == Symbol || NULL == Symbol2 || NULL == Number || NULL == Number){
        printf("Alloc error");
        return EXIT_FAILURE;
    }
    *i = 50;
    *Symbol = -100;
    puts("Please enter 16-based symbols(0 1 2 3 4 5 6 7 8 9 A-10 B-11 C-12 D-13 E-14 F-15)");
    puts("Type your string: ");
    fgets(str, *i, stdin);
    for(*i = 0; *i < strlen(str) - 1; (*i)++){
if((isdigit(str[*i])  && str[*i]>='0' && str[*i]<='9') || (isalpha(str[*i]) && (str[*i])>='A' && (str[*i])<='F')){
    *Symbol2 = *i;
    if(*Symbol==-100){
                *Symbol = *i;
        }
    }
}
    if(*Symbol!=-100){
        *Symbol = (str[*Symbol]);
        *Symbol2 = (str[*Symbol2]);
        *Number = isdigit(*Symbol) ? (*Symbol - '0') : (10 + (*Symbol) -  'A');
        *Number2 = isdigit(*Symbol2) ? (*Symbol2 - '0') : (10 + (*Symbol2) -  'A');
     printf("Result is %i", *Symbol < *Symbol2 ? *Number : *Number2 );
} else {
printf("ERROR!!! Please enter the correct data");
}
    free(str);
    free(Symbol);
    free(Symbol2);
    free(Number);
    free(Number2);
    free(i);
    return EXIT_SUCCESS;
}

