/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

int main(void) {
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "db.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc) {
        printf("Can't open file `%s`\n", dbFile);
        return 1;
    }

    printf("OK: Database connection established!");
    sqlite3_close(db);  // close connection to DB
    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include "db_manager.h"
#include "scientists.h"

int main()
{
    const char * dbFile = "db.db";
    scientist_t scientistList[100];
    db_t * db = db_new(dbFile);

    int countAllScientists = db_countScientists(db);
    printf("Scientists total: %i\n\n", countAllScientists);
    int filterArticles = 7;
    int filterBooks = 2;
    int count = db_getScientistsTask(db, filterArticles, filterBooks, scientistList, 100);
    printf("Scientists with Articles > %i or Books > %i: %i\n\n", filterArticles, filterBooks, count);
    scientist_printList(scientistList, count);
    db_insertScientist(db,&scientistList[count]);
    db_updateScientist(db,&scientistList[count],2);
    db_deleteScientist(db,1);
    printf("Scientist with id = 3:\n");
    scientist_t * sc = db_getScientistById(db,3);
    scientist_print(sc);


    //getch();
    system("pause");
    db_free(db);


    return 0;
}
