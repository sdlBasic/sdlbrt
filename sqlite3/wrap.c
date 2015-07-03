#ifdef SQLITE_SUPPORT

#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "wrap.h"
#include<stdio.h>
#include "../SDLengine/SDLengine.h"


sqlite3      *sqldb[NUM_SQL_DB];
sqlite3_stmt *sqlprep[NUM_SQL_STMTS];

/*

  "basic", basic, 1, 1,   //STRUCTURE
   void mywrap();         //BASFUNCTION
*/
int wrapsqlopen(char *filename, int n) {

	int rc;

	rc=sqlite3_open(filename, &sqldb[n]);
	
	if (rc) {
		return -1;
	}
	return 0;

}
int wrapsqlclose(int n) {

	sqlite3_close(sqldb[n]);
	return 0;
}
int wrapsqlprepare(int n, int pnum, char *sql) {
	int rc;

	rc = sqlite3_prepare( sqldb[n], sql, -1, &sqlprep[pnum], 0);
	if ( rc == SQLITE_OK )
	{ 
		return 0;
	} 
	printf("SQLERROR: (%s)\n", sqlite3_errmsg( sqldb[n] ) );
	printf("SQL: (%s)\n", sql );
	return -1;
}
int wrapsqlfinalize(int pnum) {
	int rc;
	rc = sqlite3_finalize(sqlprep[pnum]);
	return 0;
}
int wrapsqlstep(int pnum) {
	int rc;
	rc = sqlite3_step( sqlprep[pnum] );
	return rc;
}
int wrapsqlrows(int pnum) {
	int count=0;
	return count;
}
int wrapsqlcolumns(int pnum) {
	int count;
	count= sqlite3_column_count(sqlprep[pnum]);
	return count;
}
char *wrapsqlcoltext( int pnum, int col)  
{
/*
	return sqlite3_column_text(sqlprep[pnum], col);
*/
	return (char*)sqlite3_column_text(sqlprep[pnum], col);
}
int wrapsqlimage(int pnum, int col, int imageslot)
{
/*
	int rc;
	unsigned char * blob ; 
	int bsize;
	blob = (unsigned char*)sqlite3_column_blob(sqlprep[pnum], col);
	bsize = sqlite3_column_bytes(sqlprep[pnum], col);
	rc = mapblobimage( blob, bsize, imageslot);
*/
	
	return  mapblobimage( (unsigned char *)sqlite3_column_blob (sqlprep[pnum],col),\
			     sqlite3_column_bytes(sqlprep[pnum], col),\
			     imageslot);
}

#endif
