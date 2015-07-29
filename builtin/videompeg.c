//_______________________________________________________________________________________________________________________
//
// Video mpeg
//_________________________________________________________________________________________________________________________

//loadmpeg(fname,usesound)		: load a mpeg video

void basLoadMpeg()
{
    char *fname;
    int usesound;
    int ret;

    usesound=popNumber();
    fname=popString();

    ret=loadmpeg(fname,usesound);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//plaympeg(optional loop)		: play a mpeg1 video
void basPlayMpeg()
{
    int loop;
    int ret;

    if (argCount==1)
	loop=popNumber();
    else
	loop=0;

    ret=plaympeg(loop);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//stopmpeg()				: terminate the video play
void basStopMpeg()
{
    int ret;
    ret=stopmpeg();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//deletempeg()				: unload mpeg video
void basDeleteMpeg()
{
    int ret;
    ret=deletempeg();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//pausempeg()				: Pause/Resume playback of an SMPEG object
void basPauseMpeg()
{
    int ret;
    ret=pausempeg();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//rewindmpeg()				: Rewind the play position of an SMPEG object to the beginning of the MPEG
void basRewindMpeg()
{
    int ret;
    ret=rewindmpeg();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}

//_________________________________________________________________________________________________________________________

//seekmpeg(p)				: Seek 'bytes' bytes in the MPEG stream
void basSeekMpeg()
{
    int p;
    int ret;
    p=popNumber();
    ret=seekmpeg(p);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}

//_________________________________________________________________________________________________________________________

//skipmpeg(s)				: Skip 'seconds' seconds in the MPEG stream
void basSkipMpeg()
{
    double p;
    int ret;
    p=popNumber();
    ret=skipmpeg(p);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_________________________________________________________________________________________________________________________

//statusmpeg()				: return 1 if plaympeg work or 0 in other case
void basStatusMpeg()
{
    int ret;
    ret=statusmpeg();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
