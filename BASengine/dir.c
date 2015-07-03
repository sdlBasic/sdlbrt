/*
    Name:       dir.c
    Purpose:    dir support for wxBasic/sdlBasic
    Author:     Viola Roberto __vroby__
    Copyright:  (c) 2003 Viola Roberto <__vroby__@libero.it>
    Licence:    LGPL
*/

#pragma GCC diagnostic ignored "-Wunused-result"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define LVLDIR 8

#if defined(UNIX) || defined(__MORPHOS__) || defined(__amigaos4__)
	#include <unistd.h>
	#include <dirent.h>
	DIR *hDir[LVLDIR];
	struct dirent *s_file[LVLDIR];
#else
	#include <direct.h>
	#include <io.h>
	struct _finddata_t c_file[LVLDIR];
	struct _finddata_t c_dir;
	long n_file[LVLDIR];
#endif


char dir_path[255];
char ext[LVLDIR][1024];
char prefix[LVLDIR][1024];
int lvldir;



//______________________________________________________________________________________________________________________

/* mkdir: make new directory */
/*
int mkdir(char *namedir)
{
char cmd[256];
#ifdef unix
	strcpy(cmd,"mkdir ");
	strcat(cmd,namedir);
	//printf(cmd);
#else
	strcpy(cmd,"md ");
	strcat(cmd,namedir);
	//printf(cmd);
#endif

	system(cmd);
	return 0;
}
*/
//______________________________________________________________________________________________________________________

//*
char *dir()
{

int i;

getcwd(dir_path,254);

for(i=0; i<strlen(dir_path);i++)
    if (dir_path[i]== '\\' ) dir_path[i]='/';


return dir_path;
}
//*/
//______________________________________________________________________________________________________________________

/* dir: listed in directory path the first entry */

char *dirfirst(char *path)
{
#if defined(UNIX) || defined(AMIGA)
	int i ;

	lvldir++;
	i=strlen(path);
	while(path[i]!='*' && path[i]!='/'){
	    i--;
	    if(i<1)break;
	}
	i++;
	strncpy(ext[lvldir],&path[i],(strlen(path)-i));

	i=strlen(path);
	while( path[i]!='/' ){
	    i--;
	    if(i<1)break;
	}

	if ((int)(strlen(path) - i - strlen(ext[lvldir]) - 2) > 1 )
	    strncpy(prefix[lvldir],&path[i+1],(strlen(path)-i-strlen(ext[lvldir])-2));
	else
	    strcpy(prefix[lvldir],"");

	path[i]='\0';

	hDir[lvldir] = opendir(path);
	if (hDir[lvldir] == NULL )return "";

	s_file[lvldir]=readdir(hDir[lvldir]);
	while( s_file[lvldir]!=NULL){
	    if (memcmp( &s_file[lvldir]->d_name, prefix[lvldir], strlen(prefix[lvldir]) )==0)
		if (memcmp( &s_file[lvldir]->d_name[strlen(s_file[lvldir]->d_name)-strlen(ext[lvldir])], ext[lvldir], strlen(ext[lvldir]) )==0){
		    break;
	    }
	    s_file[lvldir]=readdir(hDir[lvldir]);
	}

	if (s_file[lvldir]==NULL){
		closedir(hDir[lvldir]);
		lvldir--;
		return "";
	}
	    return s_file[lvldir]->d_name;
#else
	char * dirpath;

	lvldir++;
	dirpath=(char *) malloc(strlen(path)+4);
	strcpy(dirpath,path);
	strcat(dirpath,"*");
	dirpath[strlen(path)+2]='\0';

	n_file[lvldir]=_findfirst( dirpath, &c_file[lvldir] );
	if (n_file[lvldir]==-1L){
	    _findclose(n_file[lvldir]);
	    lvldir--;
	    free(dirpath);
	    return "";
	}
	free(dirpath);

	return c_file[lvldir].name;
#endif
}

/*______________________________________________________________________________________________________________________*/

/* dir: listed in directory path the next entry or none if it's at the end list */
char *dirnext()
{
#if defined(UNIX) || defined(AMIGA)
	s_file[lvldir]=readdir(hDir[lvldir]);
	while( s_file[lvldir]!=NULL){
	    if (memcmp( &s_file[lvldir]->d_name, prefix[lvldir], strlen(prefix[lvldir]) )==0)
		if (memcmp( &s_file[lvldir]->d_name[strlen(s_file[lvldir]->d_name)-strlen(ext[lvldir])], ext[lvldir], strlen(ext[lvldir]) )==0){
		    break;
	    }
	    s_file[lvldir]=readdir(hDir[lvldir]);
	}

	if (s_file[lvldir]==NULL){
		closedir(hDir[lvldir]);
		lvldir--;
		return "";
	}
	    return s_file[lvldir]->d_name;
#else
	if (_findnext(n_file[lvldir], &c_file[lvldir] )!=0){
	    if (n_file[lvldir]!=0){
		_findclose(n_file[lvldir]);
		lvldir--;
		return "";
	    }
	}
	return c_file[lvldir].name;
#endif
}
/*______________________________________________________________________________________________________________________*/

/* direxist: check if exist dir path */
int direxists(char *path)
{


#if defined(UNIX) || defined(AMIGA)
	DIR *hDirEx;

	hDirEx = opendir(path);
	if (hDirEx == NULL ){
		closedir(hDirEx);
		return 0;
	}
	else{
		closedir(hDirEx);
		return 1;
	}
#else
	FILE    *handle;
	long n_fileEx;

	n_fileEx=_findfirst( path, &c_dir);
	if (n_fileEx==-1L){
	    _findclose(n_fileEx);
		return 0;
	}
	else{
	    _findclose(n_fileEx);
	    handle = fopen( path, "rb" );
	    if (handle == NULL)
		return 1;
	    fclose( handle );
	    return 0;
	}
#endif
}
/*______________________________________________________________________________________________________________________*/

/* isdir: return 1 if path is a directory*/
int isdir(char *path)
{
	return direxists(path);
}
/*______________________________________________________________________________________________________________________*/
