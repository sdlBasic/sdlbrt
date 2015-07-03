%{

/* comma: return a sequence of items to execute */
Node *comma( Node *node1, Node *node2 )
{
    return opNode( OpComma, node1, node2 );
}

/* blockName: returns name of block */
char *blockName( int klass )
{
    switch(klass) {
    case -1:        return eCopyString( "end-of-file" );
    case For:       return eCopyString( "End For/Next" );
    case Function:  return eCopyString( "End Function" );
    case If:        return eCopyString( "End If" );
    case While:     return eCopyString( "End While" );
    case Do:	    return eCopyString( "Loop" );
    case Select:    return eCopyString( "End Select" );
    case Sub:       return eCopyString( "End Sub" );
    default:        return eCopyString("block");
    }
}

/* checkBlockEnd: make sure the block ends correctly */
void checkBlockEnd(int got)
{
    int     wanted;
    //char    *wantedName, *gotName;

    if (isEmptyStack(blockStack)) {
        switch (got) {
        case For:       ePrintf( Syntax, "End For without For");break;
        case Function:  ePrintf( Syntax, "End Function without Function");break;
        case If:        ePrintf( Syntax, "End If without If");break;
        case While:     ePrintf( Syntax, "End While without While");break;
        case Do:        ePrintf( Syntax, "Loop without Do");break;
        case Select:    ePrintf( Syntax, "End Select without Select");break;
        case Sub:       ePrintf( Syntax, "End Sub without Sub");break;
        }
    }

    wanted = peekStack(blockStack);
    if (got != wanted){
        ePrintf( Syntax, "expected %s, not %s", blockName(wanted), blockName(got));
    }
}

%}

/* %no_lines */
%union {
    int     iValue;         /* integer value */
    Number  fValue;         /* float value */
    char    *strValue;      /* string pointer */
    Node    *node;          /* parse node */
    Symbol  *symbol;        /* symbol */
}

%token <iValue> Integer
%token <iValue> Hex
%token <fValue> Float
%token <strValue> String
%token <symbol> FunctionName
%token <symbol> SubName
%token <symbol> ForwardSubName
%token <symbol> ForwardFunctionName
%token <symbol> BuiltinName
%token <symbol> ConstantName
%token <symbol> VariableName
%token <symbol> ArrayName
%token <symbol> TypeName
%token <symbol> ClassName
%token <strValue> MethodName
%token <strValue> Undefined

%type <node> block
%type <node> command
%type <node> statement
%type <node> elseIf
%type <node> expr
%type <node> argList
%type <node> argItems
%type <node> printList
%type <node> subList
%type <node> indexList
%type <node> cases
%type <node> caseTests
%type <node> caseTail
%type <node> loopTail
%type <node> dimList
%type <node> dimItem
%type <node> dimIndexList
%type <node> dimIndexItems
%type <node> indexListTail
%type <node> lval
%type <iValue> fileMode
%type <node> constList
%type <node> constItem
%type <node> fileHandle

%token And
%token Append
%token As
%token Call
%token Case
%token Class
%token Close
%token Common
%token Const
%token Continue
%token Declare
%token Default
%token Delete
%token Dim
%token Do
%token Each
%token Else
%token ElseIf
%token End
%token EndX
%token Erase
%token Error
%token Exit
%token Explicit
%token For
%token Function
%token Get
%token GetRef
%token GoTo
%token If
%token In
%token IncludeFile
%token ZipIncludeFile
%token Input
%token Inv
%token Is
%token Let
%token Line
%token Loop
%token Mod
%token New
%token Next
%token NoConsole
%token Not
%token Or
%token Open
%token Option
%token Output
%token Preserve
%token Print
%token QBasic
%token ReDim
%token Return
%token Select
%token Set
%token Shared
%token Shl
%token Shr
%token Static
%token Step
%token Sub
%token Then
%token To
%token Until
%token Wend
%token While
%token With
%token Xor

/* two character tokens */
%token Ge
%token Le
%token Ne
%token <iValue> IncrSelf        /* +=, -=, *=, /=, &= */

%nonassoc UMinus

/* precedence, weakest to strongest */
%left And Or Xor
%left In
%left Eq Ne Lt Gt Le Ge
%left '+' '-' '!' Not '&' '|' Mod Inv
%left '*' '/' '\\' '%' Shl Shr
%left '^'

%%

program:

      program statement
        {
            /* should be empty at this point */
            if (!isEmptyStack(blockStack)) {
                    checkBlockEnd(-1);
            }

            /* print error? */
            if (errFlag) {
                ePrintf( Syntax, "syntax error");
            }

            /* code? */
            if ($2 != NULL) {
                /* defer or execute */
                if (qBasicFlag) {
                    if (deferredCode == NULL) {
                        deferredCode = $2;
                    } else {
                        deferredCode = comma( deferredCode, $2 );
                    }
                } else {
                    eval( $2 );
                    freeNode( $2 );
                }
            } }

    | /* nothing */
        {   eval( deferredCode );
            freeNode( deferredCode ); }
    ;

