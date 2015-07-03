/*
    Name:       keyword.h
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct Keyword Keyword;

struct Keyword {
    char    *name;
    int     value;
};

void initKeywords(void);

