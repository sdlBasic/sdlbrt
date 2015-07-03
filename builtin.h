/*
    Name:       builtin.h
    Purpose:    builtin routines for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

void notYet( char *name);

void basPrintStack(void);
void basConcat(void);
void basConvBase(void);
void basIndexes(void);
//_________________________________________________________________________________________________________________________
// Run time
void basArgument(void);
void basArgc(void);
void basArgv(void);
void basCommand(void);
void basSetEnv(void);
void basGetEnv(void);
void basRun(void);
void basShell(void);
void basStop(void);
//_________________________________________________________________________________________________________________________
// Array
void basLBound(void);
void basQuickSort(void);
void basUBound(void);
//_________________________________________________________________________________________________________________________
//Strings
void basAsc(void);
void basChr(void);
void basFormat(void);
void basInsert(void);
void basInstr(void);
void basLCase(void);
void basLeft(void);
void basLen(void);
void basLTrim(void);
void basMid(void);
void basReplace(void);
void basReplaceSubStr(void);
void basReverse(void);
void basRight(void);
void basRInstr(void);
void basRTrim(void);
void basSpace(void);
void basStr(void);
void basStrF(void);
void basString(void);
void basTrim(void);
void basTally(void);
void basTypeOf(void);
void basUCase(void);
void basVal(void);

//_________________________________________________________________________________________________________________________
//Maths
void basAbs(void);
void basACos(void);
void basASin(void);
void basAtan(void);
void basAtan2(void);
void basBin(void);
void basCos(void);
void basExp(void);
void basFix(void);
void basFrac(void);
void basHex(void);
void basInt(void);
void basLog(void);
void basRandomize(void);
void basRnd(void);
void basRound(void);
void basSgn(void);
void basSin(void);
void basSqr(void);
void basTan(void);
void basMin(void);
void basMax(void);
void basBitwiseAnd(void);
void basBitwiseOr(void);
void basBitwiseXor(void);

//_________________________________________________________________________________________________________________________
//Files
void basEof(void);
void basFileExists(void);
void basFileCopy(void);
void basFileMove(void);
void basFileRename(void);
void basFreeFile(void);
void basKill(void);
void basLoc(void);
void basLof(void);
void basReadByte(void);
void basSeek(void);
void basWriteByte(void);

//_________________________________________________________________________________________________________________________
//Dirs
void basChDir(void);
void basDir(void);
void basDirExists(void);
void basDirFirst(void);
void basDirNext(void);
void basMkDir(void);
void basRmDir(void);

//_________________________________________________________________________________________________________________________
//Data function support
void basData(void);
void basRead(void);

//_________________________________________________________________________________________________________________________
//Date and time
void basDate(void);
void basTicks(void);
void basTime(void);


#ifdef MEMORYBANK_SUPPORT
#include "builtin/memorybank.h"
#endif

#ifdef SDLENGINE_SUPPORT
#include "builtin/sdlengine.h"
#endif

#ifdef CD_SUPPORT
#include "builtin/cd.h"
#endif

#ifdef VIDEOMPEG_SUPPORT
#include "builtin/videompeg.h"
#endif

#ifdef SOCKET_SUPPORT
#include "builtin/socket.h"
#endif

#ifdef SQLITE_SUPPORT
#include "builtin/sqlite.h"
#endif
//_________________________________________________________________________________________________________________


void addBuiltin( char *name, void (*routine)(void), int args, int optargs );
void initBuiltins(void);


static struct {     /* builtin routines */
    char    *name;
    void    (*routine)(void);
    int     args;
    int     optargs;
} builtin[] = {
    {"argument",        basArgument,        0,  1},
    {"argument$",       basArgument,        0,  1},
    {"printstack",      basPrintStack,      0,  0},
    {"convbase",        basConvBase,        2,  0},
    {"convbase$",       basConvBase,        2,  0},

//    Run time
    {"argc",            basArgc,            0,  0},
    {"argv",            basArgv,            1,  0},
    {"command",         basCommand,         0,  1},
    {"command$",        basCommand,         0,  1},
    {"setenv",          basSetEnv,          2,  0},
    {"getenv",          basGetEnv,          1,  0},
    {"run",             basRun,             1,  0},
    {"shell",           basShell,           1,  0},
    {"stop",            basStop,            0,  0},

//    Array
    {"indexes",         basIndexes,         1,  0},
    {"lbound",          basLBound,          2,  0},
    {"quicksort",       basQuickSort,       3,  0},
    {"ubound",          basUBound,          2,  0},

//    Strings
    {"chr",             basChr,             1,  0},
    {"chr$",            basChr,             1,  0},
    {"format",          basFormat,          1,  20},
    {"format$",         basFormat,          1,  20},
    {"insert",          basInsert,          3,  0},
    {"insert$",         basInsert,          3,  0},
    {"instr",           basInstr,           2,  1},
    {"lcase",           basLCase,           1,  0},
    {"lcase$",          basLCase,           1,  0},
    {"left",            basLeft,            2,  0},
    {"left$",           basLeft,            2,  0},
    {"len",             basLen,             1,  0},
    {"length",          basLen,             1,  0},
    {"ltrim",           basLTrim,           1,  0},
    {"ltrim$",          basLTrim,           1,  0},
    {"mid",             basMid,             2,  1},
    {"mid$",            basMid,             2,  1},
    {"replace",         basReplace,         2,  1},
    {"replace$",        basReplace,         2,  1},
    {"replacesubstr",   basReplaceSubStr,   3,  1},
    {"replacesubstr$",  basReplaceSubStr,   3,  1},
    {"reverse",         basReverse,         1,  0},
    {"reverse$",        basReverse,         1,  0},
    {"right",           basRight,           2,  0},
    {"right$",          basRight,           2,  0},
    {"rinstr",          basRInstr,          2,  1},
    {"rtrim",           basRTrim,           1,  0},
    {"rtrim$",          basRTrim,           1,  0},
    {"space",           basSpace,           1,  0},
    {"space$",          basSpace,           1,  0},
    {"str",             basStr,             1,  0},
    {"str$",            basStr,             1,  0},
    {"strf",            basStrF,            1,  0},
    {"strf$",           basStrF,            1,  0},
    {"string",          basString,          2,  0},
    {"string$",         basString,          2,  0},
    {"trim",            basTrim,            1,  0},
    {"trim$",           basTrim,            1,  0},
    {"tally",           basTally,           2,  1},
    {"ucase",           basUCase,           1,  0},
    {"ucase$",          basUCase,           1,  0},
    {"typeof$",         basTypeOf,          1,  0},
    {"typeof",          basTypeOf,          1,  0},

//    Maths
    {"abs",             basAbs,             1,  0},
    {"acos",            basACos,            1,  0},
    {"asc",             basAsc,             1,  0},
    {"asin",            basASin,            1,  0},
    {"atan",            basAtan,            1,  0},
    {"atan2",           basAtan2,           2,  0},
    {"bin",             basBin,             1,  0},
    {"bin$",            basBin,             1,  0},
    {"cos",             basCos,             1,  0},
    {"exp",             basExp,             1,  0},
    {"fix",             basFix,             1,  0},
    {"floor",           basFix,             1,  0},
    {"frac",            basFrac,            1,  0},
    {"hex",             basHex,             1,  0},
    {"hex$",            basHex,             1,  0},
    {"int",             basInt,             1,  0},
    {"log",             basLog,             1,  0},
    {"randomize",       basRandomize,       0,  1},
    {"rnd",             basRnd,             0,  1},
    {"round",           basRound,           1,  0},
    {"sgn",             basSgn,             1,  0},
    {"sin",             basSin,             1,  0},
    {"sqr",             basSqr,             1,  0},
    {"tan",             basTan,             1,  0},
    {"val",             basVal,             1,  0},
    {"min",             basMin,             2,  0},
    {"max",             basMax,             2,  0},
    {"bitwiseand",      basBitwiseAnd,      2,  0},
    {"bitwiseor",       basBitwiseOr,       2,  0},
    {"bitwisexor",      basBitwiseXor,      2,  0},
    {"andbit",          basBitwiseAnd,      2,  0},
    {"orbit",           basBitwiseOr,       2,  0},
    {"xorbit",          basBitwiseXor,      2,  0},

//    Files
    {"eof",             basEof,             1,  0},
    {"fileexists",      basFileExists,      1,  0},
    {"filecopy",        basFileCopy  ,      2,  0},
    {"filemove",        basFileMove  ,      2,  0},
    {"filerename",      basFileRename,      2,  0},
    {"freefile",        basFreeFile,        0,  0},
    {"kill",            basKill,            1,  0},
    {"filedelete",      basKill,            1,  0},
    {"loc",             basLoc,             1,  0},
    {"lof",             basLof,             1,  0},
    {"readbyte",        basReadByte,        1,  0},
    {"rename",          basFileRename,      2,  0},
    {"seek",            basSeek,            1,  1},
    {"writebyte",       basWriteByte,       2,  0},

//    Dirs
    {"chdir",           basChDir,           1,  0},
    {"dir",		basDir,             0,  0},
    {"dir$",		basDir,             0,  0},
    {"dirfirst",        basDirFirst,        1,  0},
    {"dirnext",		basDirNext,         0,  0},
    {"direxists",       basDirExists,       1,  0},
    {"mkdir",           basMkDir,           1,  0},
    {"rmdir",           basRmDir,           1,  0},

//    Data function support
    {"data",            basData,            0,  255},
    {"read",            basRead,            0,  1},

//    Date and time
    {"date",            basDate,            0,  0},
    {"date$",           basDate,            0,  0},
    {"ticks",           basTicks,           0,  0},
    {"time",            basTime,            0,  0},
    {"time$",           basTime,            0,  0},


#ifdef MEMORYBANK_SUPPORT
#include "builtin/struct-memorybank.h"
#endif
    
#ifdef SDLENGINE_SUPPORT
#include "builtin/struct-sdlengine.h"
#endif

#ifdef CD_SUPPORT
#include "builtin/struct-cd.h"
#endif
   
#ifdef VIDEOMPEG_SUPPORT
#include "builtin/struct-videompeg.h"
#endif

#ifdef SOCKET_SUPPORT
#include "builtin/struct-socket.h"
#endif

#ifdef SQLITE_SUPPORT
#include "builtin/struct-sqlite.h"
#endif

    {NULL,              NULL,               0,  0}
};

