/*
    Name:       sdlBasic.h
    Purpose:    Core (wxBasic) version for sdlBasic
    Author:     David Cuny - __vroby__ based on sdlBasic.c
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


#define PROGNAME    "sdlbasic runtime"
#define RELEASE     "2013"
#define DATEOF      "11-Giu-2013"
#define COPYRIGHT   "(c) 2001 David Cuny and sdlBasic team"
#define LICENSE     "Lesser GNU Public License"
#define SDLBASIC    1

#ifdef AMIGA
#define Node ExecNode
#include <exec/nodes.h>
#undef Node
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#ifdef __amigaos4__
#include <sys/stat.h>
#endif

/* This piece of code allows sdlBasic to compile on FreeBSD 5.3 without <malloc.h> include problem */
/* Contributed by Tails92 */
#if !defined(FBSD) && !defined(__amigaos4__) && !defined(__APPLE__)
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#if defined(WIN32)
#include <windows.h>
#endif

extern int yylex();
extern void yyerror( char* );

#include "unzip/unzip.h"	    	/* Unzip Rutines 			*/
#include "SDLengine/SDLengine.h"	/* SDL rutines 				*/
#include "BASengine/BASengine.h" 	/* BASic rutines			*/
//#include "GLengine/GLengine.h"	/* GL rutines unimplemented yet 	*/

#if defined(SQLITE_SUPPORT)
#include "sqlite3/wrap.h"
#endif


#include "shared.h"         		/* shared routines                      */
#include "trace.h"          		/* tracing code                         */
#include "error.h"          		/* error messages and 'safe' routines   */
#include "stack.h"          		/* integer stack                        */
#include "data.h"           		/* data types                           */
#include "symbol.h"         		/* symbol table                         */
#include "var.h"            		/* variables                            */
#include "array.h"          		/* array structures                     */
#include "node.h"           		/* parse tree data structure            */
#include "builtin.h"        		/* builtin routines                     */

#include "const.h"          		/* builtin constants                    */
#include "eval.h"           		/* parse tree evaluator                 */
#include "keyword.h"        		/* keywords (defined in grammar file)   */
#include "lexer.h"          		/* lexer                                */
#include "class.h"          		/* class wrappers                       */

