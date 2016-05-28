#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "scientists.h"
#include "sqlite3.h"
#include "cJSON.h"
#include "list.h"
typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertScientist(db_t * self, scientist_t * sc);
scientist_t * db_getScientistById(db_t * self, int id);
void db_updateScientist(db_t * self, scientist_t * sc, int id);
void db_deleteScientist(db_t * self, int id);
int db_countScientists(db_t * self);
void _fillScientist(sqlite3_stmt * stmt, scientist_t * sc);
int db_getScientistsTask(db_t * self, int K, int P, scientist_t * arr, int arrMax);
void db_getScientists(db_t * self,list_t * list1);
char * scientist_toJSON(scientist_t * self);
#endif // DB_MANAGER_H_INCLUDED
