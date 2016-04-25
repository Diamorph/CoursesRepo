#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef struct scientist_s {
    int id;
    char name[256];
    char surname[256];
    char birthdate[11];
    double rating;
    int articles;
    int books;
} scientist_t;

void scientist_print(scientist_t * sc);
void scientist_printList(scientist_t * arr, int len);

#endif // STUDENT_H_INCLUDED
