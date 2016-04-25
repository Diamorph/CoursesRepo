#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>

#include "db_manager.h"
#include "scientists.h"

struct db_s {
    sqlite3 * db;
};

db_t * db_new(const char * dbFile) {
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self) {
    sqlite3_close(self->db);
    free(self);
}




int db_insertScientist(db_t * self, scientist_t * sc)
{
   int newScientistId = -1;
   sqlite3_stmt * stmt = NULL;
   int rc = 0;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db,"INSERT INTO Scientists  (Name, Surname, Birthdate, Rating, Articles, Books) VALUES (?,?,?,?,?,?);", -1, &stmt, NULL)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_text(stmt, 1,sc->name,strlen(sc->name),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2,sc->surname,strlen(sc->surname),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3,sc->birthdate,strlen(sc->birthdate),SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,4,sc->rating);
    sqlite3_bind_int(stmt,5,sc->articles);
    sqlite3_bind_int(stmt,6,sc->books);

    if (SQLITE_DONE != (rc = sqlite3_step(stmt))) {
        printf("Not inserted! %i\n", rc);
    }
     newScientistId = (int) sqlite3_last_insert_rowid (self->db);
     sqlite3_finalize(stmt);
    return newScientistId;
}

scientist_t * db_getScientistById(db_t * self, int id)
{
    scientist_t * scientist = malloc(sizeof(scientist_t*));
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM Scientists WHERE Id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
     while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            printf("can't select scientists\n");
            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {   sqlite3_finalize(stmt);
            return scientist;
}
        else
        {
            _fillScientist(stmt,scientist);
        }
    }
    sqlite3_finalize(stmt);
}



void db_updateScientist(db_t * self, scientist_t * sc, int id)
{
    sqlite3_stmt * stmt = NULL;
   int rc = 0;
   if(SQLITE_OK != sqlite3_prepare_v2(self->db,"UPDATE Scientists SET Name = ?,Surname = ?,Birthdate = ?, Rating = ?, Articles = ?, Books = ? WHERE Id = ?;", -1, &stmt, NULL)) {
        printf("Not prepared!\n");
    }
    sqlite3_bind_text(stmt, 1,sc->name,strlen(sc->name),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2,sc->surname,strlen(sc->surname),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3,sc->birthdate,strlen(sc->birthdate),SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,4,sc->rating);
    sqlite3_bind_int(stmt,5,sc->articles);
    sqlite3_bind_int(stmt,6,sc->books);
    sqlite3_bind_int(stmt,7,id);

     if (SQLITE_DONE != (rc = sqlite3_step(stmt))) {
        printf("Not updated! %i\n", rc);
    }
     sqlite3_finalize(stmt);
}

void db_deleteScientist(db_t * self, int id)
{
    sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db, "DELETE FROM Scientists WHERE Id = ?;", -1, &stmt, 0)){
        printf("Not prepared!\n");
    }
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        printf("Not deleted! %i\n", rc);
    }
    sqlite3_finalize(stmt);
}

int db_countScientists(db_t * self) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Scientists;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

static void _fillScientist(sqlite3_stmt * stmt, scientist_t * sc) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    const unsigned char * birthdate = sqlite3_column_text(stmt, 3);
    double rating = sqlite3_column_double(stmt, 4);
    int articles = sqlite3_column_int(stmt, 5);
    int books = sqlite3_column_int(stmt, 6);
    sc->id = id;
    strcpy(sc->name, (const char *)name);
    strcpy(sc->surname, (const char *)surname);
    strcpy(sc->birthdate, (const char *)birthdate);
    sc->rating = rating;
    sc->articles = articles;
    sc->books = books;
}


int db_getScientistsTask(db_t * self, int K, int P, scientist_t * arr, int arrMax){
     sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Scientists WHERE Articles > ? OR Books > ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select students\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillScientist(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;

}
