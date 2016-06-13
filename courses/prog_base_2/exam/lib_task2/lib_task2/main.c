#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "doc.h"

int main()
{
    doc_t * doc = doc_new("document");
    //DOC_getName(doc);
    puts(DOC_getName(doc));
    /*user_t users[2];
    users[0] = user_new("Ivan");*/
    //puts(str);
    //printf("%s", str);
 //user_t  user = user_new("Ivan");

    return 0;
}