block:

      End If
        {   checkBlockEnd(If);
            $$ = NULL; }

    | End For
        {   checkBlockEnd(For);
            $$ = NULL; }

    | End Function
        {   clearStack( sharedStack );
            checkBlockEnd(Function);
            $$ = NULL; }

    | End Sub
        {   clearStack( sharedStack );
            checkBlockEnd(Sub);
            $$ = NULL; }

    | End While
        {   checkBlockEnd(While);
            $$ = NULL; }

    | Loop
        {   checkBlockEnd(Do);
            $$ = NULL;
	    }

    | End Select
        {   checkBlockEnd(Select);
            $$ = NULL; }

    | Next
        {   checkBlockEnd(For);
            $$ = NULL; }

    | Wend
        {   checkBlockEnd(While);
            $$ = NULL; }

    | statement block
            {   if (errFlag) {
                    ePrintf( Syntax, "syntax error");
                }
                if ($1 == NULL) {
                    $$ = $2;
                } else {
                    $$ = comma( $1, $2 );
                } }

    | /* nothing */
        { $$ = NULL; }
    ;


statement:
    command
        {   if ($$ != NULL) {
                $1->trace = parseLineId;

            }
            $$ = $1; }
    ;

command:

      '~' expr '(' ')' sep
        {   $$ = opNode( OpDestroy, $2, NULL ); }

    | '~' expr error
        {   expected("("); }

    | '~' expr '(' error
        {   expected(")"); }

    | expr sep
        {   /* convert to call (drop result) */
            switch ($1->op) {
            case OpMethod:
                $1->op = OpMethodCall;
                break;
            case OpClassMethod:
                $1->op = OpClassMethodCall;
                break;
            default:
                ePrintf( Syntax, "result of expression not assigned");
                break;
            }
            $$ = $1; }

    | ConstantName Eq
        {   ePrintf( Syntax, "duplicate definition of %s", $1->name); }

    | FunctionName Eq expr
        {   if ($1 != currentScope || !inStack(blockStack,Function)) {
                ePrintf( Syntax, "assignment outside Function");
            }
            $$ = opNode( OpReturnSetValue, $3, NULL ); }


    | FunctionName '('
        {   pushStack( argCountStack, 0 ); }

          argList sep
        {   int args = popStack( argCountStack );
            checkArgCount( $1, args );
            $$ = symbolNode( OpFunctionCall, $1, $4, NULL ); }

    | SubName '('
        {   pushStack( argCountStack, 0 ); }

          argList sep
        {   int args = popStack( argCountStack );
            checkArgCount( $1, args );
            $$ = symbolNode( OpFunctionCall, $1, $4, NULL ); }

    | ForwardFunctionName '('
        {
            pushStack( argCountStack, 0 ); }

          argList sep
        {   checkArgCount( $1, popStack( argCountStack ) );
            $$ = symbolNode( OpFunctionCall, $1, $4, NULL ); }

    | ForwardSubName '('
        {
            pushStack( argCountStack, 0 ); }

          argList sep
        {   checkArgCount( $1, popStack( argCountStack ) );
            $$ = symbolNode( OpFunctionCall, $1, $4, NULL ); }


    | FunctionName sep
        { if ($1->args != 0) {
              expected("'('");
        }
        $$ = symbolNode( OpFunctionCall, $1, NULL, NULL ); }

    | SubName sep
        { if ($1->args != 0) {
              expected("'('");
        }
        $$ = symbolNode( OpFunctionCall, $1, NULL, NULL ); }


    | ForwardFunctionName sep
        { if ($1->args != 0) {
              expected("'('");
        }
        $$ = symbolNode( OpFunctionCall, $1, NULL, NULL ); }

    | ForwardSubName sep
        { if ($1->args != 0) {
              expected("'('");
        }
        $$ = symbolNode( OpFunctionCall, $1, NULL, NULL ); }


    | BuiltinName '('
        { pushStack( argCountStack, 0 ); }

          argList sep
        { int args = popStack( argCountStack );
          checkArgCount( $1, args );
          $$ = symbolNode( OpBuiltinCall, $1, $4, NULL ); }

    | BuiltinName sep
        { if ($1->args != 0) {
              expected("'('");
          }
          $$ = symbolNode( OpBuiltinCall, $1, NULL, NULL ); }

    | Close fileHandle sep
        {   $$ = opNode( OpClose, $2, NULL ); }

    | Close sep
        {   $$ = opNode( OpClose, NULL, NULL ); }

    | Const constList sep
        { $$ = $2; }

    | Common
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "Can't use Common in Sub or Function" );
            }
            commonFlag = 1; }

        dimList sep
        {   $$ = $3;
            commonFlag = 0; }

    | Continue sep
        {   if (!inStack(blockStack,For) && !inStack(blockStack,While)) {
                ePrintf( Syntax, "Continue outside For or While");
            }
            $$ = opNode( OpContinue, NULL, NULL ); }

    | Delete expr sep
        { $$ = opNode( OpDelete, $2, NULL ); }

    /* same as Dim Common */
    | Dim Common
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "Can't use Common in Sub or Function" );
            }
            commonFlag = 1; }

        dimList sep
        {   $$ = $4;
            commonFlag = 0; }

    /* same as Shared */
    | Dim Shared
        {   if (currentScope == NULL) {
                ePrintf( Syntax, "Shared illegal outside Sub or Function");
            }
            pushStack(blockStack, (intptr_t)currentScope );
            currentScope = NULL; }
        sharedList sep
        {   currentScope = (Symbol *)popStack(blockStack);
            $$ = NULL; }

    | Dim dimList sep
        {   $$ = $2; }

    | EndX sep
        { $$ = opNode( OpEnd, NULL, NULL ); }

    | Erase ArrayName optBrackets sep
        {   $$ = symbolNode( OpErase, $2, NULL, NULL ); }

    | Erase ArrayName '[' indexList sep
        {   checkArgCount( $2, popStack( argCountStack ) );
            $$ = symbolNode( OpErase, $2, $4, NULL ); }

    | Exit Do
        {   if (!inStack(blockStack,Do)) {
                ePrintf( Syntax, "Exit outside Do loop");
            }
            $$ = opNode( OpExitDo, NULL, NULL ); }

    | Exit For
        {   if (!inStack(blockStack,For)) {
                ePrintf( Syntax, "Exit outside For loop");
            }
            $$ = opNode( OpExitFor, NULL, NULL ); }

    | Exit Function
        {   if (!inStack(blockStack,Function)) {
                ePrintf( Syntax, "Exit Function outside Function");
            }
            $$ = opNode( OpExitRoutine, NULL, NULL ); }

    | Exit Sub
        {   if (!inStack(blockStack,Sub)) {
                ePrintf( Syntax, "Exit Sub outside Sub");
            }
            $$ = opNode( OpExitRoutine, NULL, NULL ); }

    | Exit While
        {   if (!inStack(blockStack,While)) {
                ePrintf( Syntax, "Exit outside While loop");
            }
            $$ = opNode( OpExitWhile, NULL, NULL ); }

    | Exit error
        {   expected("Do, For, Sub, Function or While"); }


    /* If <expr> Then ... ElseIf <expr> ... Else ... End If */
    | If
        {   pushStack(blockStack,If); }

      expr Then sep block elseIf sep
        {   popStack(blockStack);
            $$ = opNode( OpIf, opNode( OpIfTrue, $3, $6 ), $7 );
	}

    /* For Each <var> In <expr> */
    | For Each VariableName In ArrayName optBrackets
        {   pushStack(blockStack,For); }

        sep block
        {   popStack(blockStack);
            $$ = symbolNode( OpForEach, $3,
                symbolNode( OpNoOp, $5, NULL, NULL ), $9 ); }

    | For Each VariableName In error
        {   expected("an Array"); }


    | For Each Undefined In ArrayName
        {   pushStack(blockStack,For); }

        sep block
        {   popStack(blockStack);
            $$ = symbolNode( OpForEach, returnVar($3, SYM_VARIABLE, 0),
                symbolNode( OpNoOp, $5, NULL, NULL ), $8 ); }

    | For Each Undefined In error
        {   expected("an Array"); }

    | For Each VariableName error
        {   expected("In"); }

    | For Each Undefined error
        {   expected("In"); }

    | For Each error
        {   expected("a variable"); }

    /* For <var> = <expr> To <expr> [step <expr>] ... next */
    | For VariableName
        {   pushStack(blockStack,For); }

      loopTail sep
        {   popStack(blockStack);
            $4->value.symbol = $2;
            $$ = $4; }

    | For Undefined
        {   pushStack(blockStack,For);
            returnVar($2, SYM_VARIABLE, 0); }

        loopTail sep
        {   popStack(blockStack);
            $4->value.symbol = findSymbol($2, currentScope);
            free( $2 );
            $$ = $4; }

    | For error
        {   expected("Each or a variable"); }


    | Declare Function Undefined
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define function %s in %s", $3, currentScope->name );
            }
            currentScope = addSymbol( $3, NULL, SYM_FUNCTION );
        }

      parmlist sep
        {   currentScope->code = NULL;
            currentScope->forward = 1;
            $$ = NULL;
            free( $3 );
            currentScope = NULL; }

    | Declare Sub Undefined
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Sub %s in %s", $3, currentScope->name );
            }
            currentScope = addSymbol( $3, NULL, SYM_SUB );
        }

      parmlist sep
        {   currentScope->code = NULL;
            currentScope->forward = 1;
            $$ = NULL;
            free( $3 );
            currentScope = NULL; }

    | Declare error
        {   expected("sub or function"); }


    | Function Undefined
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Function %s in %s", $2, currentScope->name );
            }
            currentScope = addSymbol( $2, NULL, SYM_FUNCTION );
            pushStack( blockStack, Function );
        }

      parmlist sep  block sep
        {   popStack( blockStack );
            currentScope->code = $6;
            $$ = NULL;
            free( $2 );
            currentScope = NULL; }

    | Sub Undefined
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Sub %s in %s", $2, currentScope->name );
            }

            currentScope = addSymbol( $2, NULL, SYM_SUB );
            pushStack( blockStack, Sub );
        }

      parmlist sep  block sep
        {   popStack( blockStack );
            currentScope->code = $6;
            $$ = NULL;
            free( $2 );
            currentScope = NULL; }


    | Function FunctionName
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Function %s in %s",
                    $2->name, currentScope->name );
            }
            if (!$2->forward) {
                ePrintf( Syntax, "function %s has already been declared", $2->name );
            }

            currentScope = $2;
            pushStack( argCountStack, 0 );
        }

        declaredList
        {   if (popStack( argCountStack ) != currentScope->args) {
                ePrintf( Syntax, "%s arg count does not match declaration - too few args", currentScope->name);
            }
            pushStack( blockStack, Function );
        }
        block sep
        {   popStack( blockStack );
            currentScope->code = $6;
            currentScope->forward = 0;
            $$ = NULL;
            currentScope = NULL; }

    | Function ForwardFunctionName
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Function %s in %s",
                    $2->name, currentScope->name );
            }

            /* change to function */
            $2->symboltype = SYM_FUNCTION;
            currentScope = $2;
            pushStack( blockStack, Function );

            /* save var count and clear */
            pushStack( argCountStack, currentScope->args);
            currentScope->args = 0;
        }

        parmlist sep  block sep
        {   checkArgCount( $2, popStack( argCountStack ) );
            popStack( blockStack );
            currentScope->code = $6;
            currentScope->forward = 0;
            $$ = NULL;
            currentScope = NULL; }


    | Sub SubName
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Sub %s in %s",
                    $2->name, currentScope->name );
            }
            if (!$2->forward) {
                ePrintf( Syntax, "sub %s has already been declared", $2->name );
            }
            currentScope = $2;
            pushStack( argCountStack, 0 );
        }

        declaredList
        {   if (popStack( argCountStack ) != currentScope->args) {
                ePrintf( Syntax, "%s arg count does not match declaration - too few args", currentScope->name);
            }
            pushStack( blockStack, Sub );
        }

        block sep
        {   popStack( blockStack );
            currentScope->code = $6;
            currentScope->forward = 0;
            $$ = NULL;
            currentScope = NULL; }


    | Sub ForwardSubName
        {   if (currentScope != NULL) {
                ePrintf( Syntax, "can't define Sub %s in %s",
                    $2->name, currentScope->name );
            }

            /* change to sub */
            $2->symboltype = SYM_SUB;
            currentScope = $2;
            pushStack( blockStack, Sub );

            /* save var count and clear */
            pushStack( argCountStack, currentScope->args);
            currentScope->args = 0;
        }

      parmlist sep  block sep
        {   checkArgCount( $2, popStack( argCountStack ) );
            popStack( blockStack );
            currentScope->code = $6;
            currentScope->forward = 0;
            $$ = NULL;
            currentScope = NULL; }

    | Function error
        {   expected("Function name"); }

    | Sub error
        {   expected("Sub name"); }


    | IncludeFile String sep
        {   pushIncludeFile( eCopyString($2), 0 );
            $$ = NULL;
            free( $2 ); }

    | ZipIncludeFile String ',' String sep
        {   pushZipIncludeFile( eCopyString($2), eCopyString($4), 0 );
            $$ = NULL;
            free( $2 ); }

    | Line Input fileHandle ',' lval sep
        {   /* set into lval */
            $5->right = intNode( OpInput, 1, $3, NULL );
            $$ = $5; }

    | Input fileHandle ',' lval sep
        {   /* set into lval */
            $4->right = intNode( OpInput, 1, $2, NULL );
            $$ = $4; }

    | Line Input fileHandle error
        {   expected(", "); }

    | Open expr For fileMode As fileHandle sep
        {   $$ = intNode( OpOpen, $4, $2, $6 ); }

    | Open expr For fileMode As error
        {   expected("#"); }

    | Open expr error
        {   expected("For"); }

    | Option Explicit
        {   explicitFlag = 1;
            $$ = NULL; }

    | Option NoConsole
        {   consoleFlag = 0;
            $$ = NULL; }


    | Option QBasic
        {   qBasicFlag = 1;
            $$ = NULL; }


    | Print printList sep
        {   $$ = opNode( OpPrint, NULL, $2 ); }

    | '?' printList sep
        {   $$ = opNode( OpPrint, NULL, $2 ); }

    | Print '#' expr ',' printList sep
        {   $$ = opNode( OpPrint, $3, $5 ); }

    | Line Output fileHandle ',' printList sep
        {   $$ = opNode( OpPrint, $3, $5 ); }

    | Print '#' expr error
        {   expected(", "); }

    | Return ArrayName '\n'
        {   ePrintf( Syntax, "array values cannot be returned" ); }

    | Return ArrayName optBrackets '\n'
        {   ePrintf( Syntax, "array values cannot be returned" ); }

    | Return expr sep
        {   if (!inStack(blockStack,Function)) {
                ePrintf( Syntax, "Return outside Function");
            }
            $$ = opNode( OpReturnValue, $2, NULL ); }

    | Return sep
        {   if (!inStack(blockStack,Sub) &&
                !inStack(blockStack,Function)) {
                ePrintf( Syntax, "Return outside Sub or Function");
            }
            $$ = opNode( OpExitRoutine, NULL, NULL ); }

    | Select Case
        {   pushStack(blockStack,Select); }

      expr sep cases sep
        {   popStack(blockStack);
            $$ = opNode( OpCaseSelect, $4, $6 ); }


    | Select error
        {   expected( "Case" ); }

    | Shared
        {   if (currentScope == NULL) {
                ePrintf( Syntax, "Shared illegal outside Sub or Function");
            }
            pushStack(blockStack, (intptr_t)currentScope );
            currentScope = NULL; }
        sharedList sep
        {   currentScope = (Symbol *)popStack(blockStack);
            $$ = NULL; }

    | While
        {   pushStack(blockStack,While); }

      expr sep block sep
        {   popStack(blockStack);
            $$ = opNode( OpWhile, $3, $5 ); }

    | Do
	{
	pushStack(blockStack,Do);
	}
	sep block sep
	{
	    popStack(blockStack);
	    $$=opNode(OpDo,NULL, $4);
	}


    | lval Eq expr sep
        {   $1->right = $3;
            $$ = $1; }

    | lval IncrSelf expr sep
        {   /* simple var or array? */
            switch ($1->op) {
            case OpAssign:
                /* create a node to hold the operation */
                $1->right = opNode( $2,
                    symbolNode( OpVar, $1->value.symbol, NULL, NULL ), $3 );
                break;

            case OpArraySet:
                /* create a node to hold the operation */
                $1->right = opNode( $2,
                        symbolNode( OpArrayGet, $1->value.symbol, $1->left, NULL ),
                        $3 );
                break;

            default:
                ePrintf( Syntax, "IncrSelf: can't apply operation to %s",
                    $2, $1->value.symbol->name );
                break;
            }

            /* value to assign */
            $$ = $1; }

    /* obvious errors */

