//_______________________________________________________________________________________________________________________
//
//------- SDLengine-link ------------------------------------------------------------------------------------------
//_______________________________________________________________________________________________________________________

//_________________________________________________________________________________________________________________________
//
//Screen
//_________________________________________________________________________________________________________________________

//setdefaults(w,h,bpp,m): : open the display, perform initializations on cursor and fonts and sets default values on sprites, bobs and screens system.
void basSetDefaults()
{
    int width,height,bpp,mode;
    int ret;

    mode = popNumber();
    bpp = popNumber();
    height = popNumber();
    width = popNumber();

    ret=setdefaults( width,height,bpp,mode);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//setdisplay(w,h,bpp,m): open the screen/window in double buffer. 0=screen|1=window|2=resizable
void basSetDisplay()
{
    int width,height,bpp,mode;
    int ret;

    mode = popNumber();
    bpp = popNumber();
    height = popNumber();
    width = popNumber();

    ret=setdisplay( width,height,bpp,mode);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________
//setalphachannel(v): activate deactivate alpha channel trasparency
void basSetAlphaChannel()
{
    int ret;
    int v;
    v=popNumber();
    ret=setalphachannel(v);
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//setcaption: change the display window title
void basSetCaption()
{
    int ret;
    char *title;

    title=popString();
    ret=setcaption(title);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
    eFree(title);
}
//_______________________________________________________________________________________________________________________

//caption: return the current display window title
void basCaption()
{
    char *title;
    caption(&title);
    pushString(title);
}
//_______________________________________________________________________________________________________________________

//SystemWidth: return the native screen width
void basSystemWidth()
{
    pushNumber( systemwidth() );
}
//_______________________________________________________________________________________________________________________

//systemheight: return the native screen height

void basSystemHeight()
{
    pushNumber( systemheight() );
}
//_______________________________________________________________________________________________________________________

//displaymode: give the display mode
void basDisplayMode()
{
    pushNumber( displaymode() );
}
//_______________________________________________________________________________________________________________________

//displaywidth: give the display width
void basDisplayWidth()
{
    pushNumber( displaywidth() );
}
//_______________________________________________________________________________________________________________________

//displayheight: give the display height
void basDisplayHeight()
{
    pushNumber( displayheight() );
}
//_______________________________________________________________________________________________________________________

//displaybpp: give the display color depth
void basDisplayBpp()
{
    pushNumber( displaybpp() );
}
//_______________________________________________________________________________________________________________________

//screen(n): attivated the logic screen n
void basScreen()
{
    int n;
    int ret;
    if (argCount!=0)
	    n = popNumber();
    else
	    n=-1;
    if (n>7)ePrintf( Runtime, "SDLengine  Error:you can use 0 to 7 screen !!! \n");
    ret=screen(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenz(n,z)				: set the zorder position of screen if z =-1 report actual z position
void basScreenZ()
{
    int n,z;
    int ret;
    if (argCount!=1)
	    z = popNumber();
    else
	    z=-1;
    n = popNumber();

    if (n>7)ePrintf( Runtime, "SDLengine  Error:you can use 0 to 7 screen !!! \n");
    ret=screenz(n,z);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//lastscreen: return the last screen open
void basLastScreen()
{
    int ret;
    ret=lastscreen();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//directscreen: direct drawing on display like a screen(more fast but sprite and offset does not works)
void basDirectScreen()
{
    int ret;
    ret=directscreen();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenopen(n,w,h,dx,dy,dw,dh,flag): open the logic screen n of dimension w,h in display coordinates dx,dy,dw,dh
void basScreenOpen()
{
    int n,w,h,dx,dy,dw,dh,flag;
    int ret;

    flag = popNumber();
    dh = popNumber();
    dw = popNumber();
    dy = popNumber();
    dx = popNumber();
     h = popNumber();
     w = popNumber();
     n = popNumber();

    if (n>7)ePrintf( Runtime, "SDLengine  Error:you can use 0 to 7 screen !!! \n");
    ret=screenopen(n,w,h,dx,dy,dw,dh,flag);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenclose(n): close the logic screen n
void basScreenClose()
{
    int n;
    int ret;

    n = popNumber();

    ret=screenclose(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screenclone(n,s,x,y,w,h,flag): create a  new viewport in logic screen s
void basScreenClone()
{
    int ret;
    int n,s,x,y,w,h,flag;

    flag = popNumber();
    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();
    s = popNumber();
    n = popNumber();

    if (n>7)ePrintf( Runtime, "SDLengine Error:you can use 0 to 7 screen !!! \n");
    ret=screenclone(n,s,x,y,w,h,flag);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screencopy(n,x,y,w,h,nd,xd,yd): copy a portion of screen n in a screen nd
void basScreenCopy()
{
    int n,x,y,w,h,nd,xd,yd;
    int ret;

    yd = popNumber();
    xd = popNumber();
    nd = popNumber();
    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();
    n = popNumber();

    if (n>7 || n<0)ePrintf( Runtime, "SDLengine Error: Error:you can use 0 to 7 screen !!! \n");
    if (nd>7 || nd<0)ePrintf( Runtime, "SDLengine Error: Error:you can use 0 to 7 screen !!! \n");
    ret=screencopy(n,x,y,w,h,nd,xd,yd);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screenfade(n,t): fade the screen n in t time
void basScreenFade()
{
    int n,t;
    int ret;

    if (argCount==2)
	t = popNumber();
    else
	t=-1;

    n = popNumber();

    ret=screenfade(n,t);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screenfadein(n,i,t): fade the screen n to image i in t time
void basScreenFadein()
{
    int n,i,t;
    int ret;

    if (argCount ==3){
	t = popNumber();
	i = popNumber();
    }else{
	t=-1;
	i=-1;
    }
    n = popNumber();

    ret=screenfadein(n,i,t);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screencrossfade(n,i,t): fade the screen n from current screen  to image i in t time
void basScreenCrossFade()
{
    int n,i,t;
    int ret;

    if (argCount ==3){
	t = popNumber();
	i = popNumber();
    }else{
	t=-1;
	i=-1;
    }
    n = popNumber();

    ret=screencrossfade(n,i,t);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//screenalpha(n,a): set alpha(trasparency) of screen n
void basScreenAlpha()
{
	int ret;
	int n,a;
    a = popNumber();
    n = popNumber();
    ret=screenalpha(n,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenlock(n): lock the  screen n for direct graphics access
void basScreenLock()
{
	int ret;
	int n;
     n = popNumber();
    ret=screenlock(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenunlock(n): unlock the  screen n for direct graphics access
void basScreenUnlock()
{
	int ret;
	int n;
     n = popNumber();
    ret=screenunlock(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//screenrect(x,y,w,h,flag): change the display output coordinates of the current screen
void basScreenRect()
{
    int x,y,w,h,flag;

    flag = popNumber();
    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber(screenrect(x,y,w,h,flag));
}
//_______________________________________________________________________________________________________________________

//xscreenrect: give the x coordinate of current screen viewport
void basXScreenRect()
{
    pushNumber( xscreenrect() );
}
//_______________________________________________________________________________________________________________________

//yscreenrect: give the y coordinate of current screen viewport
void basYScreenRect()
{
    pushNumber( yscreenrect() );
}
//_______________________________________________________________________________________________________________________

//wscreenrect: give the w value of current screen viewport
void basWScreenRect()
{
    pushNumber( wscreenrect() );
}
//_______________________________________________________________________________________________________________________

//hscreenrect: give the h value of current screen viewport
void basHScreenRect()
{
    pushNumber( hscreenrect() );
}
//_______________________________________________________________________________________________________________________

//flagscreenrect: give the flag value of current screen viewport
void basFlagScreenRect()
{
    pushNumber( flagscreenrect() );
}
//_______________________________________________________________________________________________________________________

//screenwidth: give the current screen width
void basScreenWidth()
{
    pushNumber( screenwidth() );
}
//_______________________________________________________________________________________________________________________

//screenheight: give the current screen height
void basScreenHeight()
{
    pushNumber( screenheight() );
}
//_______________________________________________________________________________________________________________________

//offset(x,y): set the logical current screen position
void basOffset()
{
    int xoff,yoff;

    yoff = popNumber();
    xoff = popNumber();
    offset(xoff,yoff);

    pushNumber( 0 );
}
//_______________________________________________________________________________________________________________________

//xoffset: give the x coordinate offset in current screen
void basXOffset()
{
    pushNumber( xoffset() );
}
//_______________________________________________________________________________________________________________________

//yoffset: give the y coordinate offset in current screen
void basYOffset()
{
    pushNumber( yoffset() );
}
//_______________________________________________________________________________________________________________________

//cls: clear the current logic screen
void basCls()
{
    pushNumber( cls() );
}
//_______________________________________________________________________________________________________________________

//screenswap: update display,bobsystem,spritesystem
void basScreenSwap()
{
    int ret;
    ret= screenswap();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//autoback setautoback(m): enable / disable automatic screenswap  m=0 disable m>0 wait m milliseconds and perform screenswap m<0 perform the invocate in code screenswap after m milliseconds
void basAutoBack()
{
    int m;
    if (argCount==1)
	    m=popNumber();
    else
	    m=-1;
    pushNumber(autoback(m));
}
//_______________________________________________________________________________________________________________________

//dualplayfield(m): set/unset automatic update of a screen upper sprite
void basDualPlayfield()
{
    int m;
	if (argCount==1)
		m=popNumber();
	else
		m=-1;

    pushNumber(dualplayfield(m));
}
//_______________________________________________________________________________________________________________________

//waitvbl: wait automatic screenswap
void basWaitVbl()
{
	int ret;

    ret= waitvbl();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//fps(n): set/unset or give the current frame rate counter
void basFps()
{
    int n;
	if (argCount==1)
		n=popNumber();
	else
		n=-1;

    pushNumber(fps(n));
}
//_______________________________________________________________________________________________________________________

//_________________________________________________________________________________________________________________________
//
//Graphics
//_________________________________________________________________________________________________________________________

//rgb(r,g,b): give current color in Uint32 format
void basRgb()
{
	int r,g,b;
    b = popNumber();
    g = popNumber();
    r = popNumber();

    pushNumber( rgb(r,g,b) );
}
//_______________________________________________________________________________________________________________________

//enablepalette(optional state=0|1 disable|enable|check)   			: enable disable and check the palettemode in 8 bit display
void basEnablePalette()
{
    int s;
    int ret;
    if (argCount==1)
	s=popNumber();
    else
	s=-1;
    ret=enablepalette(s);
    if (ret==-1) ePrintf( Runtime, "enablepalette Error\n");
    pushNumber(ret );

}

//_______________________________________________________________________________________________________________________

//color (c,optional v): set  palette color c with value v se missing give the current color c
void basColor()
{
	int c,v;
	int ret;
    if (argCount==2)
	v=popNumber();
    else
	v=-1;
    c=popNumber();

    ret=color(c,v);

    if (ret==-1) ePrintf( Runtime, "%s color Error\n", c );
    pushNumber(ret );
}
//_______________________________________________________________________________________________________________________

//palette(optional 0-255 param): set all palettes color
void basPalette()
{
	int i,v;
	int ret;
    ret=-1;
    for (i=0;i<argCount;i++){
	v=popNumber();
	ret=color(argCount-i-1,v);
	if (ret==-1)break;
    }
    pushNumber(ret );
}
//_______________________________________________________________________________________________________________________

//colorcycling(s,e,d=0|1)			: move the palettecolor one color forward or back work only in 8bit display
void basColorCycling()
{
    int s,e,d,delay;
    int ret;

    switch(argCount){
	case 4:
	    delay=popNumber();
	    d=popNumber();
	    e=popNumber();
	    s=popNumber();
	    break;

	case 3:
	    delay=0;
	    d=popNumber();
	    e=popNumber();
	    s=popNumber();
	    break;

	default:
	    delay=0;
	    d=0;
	    e=0;
	    s=-1;
	    break;
    }
    ret=colorcycling(s,e,d,delay);
    pushNumber(ret );
}
//_______________________________________________________________________________________________________________________

//ink(c): select the current color in Uint32 format
void basInk()
{
	int c;
    if (argCount==1)
	c=popNumber();
    else
	    c=-1;
    pushNumber( ink(c) );
}
//_______________________________________________________________________________________________________________________

//point(x,y)				: give the color of x,y point
void basPoint()
{
	int x,y;
    y = popNumber();
    x = popNumber();

    pushNumber( point(x,y) );
}
//_______________________________________________________________________________________________________________________

//dot(x,y): write x,y point with a current color
void basDot()
{
	int x,y;
    y = popNumber();
    x = popNumber();

    pushNumber( dot(x,y) );
}
//_______________________________________________________________________________________________________________________

//plot(x,y,c): write x,y point with a c color
void basPlot()
{
	int x,y,c;
    c = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( dot_ex(x,y,c) );
}
//_______________________________________________________________________________________________________________________

//line(x,y,x1,y1): write a line
void basLine()
{
	int x,y,x1,y1;
    y1 = popNumber();
    x1 = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( line(x,y,x1,y1) );
}
//_______________________________________________________________________________________________________________________

//box(x,y,x1,y1): write a empty rettangle
void basBox()
{
	int x,y,x1,y1;
    y1 = popNumber();
    x1 = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( box(x,y,x1,y1) );
}
//_______________________________________________________________________________________________________________________

//bar(x,y,x1,y1): write a fill rettangle
void basBar()
{
	int x,y,x1,y1;
    y1 = popNumber();
    x1 = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( bar(x,y,x1,y1) );
}
//_______________________________________________________________________________________________________________________

//rectangle(x,y,w,h,mode)			: write a rettangle w and h are the sizes mode=0 empty 1=filled
void basRectangle()
{
	int x,y,x1,y1,mode;
    if
	(argCount==4)mode=0;
    else
	mode = popNumber();
    y1 = popNumber();
    x1 = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( rectangle(x,y,x1,y1,mode) );
}

//_______________________________________________________________________________________________________________________

//circle(x,y,r): write a circle
void basCircle()
{
	int x,y,r;
    r = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( circle(x,y,r) );
}
//_______________________________________________________________________________________________________________________

//fillcircle(x,y,r): write a fill circle
void basFillCircle()
{
	int x,y,r;
    r = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( fillcircle(x,y,r) );
}
//_______________________________________________________________________________________________________________________

//ellipse(x,y,rx,ry): write a ellipse
void basEllipse()
{
	int x,y,rx,ry;
    ry = popNumber();
    rx= popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( ellipse(x,y,rx,ry) );
}
//_______________________________________________________________________________________________________________________

//fillellipse(x,y,rx,ry): write a fill ellipse
void basFillEllipse()
{
	int x,y,rx,ry;
    ry = popNumber();
    rx = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( fillellipse(x,y,rx,ry) );
}
//_______________________________________________________________________________________________________________________

//paint(x,y): fill a close area
void basPaint()
{
	int x,y;
    y = popNumber();
    x = popNumber();

    pushNumber(paint(x,y) );
}
//_______________________________________________________________________________________________________________________

//triangle(x1,y1,x2,y2,x3,y3): draw a fill triangle
void basTriangle()
{
	int x1,y1,x2,y2,x3,y3;
    y3 = popNumber();
    x3 = popNumber();
    y2 = popNumber();
    x2 = popNumber();
    y1 = popNumber();
    x1 = popNumber();

    pushNumber( triangle(x1,y1,x2,y2,x3,y3));
}
//_______________________________________________________________________________________________________________________
//polyline(x,y,x1,y1,x2,y2,.....): make a perimeter of a polygon
void basPolyLine()
{
    int i,x,y,xfirst,yfirst,xold,yold,count;

    count=argCount;
    yold = popNumber();
    xold = popNumber();
    xfirst=xold;
    yfirst=yold;

    for(i=0;i<(count/2)-1;i++){
	y = popNumber();
	x = popNumber();
	line(xold,yold,x,y);
	yold=y;
	xold=x;
    }
    line(xold,yold,xfirst,yfirst);

    pushNumber(0);
}
//_______________________________________________________________________________________________________________________

//polygon(x,y,x1,y1,x2,y2,.....): make a fill polygon
void basPolyGon()
{
    int i,xa,ya,xb,yb,xfirst,yfirst,count;
    count=argCount;

    ya = popNumber();
    xa = popNumber();
    yfirst=ya;
    xfirst=xa;
    for(i=0;i<(count/2)-1;i++){
	yb = popNumber();
	xb = popNumber();
	triangle(xfirst,yfirst,xa,ya,xb,yb);
	xa=xb;
	ya=yb;
    }

    pushNumber(0);
}

//_______________________________________________________________________________________________________________________
//
//graphics input output
//_________________________________________________________________________________________________________________________

//loadimage(filename,optional n): load a graphics file in a slot n return n
void basLoadImage()
{
	char	*filename;
	int n;
	int ret;

	if (argCount==1)
		n=-1;
	else
		n = popNumber();

    filename=popString();
    ret =loadimage(filename,n);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "%s not found Error\n", filename );
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//loadzipimage(zipfile,filename,optional n): load a graphics file in a slot n return n
void basLoadZipImage()
{
	char	*zipfile;
	char	*filename;
	int n;
	int ret;

	if (argCount==2)
		n=-1;
	else
		n = popNumber();

    filename=popString();
    zipfile=popString();

    ret =loadzipimage(zipfile,filename,n);


    if (ret==-1) ePrintf( Runtime, "%s not found Error\n", filename );
    pushNumber(ret);

    eFree(filename);
    eFree(zipfile);

}
//_______________________________________________________________________________________________________________________

//saveimage(filename,n): save slot n in a graphics file(only bmp)
void basSaveImage()
{
	char	*filename;
	int n;

	int ret;

    n = popNumber();
    filename=popString();

    ret= saveimage(filename,n);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//loadsound(filename,n): load a wave file in a sound slot n
void basLoadSound()
{
	char	*filename;
	int n;
	int ret;

    if (argCount==1)
	n=-1;
    else
	n = popNumber();

    filename=popString();

    ret=loadsound(filename,n);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//loadzipsound(zipfile,filename,n): load a zipped wave file in a sound slot n
void basLoadZipSound()
{
	char	*zipfile;
	char	*filename;
	int n;
	int ret;

    if (argCount==2)
	n=-1;
    else
	n = popNumber();

    filename=popString();
    zipfile=popString();

    ret=loadzipsound(zipfile,filename,n);
	eFree(filename);
	eFree(zipfile);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//savesound(filename,n): save a wave file from a sound slot n
void basSaveSound()
{
	char	*filename;
	int n;

	int ret;

    n = popNumber();
    filename=popString();

    ret=savesound(filename,n);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//loadmusic(filename): load a music module (xm,mod,ogg and only for linux mp3)
void basLoadMusic()
{
	char	*filename;

	int ret;
    filename=popString();

    ret=loadmusic(filename);
	eFree(filename);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);


}
//_______________________________________________________________________________________________________________________

//loadzipmusic(zipfile,filename): load a zipped music module (xm,mod,ogg and only for linux mp3)

void basLoadZipMusic()
{
	char	*zipfile;
	char	*filename;

	int ret;
    filename=popString();
    zipfile=popString();

    ret=loadzipmusic(zipfile,filename);
	eFree(filename);
	eFree(zipfile);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);


}

//_______________________________________________________________________________________________________________________
//
// Image manipulation
//_________________________________________________________________________________________________________________________

//hotspot(n,x,y): select the point of coordinates in a imageslot (n,0,0=up left(default) | n,1,1=center | n,2,2 =down right)n= image
void basHotSpot()
{
	int n,x,y;
	int ret;

    y=popNumber();
    x=popNumber();
    n=popNumber();


    ret=hotspot(n,x,y);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//setcolorkey(c): set the colorkey for bitmap transparency default=0
void basSetColorKey()
{
	int ret;
	int c;
    c = popNumber();
    ret=setcolorkey(c);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//imageexists(n): give 1 if the image buffer n exist 0 if empty
void basImageExists()
{
	int n;
	int ret;
    n = popNumber();
    ret=imageexists(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//imagewidth(n): give the image n width or error if image n if empty
void basImageWidth()
{
	int n;
	int ret;
    n = popNumber();
    ret=imagewidth(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//imageheight(n): give the image n height or error if image n if empty
void basImageHeight()
{
	int n;
	int ret;
    n = popNumber();
    ret=imageheight(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//deleteimage(n): erase the image n of the memory
void basDeleteImage()
{
	int ret;
	int n;
    n = popNumber();
    ret=deleteimage(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//copyimage(s,d): copy image s to image d
void basCopyImage()
{
	int ret;
	int s,d;
    d = popNumber();
    s = popNumber();
    ret=copyimage(s,d);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//setalpha(n,a): set trasparency
void basSetAlpha()
{
	int ret;
	int n,a;
    a = popNumber();
    n = popNumber();
    ret=setalpha(n,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//zoomimage(n,zoomx,zoomy): zoom image
void basZoomImage()
{
	int ret;
	int n;
	double zoomx,zoomy;
    zoomy = popNumber();
    zoomx = popNumber();
    n = popNumber();
    ret=zoomimage(n,zoomx,zoomy);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//rotateimage(n,angle): rotate image
void basRotateImage()
{
	int ret;
	int n;
	double angle;

    angle = popNumber();
    n = popNumber();
    ret=rotateimage(n,angle);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//rotozoomimage(n,angle,zoom): rotate and zoom image
void basRotozoomImage()
{
	int ret;
	int n;
	double angle,zoom;

    zoom = popNumber();
    angle = popNumber();
    n = popNumber();
    ret=rotozoomimage(n,angle,zoom);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//mirrorimage(n,x,y): vertical-orizontal mirror
void basMirrorImage()
{
	int ret;
	int n;
	int x,y;

    y = popNumber();
    x = popNumber();
    n = popNumber();
    ret=mirrorimage(n,x,y);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________
//
// Blitting
//_________________________________________________________________________________________________________________________

//blt(n,sx,sy,sw,sh,dx,dy): copy a part of graphics slot in screen
void basBlt()
{
    int n,sx,sy,sw,sh,dx,dy;
    int ret;

    dy = popNumber();
    dx = popNumber();
    sh = popNumber();
    sw = popNumber();
    sy = popNumber();
    sx = popNumber();
    n = popNumber();

    ret=blt(n,sx,sy,sw,sh,dx,dy);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//pastebob(x,y,n): copy on screen image n at x,y performing clip
void basPasteBob()
{
	int x,y,n;
        int ret;

    n = popNumber();
    y = popNumber();
    x = popNumber();

    ret=pastebob(x,y,n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//pasteicon(x,y,n): copy on screen image n at x,y without clipping
void basPasteIcon()
{
	int x,y,n;
	int ret;

    n = popNumber();
    y = popNumber();
    x = popNumber();

    ret= pasteicon(x,y,n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//grab(n,x,y,w,h): grab a a selectarea and copy it in slot n
void basGrab()
{
	int n,x,y,w,h;
	int ret;

    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();
    n = popNumber();

    ret=grab(n,x,y,w,h);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________
//
// Sprite system
//_______________________________________________________________________________________________________________________

//spriteclip(x,y,w,h): set the visibilty area of sprites
void basSpriteClip()
{
	int x,y,w,h;

    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( spriteclip(x,y,w,h) );
}
//_______________________________________________________________________________________________________________________

//sprite(n,x,y,fr): set or move the sprite n at x,y with image fr
void basSprite()
{
	int n,x,y,fr;
	int ret;

    fr = popNumber();
    y = popNumber();
    x = popNumber();
    n = popNumber();

    ret=sprite(n,x,y,fr);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//deletesprite(n): unset sprite n
void basDeleteSprite()
{
	int n;

    n = popNumber();

    pushNumber( deletesprite(n) );
}
//_______________________________________________________________________________________________________________________

//xsprite(n): give the x of sprite n
void basXSprite()
{
	int n;

    n = popNumber();

    pushNumber( xsprite(n) );
}
//_______________________________________________________________________________________________________________________

//ysprite(n): give the y of sprite n
void basYSprite()
{
	int n;

    n = popNumber();

    pushNumber( ysprite(n) );
}
//_______________________________________________________________________________________________________________________

//spritewidth(n): give the width of sprite n
void basSpriteWidth()
{
	int n;

    n = popNumber();

    pushNumber( spritewidth(n) );
}
//_______________________________________________________________________________________________________________________

//spriteheight(n): give the height of sprite n
void basSpriteHeight()
{
	int n;

    n = popNumber();

    pushNumber( spriteheight(n) );
}
//_______________________________________________________________________________________________________________________

//frsprite(n): give the frame of sprite n
void basFrSprite()
{
	int n;

    n = popNumber();

    pushNumber( frsprite(n) );
}
//_______________________________________________________________________________________________________________________

//livesprite(n): give 1 if sprite n is "live"
void basLiveSprite()
{
	int n;

    n = popNumber();

    pushNumber( livesprite(n) );
}
//_______________________________________________________________________________________________________________________

//spritehit(n,optional x): give 1 if sprite n have a collission with sprite x if x=-1 with any
void basSpriteHit()
{
	int n,x;
	int ret;

	if (argCount==1)
		x=-1;
	else
		x = popNumber();
    n = popNumber();

	ret=spritehit(n,x);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret  );
}
//_______________________________________________________________________________________________________________________

// spritez(n,z): set the zorder position of sprite if z =-1 report actual z position
void basSpriteZ()
{
	int n,z;
	int ret;

	if (argCount==1)
		z=-1;
	else
		z = popNumber();
    n = popNumber();

	ret=spritez(n,z);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret  );
}
//_______________________________________________________________________________________________________________________

//lastsprite: return the last sprite active
void basLastSprite()
{
    int ret;
    ret=lastsprite();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//autoupdatesprite(m): set/ unset automatic sprites update at screenswap
void basAutoUpdateSprite()
{
	int m;

    m = popNumber();

    pushNumber( autoupdatesprite(m) );
}
//_______________________________________________________________________________________________________________________

//updatesprite				: manual sprites updates at next screenswap
void basUpdateSprite()
{

    pushNumber( updatesprite() );
}
//_______________________________________________________________________________________________________________________
//
// Bob system
//_________________________________________________________________________________________________________________________

//setbob(n,scr): set bob n at logic screen scr
void basSetBob()
{
	int n,scr;

    scr = popNumber();
    n = popNumber();

    pushNumber( setbob(n,scr) );
}
//_______________________________________________________________________________________________________________________

//bob(n,x,y,fr): set or move bob n at x,y with frame fr
void basBob()
{
	int n,x,y,fr;
	int ret;

    fr = popNumber();
    y = popNumber();
    x = popNumber();
    n = popNumber();

    ret=bob(n,x,y,fr);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//deletebob(n): unset bob n
void basDeleteBob()
{
	int n;

    n = popNumber();

    pushNumber( deletebob(n) );
}
//_______________________________________________________________________________________________________________________

//xbob(n): give x of bob n
void basXBob()
{
	int n;

    n = popNumber();

    pushNumber( xbob(n) );
}
//_______________________________________________________________________________________________________________________

//ybob(n): give y of bob n
void basYBob()
{
	int n;

    n = popNumber();

    pushNumber( ybob(n) );
}
//_______________________________________________________________________________________________________________________

//bobwidth(n): give width of bob n
void basBobWidth()
{
	int n;

    n = popNumber();

    pushNumber( bobwidth(n) );
}
//_______________________________________________________________________________________________________________________

//bobheight(n): give height of bob n
void basBobHeight()
{
	int n;

    n = popNumber();

    pushNumber( bobheight(n) );
}
//_______________________________________________________________________________________________________________________

//frbob(n): give the frame of bob n
void basFrBob()
{
	int n;

    n = popNumber();

    pushNumber( frbob(n) );
}
//_______________________________________________________________________________________________________________________

//livebob(n): give 1 if bob n is "live"
void basLiveBob()
{
	int n;

    n = popNumber();

    pushNumber( livebob(n) );
}
//_______________________________________________________________________________________________________________________

//bobhit(n,optional x): give 1 if bob n have a collision with bob x if x=-1 with any
void basBobHit()
{
	int n,x;
	int ret;

	if (argCount==1)
		x=-1;
	else
		x = popNumber();
    n = popNumber();

	ret=bobhit(n,x);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret  );

}
//_______________________________________________________________________________________________________________________

// bobz(n,z): set the zorder position of bob if z =-1 report actual z position
void basBobZ()
{
	int n,z;
	int ret;

	if (argCount==1)
		z=-1;
	else
		z = popNumber();
    n = popNumber();

	ret=bobz(n,z);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret  );
}
//_______________________________________________________________________________________________________________________

//lastbob: return the last bob active
void basLastBob()
{
    int ret;
    ret=lastbob();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//autoupdatebob(m): set/ unset automatic bobs update at screenswap
void basAutoUpdateBob()
{
	int m;

    m = popNumber();

    pushNumber( autoupdatebob(m) );
}
//_______________________________________________________________________________________________________________________

//updatebob: manual bobs updates at next screenswap
void basUpdateBob()
{

    pushNumber( updatebob() );
}

//_______________________________________________________________________________________________________________________
//
// Text draw
//_________________________________________________________________________________________________________________________

//text(x,y,s,testo): print the text testo  on current screen with s size
void basText()
{
	char	*txt;
	int x,y,s,o;
	int ret;

    if (argCount==5)
	o=popNumber();
    else
	o=0;

    txt=popString();
    s = popNumber();
    y = popNumber();
    x = popNumber();

    ret=text(x,y,s,txt,o);
	eFree(txt);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//setfont(path): select the font
void basSetFont()
{
	char	*path;
	int ret;

    path=popString();

    ret=setfont(path);
	//eFree(path);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//getfont()	: get the font selected
void basGetFont()
{
    pushString(getfont());
}
//_______________________________________________________________________________________________________________________

//textrender(testo,s,n): make an image slot n with the text  write with a current font and size s
void basTextRender()
{
	char	*txt;
	int s,n,o;

	int ret;

	n=-1;
	o=0;

    if (argCount==4){
	o=popNumber();
	n = popNumber();
    }
    if (argCount==3)
	n = popNumber();


    s = popNumber();
    txt=popString();

    ret=textrender(txt,s,n,o);
	eFree(txt);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________
//
// Print screen
//_________________________________________________________________________________________________________________________

//pen(c)					: set prints color (without parameter give the current color)
void basPen()
{

	int c;
	int ret;

    if (argCount==1)
		c = popNumber();
	else c=-1;

    ret=pen(c);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//paper(c): set caractere back color (without parameter give the current color)
void basPaper()
{

	int c;
	int ret;

    if (argCount==1)
		c = popNumber();
	else c=-1;

    ret=paper(c);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//fprints(testo): print a text monospace without cariage return
void basfPrints()
{
	int ret;
	char *txt;

    txt = popString();
	ret=fprints(txt);
	eFree(txt);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//prints(testo): print a text monospace
void basPrints()
{

	int ret;
	char *txt;

    txt = popString();
	ret=prints(txt);
	eFree(txt);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//locate(x,y): move the cursor at x y
void basLocate()
{

	int x,y;

    y = popNumber();
    x = popNumber();

    pushNumber(locate(x,y) );

}
//_______________________________________________________________________________________________________________________

//atx: give x of cursor
void basAtx()
{
    pushNumber(atx());
}
//_______________________________________________________________________________________________________________________

//aty: give y of cursor
void basAty()
{
    pushNumber(aty());
}
//_______________________________________________________________________________________________________________________

//curson: show the text cursor on screen at(atx,aty)
void basCursOn()
{
    pushNumber(curson());
}
//_______________________________________________________________________________________________________________________

//cursoff: hide the text cursor
void basCursOff()
{
    pushNumber(cursoff());
}
//_______________________________________________________________________________________________________________________

//inputs(prompt,defs): give the string insert to keyboard(default is default text)
void basInputs()
{
	char *txt;
	char *request;
	char defs[255];
	txt=popString();
	strcpy(defs,txt);
	request=popString();
	inputS(request,defs);
	pushStringCopy(defs);
	eFree(txt);


}
//_______________________________________________________________________________________________________________________

//zoneinputs(x,y,l,default): give the string insert to keyboard in  x,y coordinates with l lenght
void basZoneInputs()
{
	char *txt;
	int l,y,x;

	char defs[255];
	txt=popString();
	strcpy(defs,txt);
	l=popNumber();
	y=popNumber();
	x=popNumber();
	zoneinputs(x,y,l,defs);
	/* ivanixcu: should push copy of string */
        pushStringCopy(defs);
}
//_______________________________________________________________________________________________________________________
//
// Sounds and music
//_______________________________________________________________________________________________________________________

//isenabledsound()			: return 1 if sdlsound was enabled
void basIsEnabledSound()
{
    pushNumber( isenabledsound());
}
//_______________________________________________________________________________________________________________________

//soundexists(n): give 1 if the sound buffer n exist 0 if empty
void basSoundExists()
{
	int n;
    n = popNumber();
    pushNumber( soundexists(n) );

}
//_______________________________________________________________________________________________________________________

//deletesound(n): delete the sound bank from memory
void basDeleteSound()
{
	int n;
	int ret;
    n = popNumber();
    ret=deletesound(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//copysound(s,d): copy the sound bank s in d bank
void basCopySound()
{
	int s,d;
	int ret;
    d = popNumber();
    s = popNumber();
    ret=copysound(s,d);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//musicexists(): give 1 if the music is load 0 if empty
void basMusicExists()
{
    pushNumber( musicexists() );
}
//_________________________________________________________________________________________________________________________

//playsound(n,c,optional l): play the sound n in  channel c l loops
void basPlaySound()
{
	int n,c,l;
	int ret;
    if (argCount==3)
	l=popNumber();
    else
	l=0;
    c = popNumber();
    n = popNumber();

    ret=playsound(n,c,l);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//playfreqsound(n,c,rate,optional l): play the sound n in  channel c at freq rate l loops
void basPlayFreqSound()
{
	int n,c,l;
	float rate;
	int ret;
    if (argCount==4)
	l=popNumber();
    else
	l=0;

    rate = popNumber();
    c = popNumber();
    n = popNumber();

    ret=playfreqsound(n,c,rate,l);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//volumesound(c,optional v): change the volume of channel c (-1  all) at value v (0-128) without v or -1 give the current volume
void basVolumeSound()
{
	int ret;
	int c,v;

    if (argCount==2)
	    v = popNumber();
    else
	    v=-1;

    c = popNumber();

    ret=volumesound(c,v);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//stopsound(optional c): stop the  wave play in channel c (-1 or none =all)
void basStopSound()
{
    int c;
    if (argCount==1)
	    c=popNumber();
    else
	    c=-1;
    pushNumber( stopsound(c));
}
//_______________________________________________________________________________________________________________________

//pausesound(optional c): paused channel c (-1 or none =all)
void basPauseSound()
{
    int c;
    if (argCount==1)
	    c=popNumber();
    else
	    c=-1;
    pushNumber( pausesound(c));
}
//_______________________________________________________________________________________________________________________

//resumesound(optional c): unpaused channel c (-1 or none =all)
void basResumeSound()
{
    int c;
    if (argCount==1)
	    c=popNumber();
    else
	    c=-1;
    pushNumber( resumesound(c));
}
//_______________________________________________________________________________________________________________________

//vumetersound(optional c): give the current state of sound channel (-1 or none=all)
void basVuMeterSound()
{
    int c;
    if (argCount==1)
	    c=popNumber();
    else
	    c=-1;
    pushNumber( vumetersound(c));
}
//_______________________________________________________________________________________________________________________

//positionsound(c,angle,dist): position sound in 3d space
void basPositionSound()
{
    int c,angle,dist;

    dist=popNumber();
    angle=popNumber();
    c=popNumber();

    pushNumber( positionsound(c,angle,dist));
}
//_______________________________________________________________________________________________________________________

//soundchannels(n): dinamically change the number of channells managed by sdlBasic
void basSoundChannels()
{
    int n;

    n=popNumber();
    pushNumber( soundchannels(n));
}
//_______________________________________________________________________________________________________________________

//playmusic(n): play track xm,mod,ogg,mp3 n=number of ripetition(-1 always)
void basPlayMusic()
{
	int n;
	int ret;

    n = popNumber();

    ret=playmusic(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//positionmusic(p): move the execution at p second
void basPositionMusic()
{
	int p;
	int ret;

    p = popNumber();

    ret=positionmusic(p);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//stopmusic: terminate the music play
void basStopMusic()
{
    pushNumber( stopmusic() );
}
//_______________________________________________________________________________________________________________________

//pausemusic: set pause of the current music
void basPauseMusic(void)
{
    pushNumber( pausemusic() );
}
//_______________________________________________________________________________________________________________________

//resumemusic: unset pause of musica
void basResumeMusic(void)
{
    pushNumber( resumemusic() );
}
//_______________________________________________________________________________________________________________________

//rewindmusic: report at start the music
void basRewindMusic(void)
{
    pushNumber( rewindmusic() );
}
//_______________________________________________________________________________________________________________________

//fademusic(t): music fade
void basFadeMusic()
{
    int t;
    int ret;

    if(argCount==1)
	t = popNumber();
    else
	t=-1;

    ret=fademusic(t);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}
//_______________________________________________________________________________________________________________________

//volumemusic(optional v): change the volume of music (0-128) -1 or none give the current volume
void basVolumeMusic()
{
    int v;
    int ret;
    if (argCount==1)
	    v = popNumber();
    else
	    v=-1;

    ret=volumemusic(v);

    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//speedmusic(v): change the speed of music
void basSpeedMusic()
{
	int v;
	    v = popNumber();
    pushNumber( speedmusic(v));

}

//_______________________________________________________________________________________________________________________
//
// Keyboard
//_________________________________________________________________________________________________________________________

//key(keycode): give 1 if is press the key keycode
void basKey()
{
    int ret;
    int keycode;

    keycode = popNumber();
    ret=key(keycode);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber( ret );
}
//_______________________________________________________________________________________________________________________

//inkey: give ascii code of key press
void basInkey()
{
    pushNumber(inkey());
}
//_______________________________________________________________________________________________________________________

//waitkey(optional keycode): wait a key pression (0 =any key)
void basWaitKey()
{
    int keycode;

    if (argCount==1)
        keycode = popNumber();
    else
	keycode=0;
    pushNumber(waitkey(keycode));
}
//_______________________________________________________________________________________________________________________
//
// Mouse
//_________________________________________________________________________________________________________________________

//xmouse: give mouse x coordinate on display
void basXMouse()
{
    pushNumber( xmouse() );
}
//_______________________________________________________________________________________________________________________

//ymouse: give mouse y coordinate on display
void basYMouse()
{
    pushNumber( ymouse() );
}
//_______________________________________________________________________________________________________________________

//xmousescreen(n): give mouse x coordinate on screen
void basXMouseScreen()
{
    int n;
    n=popNumber();
    pushNumber( xmousescreen(n) );
}
//_______________________________________________________________________________________________________________________

//ymousescreen(n): give mouse y coordinate on screen
void basYMouseScreen()
{
    int n;
    n=popNumber();
    pushNumber( ymousescreen(n) );
}
//_______________________________________________________________________________________________________________________

//bmouse: give the buttonclick on the mouse
void basBMouse()
{
    pushNumber( bmouse() );
}
//_______________________________________________________________________________________________________________________

//changemouse(optional n): change mouse from default(0) to emulate with sprite 0 - image 0 (1,2,3)without n return current pointer
void basChangeMouse()
{
    int n;
    int ret;
    if (argCount==1)
	n=popNumber();
    else
	n=-1;

    ret=changemouse(n);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

// locatemouse: move cursor at xy coordinates
void basLocateMouse()
{
    int x,y;
    int ret;
    y=popNumber();
    x=popNumber();
    ret=locatemouse(x,y);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);

}

//_______________________________________________________________________________________________________________________

//mouseshow: show the mouse cursor
void basMouseShow()
{
    pushNumber( mouseshow() );
}
//_______________________________________________________________________________________________________________________

//mousehide: hide the mouse cursor
void basMouseHide()
{
    pushNumber( mousehide() );
}
//_______________________________________________________________________________________________________________________

//mousezone(x,y,w,h): give 1 if the mouse pointer is in rectangle(xy with size wh)
void basMouseZone()
{
    int x,y,w,h;


    h = popNumber();
    w = popNumber();
    y = popNumber();
    x = popNumber();

    pushNumber( mousezone(x,y,w,h) );

}
//_______________________________________________________________________________________________________________________
//
// Joystick
//_________________________________________________________________________________________________________________________

//numjoysticks: Count available joysticks.
void basNumJoySticks()
{
    int ret;
    ret=numjoysticks();
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//namejoystick(i): Get joystick name
void basNameJoyStick()
{
   char *ret;
    int i;

    i=popNumber();
    ret=namejoystick(i);
    if (ret==NULL) ePrintf( Runtime, "SDLengine Error \n");
    pushString(ret);
}
//_______________________________________________________________________________________________________________________

//numaxesjoystick(i): Get the number of joystick axes
void basNumAxesJoyStick(void)
{
   int ret;
    int i;

    i=popNumber();
    ret=numaxesjoystick(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//numballsjoystick(i): Get the number of joystick trackballs
void basNumBallsJoyStick(void)
{
   int ret;
    int i;

    i=popNumber();
    ret=numballsjoystick(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//numhatsjoystick(i): Get the number of joystick hats
void basNumHatsJoyStick(void)
{
   int ret;
    int i;

    i=popNumber();
    ret=numhatsjoystick(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//numbuttonsjoystick(i): Get the number of joysitck buttons
void basNumButtonsJoyStick(void)
{
   int ret;
    int i;

    i=popNumber();
    ret=numbuttonsjoystick(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//getaxisjoystick(i,a): Get the current state of an axis
void basGetAxisJoyStick(void)
{
   int ret;
    int a,i;

    a=popNumber();
    i=popNumber();
    ret=getaxisjoystick(i,a);
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//gethatjoystick(i,a): Get the current state of a joystick hat
void basGetHatJoyStick(void)
{
   int ret;
    int a,i;

    a=popNumber();
    i=popNumber();
    ret=gethatjoystick(i,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//getbuttonjoystick(i,a): Get the current state of a given button on a given joystick
void basGetButtonJoyStick(void)
{
   int ret;
    int a,i;

    a=popNumber();
    i=popNumber();
    ret=getbuttonjoystick(i,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//xgetballjoystick(i,a): Get relative trackball motion
void basXGetBallJoyStick(void)
{
   int ret;
    int a,i;

    a=popNumber();
    i=popNumber();
    ret=xgetballjoystick(i,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//ygetballjoystick(i,a): Get relative trackball motion
void basYGetBallJoyStick(void)
{
   int ret;
    int a,i;

    a=popNumber();
    i=popNumber();
    ret=ygetballjoystick(i,a);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//joy: give joystick boolean coordinate
void basJoy()
{
    int i,ret;
    i=popNumber();
    ret=joy(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//bjoy					: give joystick button pressed
void basBJoy()
{
    int i,ret;
    i=popNumber();
    ret=bjoy(i);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//waitbjoy					: wait joystick button pressed
void basWaitBJoy()
{
    int j,b,ret;
    if (argCount==2)
	j=popNumber();
    else
	j=0;

    b=popNumber();


    ret=waitbjoy(b,j);
    if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________
//
// SDLtime
//_________________________________________________________________________________________________________________________

//wait(t): wait t milliseconds
void basWait()
{
	int t;
	int ret;

	t= popNumber();
	ret=waitTime(t);
	if (ret==-1) ePrintf( Runtime, "SDLengine Error \n");
	pushNumber( ret);
}
//_______________________________________________________________________________________________________________________

//timer: give the current tick
void basTimer()
{
	pushNumber( chrono());
}
