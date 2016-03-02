#include "text.h"


#define MAX_SIZE 25
#define MAX_SENTENCE 50
struct text_s {
char ** sentence;
int size;

};
text_t * text_new (){
text_t * tx = malloc(sizeof(text_t));
tx->sentence = malloc(MAX_SIZE*sizeof(char *));
tx->size = 0;
return tx;
}

text_status text_add(text_t * self,char  *text, int index) {
    if (index > self->size)
        return WRONG_INDEX;
    else {
        char * txt = malloc (sizeof(char) * strlen(text));
        strcpy(txt, text);
        for (int i = self->size - 1; i >= index; i--){
            self->sentence[i+1] = self->sentence[i];
        }
    self->sentence[index] = txt;
    self->size++;
    }
}

void print_text(text_t * self){
for (int i = 0; i < self->size; i++){
    printf("%s\n", self->sentence[i]);
}
}

int text_size(text_t * self){
    return self->size;
}

text_status text_delete(text_t * self, int index)
{
    if (index > self->size) {
        return WRONG_INDEX;
    }
    else {
        free(self->sentence[index]);
        if (index < self->size){
            for (int i = index; i < self->size ; i++ ){
                self->sentence[i] = self->sentence[i+1];
            }
        }
        self->size--;
        return OK;
    }

}

void text_remove (text_t ** self)
{
    for (int i = 0; i < (*self)->size; i++)
        free((*self)->sentence[i]);
    free((*self)->sentence);
    free(*self);
    *self = NULL;
}

int text_word_count (text_t * self)
{
    int count = 0, j;
    int flag;
    for (int i = 0; i < self->size; i++)
    {
        flag = 0;
        j = 0;
        while(self->sentence[i][j] != '\0')
        {
            if (flag && (self->sentence[i][j] <= 'a' || self->sentence[i][j] >= 'z') && (self->sentence[i][j] <= 'A' || self->sentence[i][j] >= 'Z') )
            {
                flag = 0;
                count++;
            }
            else
            {
                flag = 1;
                if (self->sentence[i][j + 1] == '\0')
                    count++;
            }
            j++;
        }
    }
    return count;
}

