#include <stdio.h>
#include "cJSON.h"
#include "scientist.h"
#include "parse.h"

struct Scientist{
char  name[20];
char  surname[20];
char  birthdate[20];
char  company[20];
char deparment[20];
int theNumberOfScientificPapers;
double experience;
};

scientist * scientist_create(){
scientist * s = malloc(sizeof(struct Scientist));
return s;
}


void scientist_fill(scientist * s,char * s_name,char * s_surname, char * s_birthdate,int s_Papers, double s_experience, char * s_company, char * s_deparment){
strcpy(s->name,s_name);
strcpy(s->surname,s_surname);
strcpy(s->birthdate,s_birthdate);
strcpy(s->company,s_company);
strcpy(s->deparment,s_deparment);
s->theNumberOfScientificPapers = s_Papers;
s->experience = s_experience;
}

void scientist_print(scientist* s){
printf("Name: %s\nSurname: %s\nBirthdate: %s\nThe Number Of Scientific Papers :%d \nExperience:%f \nCompany: %s\nDeparment: %s",s->name,s->surname,s->birthdate,s->theNumberOfScientificPapers,s->experience,s->company,s->deparment);
}

void scientist_free(scientist * s){
free(s);
}
