#include <stdio.h>

typedef struct Scientist scientist;


scientist * scientist_create();
void scientist_set(scientist * s,char * s_name,char * s_surname, char * s_birthdate,char * s_Papers, double s_experience, char * s_company, char * s_deparment);
void scientist_print(scientist* s);
void scientist_free(scientist * s);