/*  old version
    | Undefined '('
        {   ePrintf( Syntax, "%s() is not defined", $1 ); }
*/

    | Undefined '('
        {   pushStack( argCountStack, 0 ); }

          argList sep
        {   Symbol *s = addSymbol( $1, NULL, SYM_FORWARD_SUB );
            s->forward = 1;
            s->code = NULL;
            s->args = popStack( argCountStack );
            free( $1 );

            $$ = symbolNode( OpFunctionCall, s, $4, NULL );
        }

    | sep
        {  $$ = NULL; }

    ;

/* Note: the value to be assigned to the LVAL is */
/* placed in the right node, not the left        */

lval:
      Undefined
        {   $$ = symbolNode( OpAssign, returnVar($1, SYM_VARIABLE, 0), NULL, NULL );
            free( $1 ); }

    | VariableName
        {   $$ = symbolNode( OpAssign, $1, NULL, NULL ); }

    | ArrayName '[' indexList
        { checkArgCount( $1, popStack( argCountStack ) );
          $$ = symbolNode( OpArraySet, $1, $3, NULL ); }

    | ArrayName error
        {   expected("'['"); }

    ;

sep:
      '\n'
    | ':'
    | error
        {   if (strcmp(currtok, "end-of-file") == 0 ) {
                checkBlockEnd(-1);
            }
            expected("end-of-line" ); }
    ;

