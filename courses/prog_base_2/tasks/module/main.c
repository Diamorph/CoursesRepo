#include "text.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int main()
{
    text_t * tx = text_new();
    text_add(tx,"gfd", 0);
    text_add(tx,"gfd", 0);
    text_add(tx,"gfd", 0);
    text_add(tx,"gfd", 0);
    text_add(tx,"gfd fn fghd 8f fg", 0);

    text_size(tx);
    //printf("OK\n");
    print_text(tx);
    text_delete(tx, 3);
     text_size(tx);
    print_text(tx);
    printf("%i words\n", text_word_count(tx));
    text_remove(&tx);
    if (tx == NULL)
        puts("success");
    return 0;
}
