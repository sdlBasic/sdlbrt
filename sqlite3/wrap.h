#ifdef SQLITE_SUPPORT

#include <sqlite3.h>


#define NUM_SQL_DB 10
#define NUM_SQL_STMTS 10
extern sqlite3      *sqldb[NUM_SQL_DB];
extern sqlite3_stmt *sqlprep[NUM_SQL_STMTS];


int wrapsqlopen(char *filename, int n);
int wrapsqlclose(int n); 
int wrapsqlprepare(int n, int pnum, char *sql); 
int wrapsqlfinalize(int pnum);
int wrapsqlstep(int pnum); 
int wrapsqlrows(int pnum);
int wrapsqlcolumns(int n);
char *wrapsqlcoltext( int pnum, int  col);
int wrapsqlimage(int pnum, int col, int imageslot);

#endif