eq:
      Eq
    | error
        {   expected("'='"); }
    ;

elseIf:

    ElseIf expr Then sep block elseIf
      { $$ = opNode( OpIf,
                opNode( OpIfTrue, $2, $5 ),
                $6 ); }

    |  Else sep block
      { $$ = $3; }

    | /* none */
      { $$ = NULL; }

    ;

cases:
     Case caseTests sep block cases
        { $$ = comma( comma( $2, $4 ), $5 ); }

    | Case Else sep block
        { $$ = comma(  comma( opNode( OpCaseElse, NULL, NULL ), $4 ),
                        NULL ); }

    | /* nothing */
        { $$ = NULL; }
    ;


caseTests:
      expr To expr caseTail
        { $$ = opNode( OpCaseRange, comma( $1, $3 ), $4 ); }

    | expr caseTail
        { $$ = intNode( OpCaseCmp, EQ, $1, $2 ); }

    | Is Eq expr caseTail
        { $$ = intNode( OpCaseCmp, EQ, $3, $4 ); }

    | Is Ne expr caseTail
        { $$ = intNode( OpCaseCmp, NE, $3, $4 ); }

    | Is Gt expr caseTail
        { $$ = intNode( OpCaseCmp, GT, $3, $4 ); }

    | Is Lt expr caseTail
        { $$ = intNode( OpCaseCmp, LT, $3, $4 ); }

    | Is Le expr caseTail
        { $$ = intNode( OpCaseCmp, LE, $3, $4 ); }

    | Is Ge expr caseTail
        { $$ = intNode( OpCaseCmp, GE, $3, $4 ); }

    ;

