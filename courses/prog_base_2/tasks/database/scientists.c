#include <stdlib.h>
#include <stdio.h>

#include "scientists.h"

void scientist_print(scientist_t * sc) {
    printf("Name: %s\nSurname: %s\nBirthdate: %s\nRating: %f\nAtricles: %i\nBooks: %i\n\n",
        sc->name, sc->surname, sc->birthdate, sc->rating, sc->articles, sc->books);
}

void scientist_printList(scientist_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        scientist_print(&arr[i]);
    }
}

