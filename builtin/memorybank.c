
//_______________________________________________________________________________________________________________________

//Memory Bank
//_________________________________________________________________________________________________________________________

//reservebank(bank,size)			: make a raw memory bank. there are 256 bank ( 0 - 255)
void basReserveBank()
{
    int bank;
    long size;
    int ret;

    size=popNumber();
    bank=popNumber();

    ret=reservebank(bank,size);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//baseimage(bank,image)			: link a  memory bank with image bitmap
void basBaseImage()
{
    int bank;
    int image;
    int ret;

    image=popNumber();
    bank=popNumber();

    ret=baseimage(bank,image);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//baseimageCC(bank,image)			: link a  memory bank with image bitmap
void basBaseImageCC()
{
    int bank;
    int imageCC;
    int ret;

    imageCC=popNumber();
    bank=popNumber();

    ret=baseimageCC(bank,imageCC);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//basescreen(bank,image)			: link a  memory bank with image bitmap
void basBaseScreen()
{
    int bank;
    int screen;
    int ret;

    screen=popNumber();
    bank=popNumber();

    ret=basescreen(bank,screen);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//basesound(bank,sound)			: link a  memory bank with soundb bank
void basBaseSound()
{
    int bank;
    int sound;
    int ret;

    sound=popNumber();
    bank=popNumber();

    ret=basesound(bank,sound);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//freebase(bank)				: disconnect a base from bank
void basFreeBase()
{
    int bank;
    int ret;

    bank=popNumber();

    ret=freebase(bank);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//freebank(bank)				: destroy a memory bank
void basFreeBank()
{
    int bank;
    int ret;

    bank=popNumber();

    ret=freebank(bank);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//copybank(s,d)				: copy the banco s in d
void basCopyBank()
{
    int s,d;
    int ret;

    d=popNumber();
    s=popNumber();

    ret=copybank(s,d);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);

}

//_______________________________________________________________________________________________________________________

//loadbank(filename,optional bank)	: load a file in memory bank (if omitted the current )
void basLoadBank()
{
	char	*filename;
	int bank;

	int ret;

    if (argCount==2)
	bank = popNumber();
    else
	bank=-1;

    filename=popString();
    ret =loadbank(filename,bank);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "%s not found Error\n", filename );
    pushNumber(ret);

}

//_______________________________________________________________________________________________________________________

//savebank(filename,optional bank)	: save memory bank in a file
void basSaveBank()
{
	char	*filename;
	int bank;

	int ret;

    if (argCount==2)
	bank = popNumber();
    else
	bank=-1;

    filename=popString();
    ret =savebank(filename,bank);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "%s not found Error\n", filename );
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//setbank(optional bank)			: set the current bank
void basSetBank()
{
    int bank;
    int ret;

    if (argCount==1)
	bank=popNumber();
    else
	bank=-1;

    ret=setbank(bank);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//sizebank(optional bank)			: return the bank memory size
void basSizeBank()
{
    int bank;
    int ret;

    if (argCount==1)
	bank=popNumber();
    else
	bank=-1;

    ret=sizebank(bank);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//poke(optional bank,address,value)	: write a byte value in memory bank at specific address
void basPoke()
{
    int bank;
    long address;
    unsigned char value;
    int ret;


    value=popNumber();
    address=popNumber();

    if (argCount==3)
	bank = popNumber();
    else
	bank=-1;

    ret=poke(bank,address,value);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//doke(optional bank,address,value)       : write a 16bit value in memory bank at specific address
void basDoke()
{
    int bank;
    long address;
    unsigned short value;
    int ret;


    value=popNumber();
    address=popNumber();

    if (argCount==3)
	bank = popNumber();
    else
	bank=-1;

    ret=doke(bank,address,value);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//loke(optional bank,address,value)	: write a 32bit value in memory bank at specific address
void basLoke()
{
    int bank;
    long address;
    unsigned int value;
    int ret;


    value=popNumber();
    address=popNumber();

    if (argCount==3)
	bank = popNumber();
    else
	bank=-1;

    ret=loke(bank,address,value);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//peek(optional bank,address)		: read a byte value in memory bank at specific address
void basPeek()
{
    int bank;
    long address;
    int ret;


    address=popNumber();
    if (argCount==2)
	bank = popNumber();
    else
	bank=-1;

    ret=peek(bank,address);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}

//_______________________________________________________________________________________________________________________

//deek(optional bank,address)		: read a 16bit value in memory bank at specific address
void basDeek()
{
    int bank;
    long address;
    int ret;


    address=popNumber();
    if (argCount==2)
	bank = popNumber();
    else
	bank=-1;

    ret=deek(bank,address);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//leek(optional bank,address)		: read a 32bit value in memory bank at specific address
void basLeek()
{
    int bank;
    long address;
    int ret;


    address=popNumber();
    if (argCount==2)
	bank = popNumber();
    else
	bank=-1;

    ret=leek(bank,address);
    if (ret==-1) ePrintf( Runtime, "membank Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//memcopy(sbank,s,dbank,d,size)		: copy a part of bank memory s in d
void basMemCopy()
{
    int sbank,s,dbank,d,size;
    int ret;

    size=popNumber();
    d=popNumber();
    dbank=popNumber();
    s=popNumber();
    sbank=popNumber();

    ret=memcopy(sbank,s,dbank,d,size);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
