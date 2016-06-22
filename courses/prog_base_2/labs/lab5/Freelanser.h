#ifndef FREELANSER_H_INCLUDED
#define FREELANSER_H_INCLUDED

typedef struct Scientist scientist_t;

scientist_t * Freelanser_new(void);
void Scientist_free(scientist_t *);
void Scientist_print(scientist_t *);

void Scientist_set(scientist_t *, char *, char * , double , char *, int );

char * Scientist_name_get(scientist_t *);
char * Scientist_surname_get(scientist_t *);
char * Scientist_date_get(scientist_t *);
double Scientist_age_get(scientist_t *);
int Scientist_salary_get(scientist_t *);

#endif
