// CD support
//_________________________________________________________________________________________________________________________

//numdrivescd() 				: returns the number of cd-rom drives on the system.
void basNumDrivesCD()
{
    int ret;
    ret=numdrivescd();

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//namecd(drive)				: returns a human-readable, system-dependent identifier for the cd-rom.
void basNameCD()
{
    int drive;
    int ret;

    char name[255];
    strcpy(name,"      ");
    drive=popNumber();
    ret=namecd(name,drive);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushString(name);

}
//_______________________________________________________________________________________________________________________

//opencd(n,drive)				: opens a cd-rom drive for access.
void basOpenCD()
{
    int n,drive;
    int ret;

    drive=popNumber();

    if (argCount==2)
	n=popNumber();
    else
	n=-1;

    ret=opencd(n,drive);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//indrivecd(n)				: return 1 if cd is in driver
void basInDriveCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=indrivecd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//trackscd(n) 				: return the number of tracks in cd
void basTracksCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=trackscd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//curtrackcd(n)				: return the current track in cd
void basCurTrackCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=curtrackcd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//curframecd(n)				: return the current frame in cd
void basCurFrameCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=curframecd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//playcd(n,s,l) 				: play a cd
void basPlayCD()
{
    int n,s,l;
    int ret;

    if (argCount==3)
	l=popNumber();
    else
	l=0;

    if (argCount>=2)
	s=popNumber();
    else
	s=0;

    n=popNumber();

    ret=playcd(n,s,l);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//playtrackscd(n,trk1,fr1,ntrks,nfrs)	: play the given cd track(s)0=all
void basPlayTracksCD()
{
    int n,trk1,fr1,ntrks,nfrs;
    int ret;

    switch(argCount){
	case 5:
	    nfrs=popNumber();
	    ntrks=popNumber();
	    fr1=popNumber();
	    trk1=popNumber();
	    n=popNumber();
	    break;
	case 4:
	    ntrks=popNumber();
	    fr1=popNumber();nfrs=1;
	    trk1=popNumber();
	    n=popNumber();
	    break;
	case 3:
	    nfrs=0;
	    ntrks=popNumber();
	    fr1=0;
	    trk1=popNumber();
	    n=popNumber();
	    break;
	case 2:
	    nfrs=0;
	    fr1=0;
	    trk1=popNumber();ntrks=1;
	    n=popNumber();
	default:
	    nfrs=0;
	    ntrks=0;
	    fr1=0;
	    trk1=0;
	    n=popNumber();
	    break;
    }

    ret=playtrackscd(n,trk1,fr1,ntrks,nfrs);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//pausecd(n) 				: pauses a cdrom
void basPauseCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=pausecd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//resumecd(n) 				: resumes a cdrom
void basResumeCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=resumecd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//stopcd(n)				: stops a cdrom
void basStopCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=stopcd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//ejectcd(n) 				: ejects a cdrom
void basEjectCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=ejectcd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//closecd(n) 				: closes a cd handle
void basCloseCD()
{
    int n;
    int ret;

    n=popNumber();

    ret=closecd(n);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//tracktypecd(n,t)			: return SDL_AUDIO_TRACK(0...) or SDL_DATA_TRACK(1...)
void basTrackTypeCD()
{
    int n,t;
    int ret;

    t=popNumber();
    n=popNumber();

    ret=tracktypecd(n,t);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//tracklengthcd(n,t)			: return the length of track t
void basTrackLengthCD()
{
    int n,t;
    int ret;

    t=popNumber();
    n=popNumber();

    ret=tracklengthcd(n,t);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//trackoffsetcd(n,t)			: return the offset to the beginning of this track in frames
void basTrackOffsetCD()
{
    int n,t;
    int ret;

    t=popNumber();
    n=popNumber();

    ret=trackoffsetcd(n,t);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
