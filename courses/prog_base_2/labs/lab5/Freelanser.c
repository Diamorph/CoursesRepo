#include <stdlib.h>
#include <string.h>

#include "Freelanser.h"


struct Scientist {
    char * name;
    char * surname;
    double age;
    char * date;
    int salary;
};

scientist_t * Scientist_new(void) {
    scientist_t * sc = malloc(sizeof(struct Scientist));
    sc->name = NULL;
    sc->surname = NULL;
    sc->age = 0;
    sc->date = NULL;
    sc->salary = 0;
    return sc;
}

void Scientist_free(scientist_t * self) {
    free(self);
}

void Scientist_set(scientist_t * self, char * name, char * surname, double age, char * date,int salary){
    if(name!=NULL)
    {
    self->name=malloc(sizeof(name));
    strcpy(self->name,name);
    }
    else
        self->name=name;
    if(surname!=NULL)
    {
    self->surname=malloc(sizeof(surname));
    strcpy(self->surname,surname);
    }
    else
        self->surname=surname;
    if(date!=NULL)
    {
    self->date=malloc(sizeof(date));
    strcpy(self->date,date);
    }
    else
       self->date=date;


    self->age=age;

    self->salary=salary;
}


char * Scientist_name_get(scientist_t * sc)
{
    return sc->name;
}

char * Scientist_surname_get(scientist_t * sc)
{
    return sc->surname;
}

char * Scientist_date_get(scientist_t * sc)
{
    return sc->date;
}

double Scientist_age_get(scientist_t * sc)
{
    return sc->age;
}

int Scientist_salary_get(scientist_t * sc)
{
    return sc->salary;
}
