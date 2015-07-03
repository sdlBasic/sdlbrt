/*********************************************************************

  unzip.h

  Support for retrieving files from zipfiles.

*********************************************************************/

/* public functions */
extern int load_zipped_file (char *zipfile, char *filename,
	unsigned char **buf, int *length);

extern int file_unzip(char *zipfile,char *filename,char *tmpdir);
/*********************************************************************/
