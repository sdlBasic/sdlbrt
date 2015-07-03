/*
    Name:       keyword.c
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2001 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* not in .h file because of load order */
Keyword keyword[] = {
    { "and",        And         },
    { "append",     Append      },
    { "as",         As          },
    { "call",       Call        },
    { "case",       Case        },
    { "close",      Close       },
    { "const",      Const       },
    { "continue",   Continue    },
    { "common",     Common      },
    { "declare",    Declare     },
    { "delete",     Delete      },
    { "dim",        Dim         },
    { "do",         Do          },
    { "each",       Each        },
    { "else",       Else        },
    { "elseif",     ElseIf      },
    { "elsif",      ElseIf      },
    { "end",        End         },
    { "erase",      Erase       },
    { "error",      Error       },
    { "exit",       Exit        },
    { "explicit",   Explicit    },
    { "for",        For         },
    { "function",   Function    },
    { "if",         If          },
    { "in",         In          },
    { "include",    IncludeFile },
    { "input",      Input       },
    { "inv",        Inv         },
    { "is",         Is,         },
    { "let",        Let         },
    { "file",       Line        },
    { "loop",       Loop        },
    { "mod",        Mod         },
    { "new",        New         },
    { "next",       Next        },
    { "noconsole",  NoConsole   },
    { "not",        Not         },
    { "open",       Open        },
    { "option",     Option      },
    { "or",         Or          },
    { "output",     Output      },
    { "print",      Print       },
    { "qbasic",     QBasic      },
    { "redim",      ReDim       },
    { "return",     Return      },
    { "select",     Select      },
    { "shared",     Shared      },
    { "shl",        Shl         },
    { "shr",        Shr         },
    { "static",     Static      },
    { "step",       Step        },
    { "sub",        Sub         },
    { "then",       Then        },
    { "to",         To          },
    { "until",      Until       },
    { "wend",       Wend        },
    { "while",      While       },
    { "xor",        Xor         },
    { "zipinclude", ZipIncludeFile },
    { 0,            0           }
};


/* initKeywords: add keywords to the symbol table */
void initKeywords()
{
    int i;
    Symbol  *s;

    for (i = 0; keyword[i].name != NULL; i++) {

        s = findSymbol( keyword[i].name, NULL );
        if (s==NULL) {
            s = addSymbol( keyword[i].name, NULL, SYM_KEYWORD );
            s->klass = keyword[i].value;
        } else {
            ePrintf( Init, "initKeywords: keyword %s is already declared as a %s",
                symbolName[s->symboltype] );
        }
    }
}