caseTail:
      ',' caseTests
        { $$ = $2; }

    | /* nothing */
        { $$ = NULL; }
    ;


expr:

    '(' expr ')'
        { $$ = $2; }

    /* precedence 1 */

    | expr '^' optSep expr
        { $$ = opNode( OpPower, $1, $4 ); }

    | '-' expr %prec UMinus
        { $$ = opNode( OpNegate, $2, NULL ); }


        /* precedence 2 */


    | expr '*' optSep expr
        { $$ = opNode( OpMul, $1, $4 ); }

    | expr '/' optSep expr
        { $$ = opNode( OpDiv, $1, $4 ); }

    | expr '\\' optSep expr
        { $$ = opNode( OpIDiv, $1, $4 ); }

    | expr '%' optSep expr
        { $$ = opNode( OpMod, $1, $4 ); }

    | expr Shl optSep expr
        { $$ = opNode( OpShl, $1, $4 ); }

    | expr Shr optSep expr
        { $$ = opNode( OpShr, $1, $4 ); }


        /* precedence 3 */


    | expr Mod optSep expr
        { $$ = opNode( OpMod, $1, $4 ); }

    | expr Inv optSep expr
        { $$ = opNode( OpInv, $1, $4 ); }


        /* precedence 4 */


    | expr '+' optSep expr
        { $$ = opNode( OpAdd, $1, $4 ); }

    | expr '&' optSep expr
        { $$ = opNode( OpConcat, $1, $4 ); }

    | expr '-' optSep expr
        { $$ = opNode( OpSub, $1, $4 ); }

    | expr '|' optSep expr
        { $$ = opNode( OpOrBits, $1, $4 ); }


        /* precedence 5 */


    | expr Eq optSep expr
        { $$ = intNode( OpCmp, EQ, $1, $4 ); }

    | expr Ne optSep expr
        { $$ = intNode( OpCmp, NE, $1, $4 ); }

    | expr Lt optSep expr
        { $$ = intNode( OpCmp, LT, $1, $4 ); }

    | expr Gt optSep expr
        { $$ = intNode( OpCmp, GT, $1, $4 ); }

    | expr Le optSep expr
        { $$ = intNode( OpCmp, LE, $1, $4 ); }

    | expr Ge optSep expr
        { $$ = intNode( OpCmp, GE, $1, $4 ); }


        /* precedence 6 */

    | Not expr
      { $$ = opNode( OpNot, $2, NULL ); }

    | '!' expr
      { $$ = opNode( OpNot, $2, NULL ); }


        /* precedence 7 */


    | expr And optSep expr
      { $$ = opNode( OpAnd, $1, $4 ); }


        /* precedence 8 */


    | expr Or optSep expr
      { $$ = opNode( OpOr, $1, $4 ); }


        /* precedence 9 */


    | expr Xor optSep expr
      { $$ = opNode( OpXor, $1, $4 ); }

    | expr In optSep ArrayName optBrackets
        {   $$ = symbolNode( OpIn, $4, $1, NULL ); }


        /* precedence 10 */


    | ClassName MethodName '('
        { pushStack( argCountStack, 0 ); }

        argList
        {   popStack( argCountStack );
            $$ = stringNode( OpClassMethod, $2,
                    symbolNode( OpComma, $1, NULL, NULL ), $5 ); }


    | ClassName MethodName
        {   $$ = stringNode( OpClassMethod, $2,
                    symbolNode( OpComma, $1, NULL, NULL ), NULL ); }

    | expr MethodName '('
        { pushStack( argCountStack, 0 ); }

        argList
        {   popStack( argCountStack );
            $$ = stringNode( OpMethod, $2, $1, $5 ); }

    | expr MethodName
        {   $$ = stringNode( OpMethod, $2, $1, NULL ); }


        /* lowest precedence */

    | New ClassName '('
        {   pushStack( argCountStack, 0 ); }

        argList
        {   popStack( argCountStack );
            $$ = symbolNode( OpNew, $2, $5, NULL ); }

    | New ClassName
        {   $$ = symbolNode( OpNew, $2, NULL, NULL ); }

    | New
        { expected("a Class"); }

    | ClassName '('
        {   if (!classSafeOnStack( $1->klass )) {
                ePrintf( Syntax, "Can't create %s on stack", $1->name );
            }
            pushStack( argCountStack, 0 ); }
        argList
        {   popStack( argCountStack );
            $$ = symbolNode( OpNewTmp, $1, $4, NULL ); }

    | ClassName
        {   expected("("); }

    | Undefined
        { $$ = symbolNode( OpVar, returnVar($1, SYM_VARIABLE, 0), NULL, NULL );
          free($1); }

    | VariableName
        { $$ = symbolNode( OpVar, $1, NULL, NULL ); }

    | ArrayName optBrackets
        { $$ = symbolNode( OpArrayPtr, $1, NULL, NULL ); }

    | ArrayName '[' indexList
        { int args = popStack( argCountStack );
          checkArgCount( $1, args );
          $$ = symbolNode( OpArrayGet, $1, $3, NULL ); }

    | ArrayName
        {   expected("'['"); }

    | ConstantName
        {   $$ = symbolNode( OpConstGet, $1, NULL, NULL ); }

    | Integer
        { $$ = intNode( OpInt, $1, NULL, NULL ); }

    | Float
        { $$ = floatNode( OpFloat, $1, NULL, NULL ); }

    | String
        { $$ = stringNode( OpString, $1, NULL, NULL ); }

    | BuiltinName '('
        { pushStack( argCountStack, 0 ); }

          argList
        { int args = popStack( argCountStack );
          checkArgCount( $1, args );
          $$ = symbolNode( OpBuiltin, $1, $4, NULL ); }

    | BuiltinName
        { checkArgCount( $1, 0 );
          $$ = symbolNode( OpBuiltin, $1, NULL, NULL ); }

    | BuiltinName error
        {   expected("'('"); }

    | FunctionName '('
        {   pushStack( argCountStack, 0 ); }
            argList

        {   int args = popStack( argCountStack );
            checkArgCount( $1, args );
            $$ = symbolNode( OpFunction, $1, $4, NULL ); }

    | FunctionName
        {   checkArgCount( $1, 0 );
            $$ = symbolNode( OpFunction, $1, NULL, NULL ); }

    | FunctionName error
        {   expected("'('"); }

    | ForwardFunctionName '('
        {   pushStack( argCountStack, 0 ); }
            argList

        {   int args = popStack( argCountStack );
            checkArgCount( $1, args );
            $$ = symbolNode( OpFunction, $1, $4, NULL ); }

    | ForwardFunctionName error
        {   expected("'('"); }

    | Undefined '('
        {   pushStack( argCountStack, 0 ); }
            argList

        {   Symbol *s = addSymbol( $1, NULL, SYM_FORWARD_FUNCTION );
            s->forward = 1;
            s->code = NULL;
            s->args = popStack( argCountStack );
            free( $1 );

            $$ = symbolNode( OpFunction, s, $4, NULL );
        }

    | error
        {   expected("an expression"); }
    ;

