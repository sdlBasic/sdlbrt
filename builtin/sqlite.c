void basSqlOpen()
{
	char	*filename;
	int n;
	int ret;

    if (argCount==1)
	n=-1;
    else
	 n = popNumber();
    filename=popString();


    ret=wrapsqlopen(filename, n);

	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "SQL Error \n");
    pushNumber(ret);

}
void basSqlClose()
{
	int n;
	int ret;

	n = popNumber();

   ret=wrapsqlclose( n);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlPrepare()
{
	char	*sql;
	int n,pnum;
	int ret;

   sql = popString();
	pnum = popNumber();
	n = popNumber();

   ret=wrapsqlprepare( n, pnum, sql);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlFinalize()
{
	int n;
	int ret;

	n = popNumber();

   ret=wrapsqlfinalize( n);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlStep()
{
	int n;
	int ret;

	n = popNumber();

   ret=wrapsqlstep( n);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlGetRows()
{
	int n;
	int ret;

	n = popNumber();

   ret=wrapsqlrows(n);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlGetColumns()
{
	int n;
	int ret;

	n = popNumber();

   ret=wrapsqlcolumns(n);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}
void basSqlGetText()
{
	int n,col;

	col = popNumber();
	n = popNumber();

   pushStringCopy( wrapsqlcoltext(n, col) );

}
void basSqlGetImage()
{
	int n, col, imageslot;
	int ret;

	imageslot = popNumber();
	col = popNumber();
	n = popNumber();

   ret=wrapsqlimage(n, col, imageslot);

   if (ret==-1) ePrintf( Runtime, "SQL Error \n");
   pushNumber(ret);

}

