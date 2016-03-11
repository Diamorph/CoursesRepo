#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


#include <stdlib.h>
#include <string.h>


typedef struct text_s text_t;

typedef enum {
OK = 0,
WRONG_INDEX
} text_status;


int text_word_count (text_t * self);
text_t * text_new();
text_status text_add(text_t *,char *,int);
text_status text_delete(text_t * self, int index);

void print_text(text_t *);
int text_size(text_t * self);


#endif