argList:
      ')'
        { $$ = NULL; }

    | argItems ')'
        { $$ = $1; }

    | argItems error
        {   expected("')'"); }
    ;

argItems:
      expr ',' optSep argItems
        { incrStack( argCountStack, 1 );
          $$ = comma( $1, $4 ); }

    | expr
        { incrStack( argCountStack, 1 );
          $$ = $1; }

    | error
        { expected("an expression"); }
    ;

subList:
      expr ',' optSep subList
        { incrStack( argCountStack, 1 );
          $$ = comma( $1, $4 ); }

    | expr
        { incrStack( argCountStack, 1 );
          $$ = $1; }

    | /* nothing */
        { $$ = NULL }
    ;


parmlist:
    | '(' ')'
    | '(' parmitem
    | /* nothing */
    ;

parmitem:
      Undefined '[' ']'
        { createParm( $1, SYM_ARRAY );
          free( $1 ); }
        parmtail

    | VariableName '[' ']'
        { createParm( $1->name, SYM_ARRAY ); }
        parmtail

    | ArrayName '[' ']'
        { createParm( $1->name, SYM_ARRAY ); }
        parmtail

    | Undefined
        { createParm( $1, SYM_VARIABLE );
          free( $1 ); }
        parmtail

    | VariableName
        { createParm( $1->name, SYM_VARIABLE ); }
        parmtail

    | ArrayName
        { createParm( $1->name, SYM_VARIABLE ); }
        parmtail

    | '.' '.' '.' ')'
        {   currentScope->optargs = NOPTARGS; }


    | /* nothing */
        { expected("a parameter name"); }
    ;

parmtail:
      ',' optSep parmitem
    | ')'
    | error
        { expected("')'"); }
    ;

loopTail:
      Eq expr To expr Step expr sep block
        { $$ = symbolNode( OpForStep, NULL,
                    comma( $2, comma($4, $6) ),
                    $8 ); }

    | Eq expr To expr Step expr sep block
        { $$ = symbolNode( OpForStep, NULL,
                    comma( $2, comma($4, $6) ),
                    $8 ); }

    | Eq expr To expr sep block
        { $$ = symbolNode( OpFor, NULL, comma( $2, $4 ), $6 ); }

    | Eq expr To expr sep block
        { $$ = symbolNode( OpFor, NULL, comma( $2, $4 ), $6 ); }

    | Eq expr To expr error
        { expected("Step"); }

    | Eq expr error
        { expected("To"); }

    | error
        { expected("'='"); }
    ;

printList:
      ';' printList
        { $$ = $2; }

    | ',' printList
        { $$ = intNode( OpPrintValue, PRINT_TAB, NULL, $2 ); }

    | expr ',' printList
        { $$ = intNode( OpPrintValue, PRINT_TAB, $1, $3 ); }

    | expr ';' printList
        { $$ = intNode( OpPrintValue, PRINT, $1, $3 ); }

    | expr
        { $$ = intNode( OpPrintValue, PRINT_NEWLINE, $1, NULL ); }

    | /* nothing */
        { $$ = NULL; }
    ;

indexList:
      { pushStack( argCountStack, 0 ); }
      indexListTail
        { int args = peekStack( argCountStack );
          $$ = comma( $2, intNode( OpInt, args, NULL, NULL ) ); }
    ;

/* place items on stack in fifo order */
indexListTail:
      expr ']'
        { incrStack( argCountStack, 1 );
          $$ = comma( $1, NULL ); }

    | expr ',' optSep indexListTail
        { incrStack( argCountStack, 1 );
          $$ = comma( $4, $1 ); }
    ;


dimList:
      dimItem ',' optSep dimList
        {   if ($1==NULL) {
                $$ = $4;
            } else if ($4==NULL) {
                $$ = $1;
            } else {
                $$ = comma( $1, $4 );
            } }

    | dimItem
        { $$ = $1; }
    ;

dimItem:
       Undefined '[' ']'
        { Symbol *s = createArraySymbol( $1, 0 );
          $$ = symbolNode( OpInitArray, s, NULL, NULL );
          free( $1 ); }

    | Undefined '[' dimIndexList
        { int args = popStack( argCountStack );
          Symbol *s = createArraySymbol( $1, args );
          $$ = symbolNode( OpInitArray, s, $3, NULL );
          free( $1 ); }

    | VariableName '[' ']'
        { Symbol *s = createArraySymbol( $1->name, 0 );
          $$ = symbolNode( OpInitArray, s, NULL, NULL ); }

    | VariableName '[' dimIndexList
        { int args = popStack( argCountStack );
          Symbol *s = createArraySymbol( $1->name, args );
          $$ = symbolNode( OpInitArray, s, $3, NULL ); }

    | ArrayName '[' ']'
        { Symbol *s = createArraySymbol( $1->name, 0 );
          $$ = symbolNode( OpInitArray, s, NULL, NULL ); }

    | ArrayName '[' dimIndexList
        { int args = popStack( argCountStack );
          Symbol *s = createArraySymbol( $1->name, args );
          $$ = symbolNode( OpInitArray, s, $3, NULL ); }

    | Undefined Eq expr
        {   $$ = symbolNode( OpAssign, returnVar($1, SYM_VARIABLE, 1), NULL, $3 );
            free( $1 ); }

    | Undefined
        {   returnVar($1, SYM_VARIABLE, 1);
            free( $1 );
            $$ = NULL; }

    | VariableName Eq expr
        {   $$ = symbolNode( OpAssign, returnVar($1->name, SYM_VARIABLE, 1), NULL, $3 ); }

    | VariableName
        {   returnVar($1->name, SYM_VARIABLE, 1);
            $$ = NULL; }

    | ArrayName Eq expr
        {   $$ = symbolNode( OpAssign, returnVar($1->name, SYM_VARIABLE, 1), NULL, $3 ); }

    | ArrayName
        {   returnVar($1->name, SYM_VARIABLE, 1);
            $$ = NULL; }

    | error
        {   expected("a name"); }
    ;

/* expr To expr | expr */
dimIndexList:
      { pushStack( argCountStack, 0 ); }
      dimIndexItems
        { int args = peekStack( argCountStack );
          $$ = comma( $2, intNode( OpInt, args, NULL, NULL ) ); }
    ;

dimIndexItems:
      expr ']'
        { incrStack( argCountStack, 1 );
          $$ = comma( $1, intNode( OpInt, 0, NULL, NULL) ); }

    | expr To expr ']'
        { incrStack( argCountStack, 1 );
          $$ = comma( $3, $1 ); }

    | expr To expr ',' optSep dimIndexItems
        { incrStack( argCountStack, 1 );
          $$ = comma( $6, comma( $3, $1) ); }

    | expr ',' optSep dimIndexItems
        { incrStack( argCountStack, 1 );
          $$ = comma( $4, comma( $1, intNode( OpInt, 0, NULL, NULL)) ); }
    ;


sharedList:
      sharedItem ',' optSep sharedList
    | sharedItem
    ;

sharedItem:
      VariableName
        {   if ($1->scope != NULL) {
                ePrintf( Syntax, "Can't share local variable %s", $1->name );

            } else if (inStack(sharedStack,(int)$1)) {
                ePrintf( Syntax, "Variable %s is already shared", $1->name );

            } else {
                pushStack( sharedStack, (int)$1 );

            } }


    | ArrayName '[' ']'
        {   if ($1->scope != NULL) {
                ePrintf( Syntax, "Can't share local array %s", $1->name );

            } else if (inStack(sharedStack,(int)$1)) {
                ePrintf( Syntax, "Array %s is already shared", $1->name );

            } else {
                pushStack( sharedStack, (int)$1 );

            } }

    | ArrayName '[' error
        {   expected("']'"); }

    | ArrayName error
        {   expected("'['"); }

    | error
        {   expected("a variable name"); }
    ;


declaredList:
    | '(' ')'
    | '(' declaredItem
    | /* nothing */
    ;


declaredItem:
      ')'

    | VariableName ')'
        {   incrStack( argCountStack, 1 );
            if ($1->stackPos != peekStack(argCountStack) ) {
                ePrintf( Syntax, "variable %s does not match declaration", $1->name);
            }
	}

    | VariableName ',' optSep
        {   incrStack( argCountStack, 1 );
            if ($1->stackPos != peekStack(argCountStack) ) {
                ePrintf( Syntax, "variable %s does not match declaration", $1->name);
            } }
        declaredItem

    | VariableName error
        {   ePrintf( Syntax, "parm list does not match declaration" ); }


    | ArrayName '[' ']' ')'
        {   incrStack( argCountStack, 1 );
            if ($1->stackPos != peekStack(argCountStack) ) {
                ePrintf( Syntax, "array %s does not match declaration", $1->name);
            } }

    | ArrayName '[' ']' ',' optSep
        {   incrStack( argCountStack, 1 );
            if ($1->stackPos != peekStack(argCountStack) ) {
                ePrintf( Syntax, "array %s does not match declaration", $1->name);
            } }
        declaredItem

    | ArrayName '[' ']' error
        {   ePrintf( Syntax, "parm list does not match declaration" ); }


    | ArrayName '[' error
        {   expected("']'"); }

    | ArrayName error
        {   expected("'['"); }

    | '.' '.' '.' ')'
        {   if (currentScope->optargs != NOPTARGS) {
                ePrintf( Syntax, "... does not match declaration" );
            }
	}
    | error
        {   ePrintf( Syntax, "parm list does not match declaration" ); }

    ;


optSep:
      '\n'
    | /* nothing */
    ;


optBrackets
    :   /* nothing */
    |   '[' ']'
    ;

fileMode:
      Input
        { $$ = FILE_MODE_INPUT; }

    | Output
        { $$ = FILE_MODE_OUTPUT; }

    | Append
        { $$ = FILE_MODE_APPEND; }

    | error
        {   expected("a file mode: Input, Output or Append"); }
    ;

constList:
      constItem ',' optSep constList
        {   if ($4 == NULL) {
                $$ = $1;
            } else {
                $$ = comma( $1, $4 );
            }
        }

    | constItem
        { $$ = $1; }
    ;

constItem:
      Undefined Eq expr
        {   $$ = symbolNode( OpConstSet, createConst( $1 ), $3, NULL );
            free( $1 ); }

    | Undefined error
        {   expected("'='"); }

    | error
        {   ePrintf( Syntax, "duplicate definition"); }
    ;

fileHandle
    : '#' expr
        {   $$ = $2; }
    | expr
        {   $$ = $1; }
    ;
