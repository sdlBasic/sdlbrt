/*
_________________________________________________________________________________________________________________________

    SDLengine core of sdlBasic
    SDL_exstension


    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    __vroby__
    __vroby__@libero.it

_________________________________________________________________________________________________________________________

*/

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "SDLengine.h"

//________________________________________________________________________________________________________________________________________

// SDL_EXTENSION
//________________________________________________________________________________________________________________________________________

// fileExist(filename)			: see if a file exists
int fileExist( char *name )
{
    FILE    *handle;
    /* try to open the file */
    handle = fopen( name, "rb" );
    if (handle == NULL) return 0;
    fclose( handle );
    return -1;
}
//________________________________________________________________________________________________________________________________________

// Load_Image(filename,trasparent)	: load a image using sdl_image library
SDL_Surface *Load_Image(char *datafile, int transparent)
{
    int bpp;
    Uint32 oldck;
	SDL_Surface *image, *surface;

	if (SDLnoAlphaChannel==0){
	    image=SDL_DisplayFormatAlpha(IMG_Load(datafile));
	}
	else{
	    //image =IMG_Load(datafile);
	    image =SDL_DisplayFormat(IMG_Load(datafile));
	}
	surface=NULL;

	if ( image == NULL ) {
		error_description="Can't load image \n";
		error_type=1;
		SDLerr(stderr, "Can't load image %s: %s\n",datafile, IMG_GetError());

		return(NULL);
	}
	if ( transparent ) {
		bpp = image->format->BytesPerPixel;

		oldck=colorkey;

		if (SDL_MUSTLOCK(image) )
		    SDL_LockSurface(image);

		switch(bpp) {
		    case 1:
			if (colorkey==-1)colorkey=*(Uint8 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint8) colorkey);//*(Uint8 *)image->pixels

			if (SDLnoAlphaChannel==0){
			    SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, 0);
			    surface = SDL_DisplayFormatAlpha(image);
			}
			else{
			    surface = SDL_DisplayFormat(image);
			}
			break;
		    case 2:
			if (colorkey==-1)colorkey=*(Uint16 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint16)colorkey);//*(Uint16 *)image->pixels

			if (SDLnoAlphaChannel==0){
			    SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, 0);
			    surface = SDL_DisplayFormatAlpha(image);
			}
			else{
			    surface = SDL_DisplayFormat(image);
			}
			break;
		    case 3:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels

			if (SDLnoAlphaChannel==0){
			SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, 0);
			    surface = SDL_DisplayFormatAlpha(image);
			}
			else{
			    surface = SDL_DisplayFormat(image);
			}
			break;
		    case 4:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels

			if (SDLnoAlphaChannel==0){
			    SDL_SetAlpha(image, SDL_SRCALPHA|SDL_RLEACCEL, 0);
			    surface = SDL_DisplayFormatAlpha(image);
			}
			else{
			    surface = SDL_DisplayFormat(image);
			}
			break;
		    }
		    if (SDL_MUSTLOCK(image) )
			SDL_UnlockSurface(image);
		    colorkey=oldck;


	}else{

		if (SDLnoAlphaChannel==0)
		    surface = SDL_DisplayFormatAlpha(image);
		else
		    surface = SDL_DisplayFormat(image);
	}

	SDL_FreeSurface(image);

	return(surface);
}
//________________________________________________________________________________________________________________________________________

// Load_zip_Image(zipfile,filename,trasparent)	: load a image using sdl_image library
SDL_Surface *Load_zip_Image(char *zipfile,char *datafile, int transparent)
{
    unsigned char *mem;
    SDL_RWops *src;
    int size;
    int bpp;
    Uint32 oldck;
	SDL_Surface *image, *surface;

	if (load_zipped_file (zipfile, datafile, &mem, &size)==0){
	    src=SDL_RWFromMem(mem, size);
	    image=SDL_DisplayFormat(IMG_Load_RW(src, 0));
	    if ( image == NULL ) {
		error_description="Can't load image \n";
		error_type=1;
		SDLerr(stderr, "\n Load_zip_Image: Can't load image %s: %s \n",datafile, IMG_GetError());

		return(NULL);
	    }
	    if ( transparent ) {
		bpp = image->format->BytesPerPixel;

		oldck=colorkey;

		if (SDL_MUSTLOCK(image) )
		    SDL_LockSurface(image);

		switch(bpp) {
		    case 1:
			if (colorkey==-1)colorkey=*(Uint8 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint8) colorkey);//*(Uint8 *)image->pixels
			break;
		    case 2:
			if (colorkey==-1)colorkey=*(Uint16 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint16)colorkey);//*(Uint16 *)image->pixels
			break;
		    case 3:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels
			break;
		    case 4:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels
			break;
		    }
		    if (SDL_MUSTLOCK(image) )
			SDL_UnlockSurface(image);
		    colorkey=oldck;
	    }

	    surface = SDL_DisplayFormat(image);
	    SDL_FreeSurface(image);
	    return(surface);
	}
	else
	    return(NULL);
}
//________________________________________________________________________________________________________________________________________
SDL_Surface *Map_blob_Image(unsigned char *blob, int bsize, int transparent)
{
	SDL_RWops *src;
	int bpp;
	Uint32 oldck;
	SDL_Surface *image, *surface;

	src=SDL_RWFromMem(blob, bsize);
	image=SDL_DisplayFormat(IMG_Load_RW(src, 0));
	if ( image == NULL ) {
		error_description="Can't map image \n";
		error_type=1;
		SDLerr(stderr, "\n Map_zip_Image: Can't map image: %s \n", IMG_GetError());

		return(NULL);
	}
	if ( transparent ) {
		bpp = image->format->BytesPerPixel;
		oldck=colorkey;

		if (SDL_MUSTLOCK(image) )
		{
		    SDL_LockSurface(image);
		}

		switch(bpp) {
		    case 1:
			if (colorkey==-1)colorkey=*(Uint8 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint8) colorkey);//*(Uint8 *)image->pixels
			break;
		    case 2:
			if (colorkey==-1)colorkey=*(Uint16 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint16)colorkey);//*(Uint16 *)image->pixels
			break;
		    case 3:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels
			break;
		    case 4:
			if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
			SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);//*(Uint32 *)image->pixels
			break;
		    }
		    if (SDL_MUSTLOCK(image) )
			SDL_UnlockSurface(image);
		    colorkey=oldck;
	    }

	    surface = SDL_DisplayFormat(image);
	    SDL_FreeSurface(image);
	    return(surface);
}
//________________________________________________________________________________________________________________________________________


//Save_Image(filename,image) 	: save the image using sdl rutines you can save only in bmp format
int Save_Image(char *datafile, SDL_Surface *image)
{
	if ( SDL_SaveBMP( image , datafile) ) {
		error_description="Can't save image \n";
		error_type=1;
		SDLerr(stderr, "Can't save image %s: %s\n",datafile, IMG_GetError());
		return -1;
	}
	return 0;
}
//________________________________________________________________________________________________________________________________________

// Image_colorkey(image)	: set trasparency on image
void Image_colorkey(SDL_Surface *image)
{
    int bpp;
    Uint32 oldck;


    if (SDL_MUSTLOCK(image))
	SDL_LockSurface(image);

    bpp = image->format->BytesPerPixel;
    oldck=colorkey;

    switch(bpp) {
	case 1:
	    if (colorkey==-1)colorkey=*(Uint8 *)image->pixels;
	    SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint8)colorkey);
	    break;
	case 2:
	    if (colorkey==-1)colorkey=*(Uint16 *)image->pixels;
	    SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint16)colorkey);
	    break;
	case 3:
	    if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
	    SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);
	    break;
	case 4:
	    if (colorkey==-1)colorkey=*(Uint32 *)image->pixels;
	    SDL_SetColorKey(image, (SDL_SRCCOLORKEY|SDL_RLEACCEL),(Uint32)colorkey);
	    break;
    }
    if (SDL_MUSTLOCK(image))
	SDL_UnlockSurface(image);

    colorkey=oldck;


}
//________________________________________________________________________________________________________________________________________

// this rutine was posted by Johannes Bauer in sdl-mailing list: tank'you Joe!!
// Function expects a 16-bit Stereo Sample (4 Byte/Sample) and a scale
// factor (>1 means longer sample, thus lower pitch, <1 means shorter
// sample, thus higher pitch)
Mix_Chunk* Change_Pitch(Mix_Chunk *Input_Sample, float Factor)
{
    Mix_Chunk *Sample_Modified;
    Uint32 Number_Input_Samples;
    Uint32 Number_Output_Samples;
    float Real_Factor;

    Uint32 Begin, End;
    Sint16 Left, Right;
    Sint64 AverageL, AverageR;
    Sint16 OutLeft, OutRight;

    Uint32 i;
    Uint32 j;
    /*
    if (Input_Sample->allocated!=1) {
	throw CGenericException(std::string("CSound::Change_Pitch"),std::string("Input sample not allocated."));
    }
    */

    Number_Input_Samples=Input_Sample->alen/4;
    Number_Output_Samples= (Uint32) ((float)Number_Input_Samples*Factor);
    Real_Factor = (float) Number_Output_Samples/ (float) Number_Input_Samples;

    Sample_Modified=(Mix_Chunk*)malloc(sizeof(Mix_Chunk));
    Sample_Modified->allocated=1;// Not yet, but will soon be
    Sample_Modified->alen=Number_Output_Samples*4;
    Sample_Modified->abuf=(Uint8*)malloc(Sample_Modified->alen*sizeof(Uint8));
    Sample_Modified->volume=Input_Sample->volume;

    for (i=0;i<Number_Output_Samples;i++) {
	Begin=(Uint32)((float)i/Real_Factor);
	End=(Uint32)((float)(i+1)/Real_Factor);
	AverageL=0;
	AverageR=0;

	// Destinataion i is the average of Begin-End of Input sample
	for (j=Begin;j<=End;j++) {
	    Left=(Input_Sample->abuf[(4*j)+1]<<8)|(Input_Sample->abuf[(4*j)+0]);
	    Right=(Input_Sample->abuf[(4*j)+3]<<8)|(Input_Sample->abuf[(4*j)+2]);

	    AverageL+=Left;
	    AverageR+=Right;
	}
	OutLeft=(Sint16)((float)AverageL/(float)(End-Begin+1));
	OutRight=(Sint16)((float)AverageR/(float)(End-Begin+1));

	Sample_Modified->abuf[(4*i)+1]=(OutLeft>>8)&0xff;
	Sample_Modified->abuf[(4*i)+0]=(OutLeft)&0xff;
	Sample_Modified->abuf[(4*i)+3]=(OutRight>>8)&0xff;
	Sample_Modified->abuf[(4*i)+2]=(OutRight)&0xff;
    }
    return Sample_Modified;
}
//________________________________________________________________________________________________________________________________________

/*
Rotozoom/Zoom function for SDL
========================================================================================
(C) LGPL, A. Schiffler, aschiffler@cogeco.com - see LICENSE for details.


 32bit Zoomer with optional anti-aliasing by bilinear interpolation.
 Zoomes 32bit RGBA/ABGR 'src' surface to 'dst' surface.
*/

int zoomSurfaceRGBA (SDL_Surface * src, SDL_Surface * dst, int smooth)
{
  int x, y, sx, sy, *sax, *say, *csax, *csay, csx, csy, ex, ey, t1, t2, sstep;
  tColorRGBA *c00, *c01, *c10, *c11;
  tColorRGBA *sp, *csp, *dp;
  int sgap, dgap, orderRGBA;

  /* Variable setup */
  if (smooth)
    {
      /* For interpolation: assume source dimension is one pixel */
      /* smaller to avoid overflow on right and bottom edge.     */
      sx = (int) (65536.0 * (float) (src->w - 1) / (float) dst->w);
      sy = (int) (65536.0 * (float) (src->h - 1) / (float) dst->h);
    }
  else
    {
      sx = (int) (65536.0 * (float) src->w / (float) dst->w);
      sy = (int) (65536.0 * (float) src->h / (float) dst->h);
    }

  /* Allocate memory for row increments */
  if ((sax = (int *) malloc ((dst->w + 1) * sizeof (Uint32))) == NULL)
    {
      return (-1);
    }
  if ((say = (int *) malloc ((dst->h + 1) * sizeof (Uint32))) == NULL)
    {
      free (sax);
      return (-1);
    }

  /* Precalculate row increments */
  csx = 0;
  csax = sax;
  for (x = 0; x <= dst->w; x++)
    {
      *csax = csx;
      csax++;
      csx &= 0xffff;
      csx += sx;
    }
  csy = 0;
  csay = say;
  for (y = 0; y <= dst->h; y++)
    {
      *csay = csy;
      csay++;
      csy &= 0xffff;
      csy += sy;
    }

  /* Pointer setup */
  sp = csp = (tColorRGBA *) src->pixels;
  dp = (tColorRGBA *) dst->pixels;
  sgap = src->pitch - src->w * 4;
  dgap = dst->pitch - dst->w * 4;
  orderRGBA = (src->format->Rmask == 0x000000ff);

  /* Switch between interpolating and non-interpolating code */
  if (smooth)
    {

      /* Interpolating Zoom */

      /* Scan destination */
      csay = say;
      for (y = 0; y < dst->h; y++)
	{
	  /* Setup color source pointers */
	  c00 = csp;
	  c01 = csp;
	  c01++;
	  c10 = (tColorRGBA *) ((Uint8 *) csp + src->pitch);
	  c11 = c10;
	  c11++;
	  csax = sax;
	  for (x = 0; x < dst->w; x++)
	    {
	      /* ABGR ordering */
	      /* Interpolate colors */
	      ex = (*csax & 0xffff);
	      ey = (*csay & 0xffff);
	      t1 = ((((c01->r - c00->r) * ex) >> 16) + c00->r) & 0xff;
	      t2 = ((((c11->r - c10->r) * ex) >> 16) + c10->r) & 0xff;
	      dp->r = (((t2 - t1) * ey) >> 16) + t1;
	      t1 = ((((c01->g - c00->g) * ex) >> 16) + c00->g) & 0xff;
	      t2 = ((((c11->g - c10->g) * ex) >> 16) + c10->g) & 0xff;
	      dp->g = (((t2 - t1) * ey) >> 16) + t1;
	      t1 = ((((c01->b - c00->b) * ex) >> 16) + c00->b) & 0xff;
	      t2 = ((((c11->b - c10->b) * ex) >> 16) + c10->b) & 0xff;
	      dp->b = (((t2 - t1) * ey) >> 16) + t1;
	      t1 = ((((c01->a - c00->a) * ex) >> 16) + c00->a) & 0xff;
	      t2 = ((((c11->a - c10->a) * ex) >> 16) + c10->a) & 0xff;
	      dp->a = (((t2 - t1) * ey) >> 16) + t1;
	      /* Advance source pointers */
	      csax++;
	      sstep = (*csax >> 16);
	      c00 += sstep;
	      c01 += sstep;
	      c10 += sstep;
	      c11 += sstep;
	      /* Advance destination pointer */
	      dp++;
	    }
	  /* Advance source pointer */
	  csay++;
	  csp = (tColorRGBA *) ((Uint8 *) csp + (*csay >> 16) * src->pitch);
	  /* Advance destination pointers */
	  dp = (tColorRGBA *) ((Uint8 *) dp + dgap);
	}

    }
  else
    {

      /* Non-Interpolating Zoom */

      csay = say;
      for (y = 0; y < dst->h; y++)
	{
	  sp = csp;
	  csax = sax;
	  for (x = 0; x < dst->w; x++)
	    {
	      /* Draw */
	      *dp = *sp;
	      /* Advance source pointers */
	      csax++;
	      sp += (*csax >> 16);
	      /* Advance destination pointer */
	      dp++;
	    }
	  /* Advance source pointer */
	  csay++;
	  csp = (tColorRGBA *) ((Uint8 *) csp + (*csay >> 16) * src->pitch);
	  /* Advance destination pointers */
	  dp = (tColorRGBA *) ((Uint8 *) dp + dgap);
	}

    }

  /* Remove temp arrays */
  free (sax);
  free (say);

  return (0);
}
//________________________________________________________________________________________________________________________________________

/*
 8bit Zoomer without smoothing.
 Zoomes 8bit palette/Y 'src' surface to 'dst' surface.
*/

int zoomSurfaceY (SDL_Surface * src, SDL_Surface * dst)
{
  Uint32 x, y, sx, sy, *sax, *say, *csax, *csay, csx, csy;
  Uint8 *sp, *dp, *csp;
  int dgap;

  /* Variable setup */
  sx = (Uint32) (65536.0 * (float) src->w / (float) dst->w);
  sy = (Uint32) (65536.0 * (float) src->h / (float) dst->h);

  /* Allocate memory for row increments */
  if ((sax = (Uint32 *) malloc (dst->w * sizeof (Uint32))) == NULL)
    {
      return (-1);
    }
  if ((say = (Uint32 *) malloc (dst->h * sizeof (Uint32))) == NULL)
    {
      if (sax != NULL)
	{
	  free (sax);
	}
      return (-1);
    }

  /* Precalculate row increments */
  csx = 0;
  csax = sax;
  for (x = 0; x < dst->w; x++)
    {
      csx += sx;
      *csax = (csx >> 16);
      csx &= 0xffff;
      csax++;
    }
  csy = 0;
  csay = say;
  for (y = 0; y < dst->h; y++)
    {
      csy += sy;
      *csay = (csy >> 16);
      csy &= 0xffff;
      csay++;
    }

  csx = 0;
  csax = sax;
  for (x = 0; x < dst->w; x++)
    {
      csx += (*csax);
      csax++;
    }
  csy = 0;
  csay = say;
  for (y = 0; y < dst->h; y++)
    {
      csy += (*csay);
      csay++;
    }

  /* Pointer setup */
  sp = csp = (Uint8 *) src->pixels;
  dp = (Uint8 *) dst->pixels;
  dgap = dst->pitch - dst->w;

  /* Draw */
  csay = say;
  for (y = 0; y < dst->h; y++)
    {
      csax = sax;
      sp = csp;
      for (x = 0; x < dst->w; x++)
	{
	  /* Draw */
	  *dp = *sp;
	  /* Advance source pointers */
	  sp += (*csax);
	  csax++;
	  /* Advance destination pointer */
	  dp++;
	}
      /* Advance source pointer (for row) */
      csp += ((*csay) * src->pitch);
      csay++;
      /* Advance destination pointers */
      dp += dgap;
    }

  /* Remove temp arrays */
  free (sax);
  free (say);

  return (0);
}
//________________________________________________________________________________________________________________________________________

/*
 32bit Rotozoomer with optional anti-aliasing by bilinear interpolation.
 Rotates and zoomes 32bit RGBA/ABGR 'src' surface to 'dst' surface.
*/

void transformSurfaceRGBA (SDL_Surface * src, SDL_Surface * dst, int cx, int cy,int isin, int icos, int smooth)
{
  int x, y, t1, t2, dx, dy, xd, yd, sdx, sdy, ax, ay, ex, ey, sw, sh;
  tColorRGBA c00={0,0,0}, c01={0,0,0}, c10={0,0,0}, c11={0,0,0};
  tColorRGBA *pc, *sp;
  int gap, orderRGBA;

  /* Variable setup */
  xd = ((src->w - dst->w) << 15);
  yd = ((src->h - dst->h) << 15);
  ax = (cx << 16) - (icos * cx);
  ay = (cy << 16) - (isin * cx);
  sw = src->w - 1;
  sh = src->h - 1;
  pc = dst->pixels;
  gap = dst->pitch - dst->w * 4;
  orderRGBA = (src->format->Rmask == 0x000000ff);

  /* Switch between interpolating and non-interpolating code */
  if (smooth)
    {
      for (y = 0; y < dst->h; y++)
	{
	  dy = cy - y;
	  sdx = (ax + (isin * dy)) + xd;
	  sdy = (ay - (icos * dy)) + yd;
	  for (x = 0; x < dst->w; x++)
	    {
	      dx = (sdx >> 16);
	      dy = (sdy >> 16);
	      if ((dx >= -1) && (dy >= -1) && (dx < src->w) && (dy < src->h))
		{
		  if ((dx >= 0) && (dy >= 0) && (dx < sw) && (dy < sh))
		    {
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      sp += dx;
		      c00 = *sp;
		      sp += 1;
		      c01 = *sp;
		      sp = (tColorRGBA *) ((Uint8 *) sp + src->pitch);
		      sp -= 1;
		      c10 = *sp;
		      sp += 1;
		      c11 = *sp;
		    }
		  else if ((dx == sw) && (dy == sh))
		    {
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      sp += dx;
		      c00 = *sp;
		      c01 = *pc;
		      c10 = *pc;
		      c11 = *pc;
		    }
		  else if ((dx == -1) && (dy == -1))
		    {
		      sp = (tColorRGBA *) (src->pixels);
		      c00 = *pc;
		      c01 = *pc;
		      c10 = *pc;
		      c11 = *sp;
		    }
		  else if ((dx == -1) && (dy == sh))
		    {
		      sp = (tColorRGBA *) (src->pixels);
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      c00 = *pc;
		      c01 = *sp;
		      c10 = *pc;
		      c11 = *pc;
		    }
		  else if ((dx == sw) && (dy == -1))
		    {
		      sp = (tColorRGBA *) (src->pixels);
		      sp += dx;
		      c00 = *pc;
		      c01 = *pc;
		      c10 = *sp;
		      c11 = *pc;
		    }
		  else if (dx == -1)
		    {
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      c00 = *pc;
		      c01 = *sp;
		      c10 = *pc;
		      sp = (tColorRGBA *) ((Uint8 *) sp + src->pitch);
		      c11 = *sp;
		    }
		  else if (dy == -1)
		    {
		      sp = (tColorRGBA *) (src->pixels);
		      sp += dx;
		      c00 = *pc;
		      c01 = *pc;
		      c10 = *sp;
		      sp += 1;
		      c11 = *sp;
		    }
		  else if (dx == sw)
		    {
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      sp += dx;
		      c00 = *sp;
		      c01 = *pc;
		      sp = (tColorRGBA *) ((Uint8 *) sp + src->pitch);
		      c10 = *sp;
		      c11 = *pc;
		    }
		  else if (dy == sh)
		    {
		      sp =
			(tColorRGBA *) ((Uint8 *) src->pixels +
					src->pitch * dy);
		      sp += dx;
		      c00 = *sp;
		      sp += 1;
		      c01 = *sp;
		      c10 = *pc;
		      c11 = *pc;
		    }
		  /* Interpolate colors */
		  ex = (sdx & 0xffff);
		  ey = (sdy & 0xffff);
		  t1 = ((((c01.r - c00.r) * ex) >> 16) + c00.r) & 0xff;
		  t2 = ((((c11.r - c10.r) * ex) >> 16) + c10.r) & 0xff;
		  pc->r = (((t2 - t1) * ey) >> 16) + t1;
		  t1 = ((((c01.g - c00.g) * ex) >> 16) + c00.g) & 0xff;
		  t2 = ((((c11.g - c10.g) * ex) >> 16) + c10.g) & 0xff;
		  pc->g = (((t2 - t1) * ey) >> 16) + t1;
		  t1 = ((((c01.b - c00.b) * ex) >> 16) + c00.b) & 0xff;
		  t2 = ((((c11.b - c10.b) * ex) >> 16) + c10.b) & 0xff;
		  pc->b = (((t2 - t1) * ey) >> 16) + t1;
		  t1 = ((((c01.a - c00.a) * ex) >> 16) + c00.a) & 0xff;
		  t2 = ((((c11.a - c10.a) * ex) >> 16) + c10.a) & 0xff;
		  pc->a = (((t2 - t1) * ey) >> 16) + t1;

		}
	      sdx += icos;
	      sdy += isin;
	      pc++;
	    }
	  pc = (tColorRGBA *) ((Uint8 *) pc + gap);
	}
    }
  else
    {
      for (y = 0; y < dst->h; y++)
	{
	  dy = cy - y;
	  sdx = (ax + (isin * dy)) + xd;
	  sdy = (ay - (icos * dy)) + yd;
	  for (x = 0; x < dst->w; x++)
	    {
	      dx = (short) (sdx >> 16);
	      dy = (short) (sdy >> 16);
	      if ((dx >= 0) && (dy >= 0) && (dx < src->w) && (dy < src->h))
		{
		  sp =
		    (tColorRGBA *) ((Uint8 *) src->pixels + src->pitch * dy);
		  sp += dx;
		  *pc = *sp;
		}
	      sdx += icos;
	      sdy += isin;
	      pc++;
	    }
	  pc = (tColorRGBA *) ((Uint8 *) pc + gap);
	}
    }
}


/*
 8bit Rotozoomer without smoothing
 Rotates and zoomes 8bit palette/Y 'src' surface to 'dst' surface.
*/

void transformSurfaceY (SDL_Surface * src, SDL_Surface * dst, int cx, int cy,int isin, int icos)
{
  int x, y, dx, dy, xd, yd, sdx, sdy, ax, ay, sw, sh;
  tColorY *pc, *sp;
  int gap;

  /* Variable setup */
  xd = ((src->w - dst->w) << 15);
  yd = ((src->h - dst->h) << 15);
  ax = (cx << 16) - (icos * cx);
  ay = (cy << 16) - (isin * cx);
  sw = src->w - 1;
  sh = src->h - 1;
  pc = dst->pixels;
  gap = dst->pitch - dst->w;
  /* Clear surface to colorkey */
  memset (pc, (unsigned char) (src->format->colorkey & 0xff),
	  dst->pitch * dst->h);
  /* Iterate through destination surface */
  for (y = 0; y < dst->h; y++)
    {
      dy = cy - y;
      sdx = (ax + (isin * dy)) + xd;
      sdy = (ay - (icos * dy)) + yd;
      for (x = 0; x < dst->w; x++)
	{
	  dx = (short) (sdx >> 16);
	  dy = (short) (sdy >> 16);
	  if ((dx >= 0) && (dy >= 0) && (dx < src->w) && (dy < src->h))
	    {
	      sp = (tColorY *) (src->pixels);
	      sp += (src->pitch * dy + dx);
	      *pc = *sp;
	    }
	  sdx += icos;
	  sdy += isin;
	  pc++;
	}
      pc += gap;
    }
}
//________________________________________________________________________________________________________________________________________

/*
 rotozoomSurface()
 Rotates and zoomes a 32bit or 8bit 'src' surface to newly created 'dst' surface.
 'angle' is the rotation in degrees. 'zoom' a scaling factor. If 'smooth' is 1
 then the destination 32bit surface is anti-aliased. If the surface is not 8bit
 or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.

*/

#define VALUE_LIMIT	0.001

SDL_Surface * rotozoomSurface (SDL_Surface * src, double angle, double zoom, int smooth)
{
  SDL_Surface *rz_src;
  SDL_Surface *rz_dst;
  double zoominv;
  double radangle, sanglezoom, canglezoom, sanglezoominv, canglezoominv;
  int dstwidthhalf, dstwidth, dstheighthalf, dstheight;
  double x, y, cx, cy, sx, sy;
  int is32bit;
  int i, src_converted;

  /* Sanity check */
  if (src == NULL)
    return (NULL);

  /* Determine if source surface is 32bit or 8bit */
  is32bit = (src->format->BitsPerPixel == 32);
  if ((is32bit) || (src->format->BitsPerPixel == 8))
    {
      /* Use source surface 'as is' */
      rz_src = src;
      src_converted = 0;
    }
  else
    {
      /* New source surface is 32bit with a defined RGBA ordering */
      rz_src =
	SDL_CreateRGBSurface (SDL_SWSURFACE, src->w, src->h, 32, 0x000000ff,
			      0x0000ff00, 0x00ff0000, 0xff000000);
	    //patch for colorkey setted
	if (colorkey!=-1)
	    SDL_FillRect(rz_src,NULL,colorkey);
	else
	    SDL_FillRect(rz_src,NULL,*(Uint32*)src->pixels);


      SDL_BlitSurface (src, NULL, rz_src, NULL);
      src_converted = 1;
      is32bit = 1;
    }

  /* Sanity check zoom factor */
  if (zoom < VALUE_LIMIT)
    {
      zoom = VALUE_LIMIT;
    }
  zoominv = 65536.0 / zoom;

  /* Check if we have a rotozoom or just a zoom */
  if (fabs (angle) > VALUE_LIMIT)
    {

      /* Angle!=0: full rotozoom */
      /* ----------------------- */

      /* Calculate target factors from sin/cos and zoom */
      radangle = angle * (M_PI / 180.0);
      sanglezoom = sanglezoominv = sin (radangle);
      canglezoom = canglezoominv = cos (radangle);
      sanglezoom *= zoom;
      canglezoom *= zoom;
      sanglezoominv *= zoominv;
      canglezoominv *= zoominv;

      /* Determine destination width and height by rotating a centered source box */
      x = rz_src->w / 2;
      y = rz_src->h / 2;
      cx = canglezoom * x;
      cy = canglezoom * y;
      sx = sanglezoom * x;
      sy = sanglezoom * y;
      dstwidthhalf =
	MAX ((int)
	     ceil (MAX
		   (MAX
		    (MAX (fabs (cx + sy), fabs (cx - sy)), fabs (-cx + sy)),
		    fabs (-cx - sy))), 1);
      dstheighthalf =
	MAX ((int)
	     ceil (MAX
		   (MAX
		    (MAX (fabs (sx + cy), fabs (sx - cy)), fabs (-sx + cy)),
		    fabs (-sx - cy))), 1);
      dstwidth = 2 * dstwidthhalf;
      dstheight = 2 * dstheighthalf;

      /* Alloc space to completely contain the rotated surface */
      rz_dst = NULL;
      if (is32bit)
	{
	  /* Target surface is 32bit with source RGBA/ABGR ordering */
	  rz_dst =
	    SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 32,
				  rz_src->format->Rmask,
				  rz_src->format->Gmask,
				  rz_src->format->Bmask,
				  rz_src->format->Amask);
	    //patch for colorkey setted
	    if (colorkey!=-1)
		SDL_FillRect(rz_dst,NULL,colorkey);
	    else
		SDL_FillRect(rz_dst,NULL,*(Uint32*)src->pixels);
	}
      else
	{
	  /* Target surface is 8bit */
	  rz_dst =
	    SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 8, 0, 0,
				  0, 0);
    	    //patch for colorkey setted
	    if (colorkey!=-1)
		SDL_FillRect(rz_dst,NULL,colorkey);
	    else
		SDL_FillRect(rz_dst,NULL,*(Uint8 *)src->pixels);
	}

      /* Lock source surface */
      SDL_LockSurface (rz_src);
      /* Check which kind of surface we have */
      if (is32bit)
	{
	  /* Call the 32bit transformation routine to do the rotation (using alpha) */
	  transformSurfaceRGBA (rz_src, rz_dst, dstwidthhalf, dstheighthalf,
				(int) (sanglezoominv),
				(int) (canglezoominv), smooth);
	  /* Turn on source-alpha support */
	  SDL_SetAlpha (rz_dst, SDL_SRCALPHA, 255);
	}
      else
	{
	  /* Copy palette and colorkey info */
	  for (i = 0; i < rz_src->format->palette->ncolors; i++)
	    {
	      rz_dst->format->palette->colors[i] =
		rz_src->format->palette->colors[i];
	    }
	  rz_dst->format->palette->ncolors = rz_src->format->palette->ncolors;
	  /* Call the 8bit transformation routine to do the rotation */
	  transformSurfaceY (rz_src, rz_dst, dstwidthhalf, dstheighthalf,
			     (int) (sanglezoominv), (int) (canglezoominv));
	  SDL_SetColorKey (rz_dst, SDL_SRCCOLORKEY| SDL_RLEACCEL ,rz_src->format->colorkey);
	}
      /* Unlock source surface */
      SDL_UnlockSurface (rz_src);

    }
  else
    {

      /* Angle=0: Just a zoom */
      /* -------------------- */

      /* Calculate target size and set rect */
      dstwidth = (int) ((double) rz_src->w * zoom);
      dstheight = (int) ((double) rz_src->h * zoom);
      if (dstwidth < 1)
	{
	  dstwidth = 1;
	}
      if (dstheight < 1)
	{
	  dstheight = 1;
	}

      /* Alloc space to completely contain the zoomed surface */
      rz_dst = NULL;
      if (is32bit)
	{
	  /* Target surface is 32bit with source RGBA/ABGR ordering */
	  rz_dst =
	    SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 32,
				  rz_src->format->Rmask,
				  rz_src->format->Gmask,
				  rz_src->format->Bmask,
				  rz_src->format->Amask);
	    //patch for colorkey setted
	    if (colorkey!=-1)
		SDL_FillRect(rz_dst,NULL,colorkey);
	    else
		SDL_FillRect(rz_dst,NULL,*(Uint32 *)src->pixels);
	}
      else
	{
	  /* Target surface is 8bit */
	  rz_dst =
	    SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 8, 0, 0,
				  0, 0);
	    	    //patch for colorkey setted
	    if (colorkey!=-1)
		SDL_FillRect(rz_dst,NULL,colorkey);
	    else
		SDL_FillRect(rz_dst,NULL,*(Uint8 *)src->pixels);

	}

      /* Lock source surface */
      SDL_LockSurface (rz_src);
      /* Check which kind of surface we have */
      if (is32bit)
	{
	  /* Call the 32bit transformation routine to do the zooming (using alpha) */
	  zoomSurfaceRGBA (rz_src, rz_dst, smooth);
	  /* Turn on source-alpha support */
	  SDL_SetAlpha (rz_dst, SDL_SRCALPHA, 255);
	}
      else
	{
	  /* Copy palette and colorkey info */
	  for (i = 0; i < rz_src->format->palette->ncolors; i++)
	    {
	      rz_dst->format->palette->colors[i] =
		rz_src->format->palette->colors[i];
	    }
	  rz_dst->format->palette->ncolors = rz_src->format->palette->ncolors;
	  /* Call the 8bit transformation routine to do the zooming */
	  zoomSurfaceY (rz_src, rz_dst);
	  SDL_SetColorKey (rz_dst, SDL_SRCCOLORKEY| SDL_RLEACCEL, rz_src->format->colorkey);
	}
      /* Unlock source surface */
      SDL_UnlockSurface (rz_src);
    }

  /* Cleanup temp surface */
  if (src_converted)
    {
      SDL_FreeSurface (rz_src);
	rz_src=NULL;
    }

  /* Return destination surface */

  return (rz_dst);
}
//________________________________________________________________________________________________________________________________________

/*
 zoomSurface()
 Zoomes a 32bit or 8bit 'src' surface to newly created 'dst' surface.
 'zoomx' and 'zoomy' are scaling factors for width and height. If 'smooth' is 1
 then the destination 32bit surface is anti-aliased. If the surface is not 8bit
 or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.
*/

#define VALUE_LIMIT	0.001

SDL_Surface *zoomSurface (SDL_Surface * src, double zoomx, double zoomy, int smooth)
{
  SDL_Surface *rz_src;
  SDL_Surface *rz_dst;
  int dstwidth, dstheight;
  int is32bit;
  int i, src_converted;

  /* Sanity check */
  if (src == NULL)
    return (NULL);

  /* Determine if source surface is 32bit or 8bit */
  is32bit = (src->format->BitsPerPixel == 32);
  if ((is32bit) || (src->format->BitsPerPixel == 8))
    {
      /* Use source surface 'as is' */
      rz_src = src;
      src_converted = 0;
    }
  else
    {
      /* New source surface is 32bit with a defined RGBA ordering */
      rz_src =
	SDL_CreateRGBSurface (SDL_SWSURFACE, src->w, src->h, 32, 0x000000ff,
			      0x0000ff00, 0x00ff0000, 0xff000000);
      SDL_BlitSurface (src, NULL, rz_src, NULL);
      src_converted = 1;
      is32bit = 1;
    }

  /* Sanity check zoom factors */
  if (zoomx < VALUE_LIMIT)
    {
      zoomx = VALUE_LIMIT;
    }
  if (zoomy < VALUE_LIMIT)
    {
      zoomy = VALUE_LIMIT;
    }

  /* Calculate target size and set rect */
  dstwidth = (int) ( rz_src->w * zoomx);//(double)
  dstheight = (int) ( rz_src->h * zoomy);//(double)
  if (dstwidth < 1)
    {
      dstwidth = 1;
    }
  if (dstheight < 1)
    {
      dstheight = 1;
    }

  /* Alloc space to completely contain the zoomed surface */
  rz_dst = NULL;
  if (is32bit)
    {
      /* Target surface is 32bit with source RGBA/ABGR ordering */
      rz_dst =
	SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 32,
			      rz_src->format->Rmask, rz_src->format->Gmask,
			      rz_src->format->Bmask, rz_src->format->Amask);
    }
  else
    {
      /* Target surface is 8bit */
      rz_dst =
	SDL_CreateRGBSurface (SDL_SWSURFACE, dstwidth, dstheight, 8, 0, 0, 0,
			      0);
    }

  /* Lock source surface */
  SDL_LockSurface (rz_src);
  /* Check which kind of surface we have */
  if (is32bit)
    {
      /* Call the 32bit transformation routine to do the zooming (using alpha) */
      zoomSurfaceRGBA (rz_src, rz_dst, smooth);
      /* Turn on source-alpha support */
      SDL_SetAlpha (rz_dst, SDL_SRCALPHA, 255);
    }
  else
    {
      /* Copy palette and colorkey info */
      for (i = 0; i < rz_src->format->palette->ncolors; i++)
	{
	  rz_dst->format->palette->colors[i] =
	    rz_src->format->palette->colors[i];
	}
      rz_dst->format->palette->ncolors = rz_src->format->palette->ncolors;
      /* Call the 8bit transformation routine to do the zooming */
      zoomSurfaceY (rz_src, rz_dst);
      SDL_SetColorKey (rz_dst, SDL_SRCCOLORKEY| SDL_RLEACCEL, rz_src->format->colorkey);
    }
  /* Unlock source surface */
  SDL_UnlockSurface (rz_src);

  /* Cleanup temp surface */
  if (src_converted)
    {
      SDL_FreeSurface (rz_src);
	rz_src=NULL;
    }

/* Return destination surface */
  return (rz_dst);
}
//________________________________________________________________________________________________________________________________________

/*
	This code was extracted from fade tutorial written by PatricK Kooman
*/

/* Fades the given surface in or out to the given screen within the given time
 If the image surface is the screen surface (pointer are equal), a copy is made
 first. We must do that because we are overwriting the Screen Surface. */


void fade (int s, SDL_Surface* in_p_surf_screen, SDL_Surface* in_p_surf_img, Uint32 in_ui_seconds, int in_b_fade_out)
{
    /* copy the parameters in stared variables */
    p_surf_screen[s]=in_p_surf_screen;
    p_surf_img[s]=in_p_surf_img;
    ui_seconds[s]=in_ui_seconds;
    b_fade_out[s]=in_b_fade_out;


    /* initialize vars */
    p_surf_black[s] = NULL;
    p_surf_screen_copy[s] = NULL;
    ui_flags[s] = SDL_SRCALPHA|SDL_RLEACCEL;

  /* Create the black surface in the format of the given screen */
  if ((p_surf_screen[s]->flags & SDL_HWSURFACE)) {
    ui_flags[s] |= SDL_HWSURFACE ;
  }
  else {
    ui_flags[s] |= SDL_SWSURFACE ;
  }
  if ((p_surf_black[s] = SDL_CreateRGBSurface (ui_flags[s],
    p_surf_screen[s]->w, p_surf_screen[s]->h,
    p_surf_screen[s]->format->BitsPerPixel,
    p_surf_screen[s]->format->Rmask, p_surf_screen[s]->format->Gmask, p_surf_screen[s]->format->Bmask,
    p_surf_screen[s]->format->Amask)) == NULL) {
      /* Replace this line with you own error handling / logging */
	error_description="SDLengine error fade: could not create the black Surface";
	error_type=1;
      fprintf (stderr, "fade: could not create the black Surface. (%s)\n", SDL_GetError ()) ;
      return ;
  }
  /* Fill the Surface with black */
  SDL_FillRect (p_surf_black[s], NULL, SDL_MapRGB (p_surf_screen[s]->format, 0, 0, 0)) ;
  /* Should we make a copy of the Screen? */
  if (p_surf_screen[s] == p_surf_img[s]) {
    if ((p_surf_screen_copy[s] = SDL_CreateRGBSurface (ui_flags[s],
    p_surf_screen[s]->w, p_surf_screen[s]->h,
    p_surf_screen[s]->format->BitsPerPixel,
    p_surf_screen[s]->format->Rmask, p_surf_screen[s]->format->Gmask, p_surf_screen[s]->format->Bmask,
    p_surf_screen[s]->format->Amask)) == NULL) {
      /* Replace this line with you own error handling / logging */
	error_description="SDLengine error fade: could not create a copy of the Screen Surface";
	error_type=1;
      fprintf (stderr, "fade: could not create a copy of the Screen Surface. (%s)\n", SDL_GetError ()) ;
      SDL_FreeSurface (p_surf_black[s]) ;
      return ;
    }
    /* Ok, copy surfaces and set surfact pointer */
    SDL_BlitSurface (p_surf_screen[s], NULL, p_surf_screen_copy[s], NULL) ;
    p_surf_img[s] = p_surf_screen_copy[s] ;
  }

  	/* Ok, we are now ready for the fade. These are the steps (looped):
	1. Draw p_surf_img onto p_surf_screen, just an ordinary blit.
	2. Decrease or increase (depends on fading in or out) the alpha value,
	based on the elapsed time since the previous loop-iteration.
	3. Draw p_surf_black onto p_surf_screen in the current alpha value.*/
	ui_old_time[s] = SDL_GetTicks () ;
	ui_curr_time[s] = ui_old_time[s] ;
	/* Convert the given time in seconds into miliseconds. */
	ui_time_ms[s] = ui_seconds[s] * 1000 ;


  if (b_fade_out[s])
    f_alpha[s] = 0.0 ;
  else
    f_alpha[s] = 255.0 ;

  fadeflag[s]=1;
  fadedelay[s]=SDL_GetTicks()+5;
}

void fadehandler(int s)
 {
  if (b_fade_out[s]){
    /* Draw the image onto the screen */
    SDL_BlitSurface (p_surf_img[s], NULL, p_surf_screen[s], NULL) ;
    /* Draw the black surface onto the screen */
    SDL_SetAlpha (p_surf_black[s], SDL_SRCALPHA|SDL_RLEACCEL, (Uint8) f_alpha[s]) ;
    SDL_BlitSurface (p_surf_black[s], NULL, p_surf_screen[s], NULL) ;
    /* Update the timer variables */
    ui_old_time[s] = ui_curr_time[s] ;
    ui_curr_time[s] = SDL_GetTicks();
    /* Flip the screen Surface */
    SDL_Flip (p_surf_screen[s]) ;
    /* Calculate the next alpha value */
    f_alpha[s] += (255.0 * ((double) (ui_curr_time[s] - ui_old_time[s]) / ui_time_ms[s])) ;
    //printf("%f %d %d %d \n",f_alpha, ui_curr_time, ui_old_time, ui_time_ms);
    if (f_alpha[s] >= 255.0)
	fadeflag[s]=0;
  }
  else {

      /* Draw the image onto the screen */
      SDL_BlitSurface (p_surf_img[s], NULL, p_surf_screen[s], NULL) ;
      /* Draw the black surface onto the screen */
      SDL_SetAlpha (p_surf_black[s], SDL_SRCALPHA|SDL_RLEACCEL, (Uint8) f_alpha[s]) ;
      SDL_BlitSurface (p_surf_black[s], NULL, p_surf_screen[s], NULL) ;
      /* Update the timer variables */
      ui_old_time[s] = ui_curr_time[s] ;
      ui_curr_time[s] = SDL_GetTicks() ;
      /* Flip the screen Surface */
      SDL_Flip (p_surf_screen[s]) ;
      /* Calculate the next alpha value */
      f_alpha[s] -= 255 * ((double) (ui_curr_time[s] - ui_old_time[s]) / ui_time_ms[s]) ;
      if (f_alpha[s] <= 0.0)
	  fadeflag[s]=0;
  }
  if (fadeflag[s]==0){
  /* Free the black Surface */
  SDL_FreeSurface (p_surf_black[s]) ;
  /* Free the Screen copy, if used */
  if (p_surf_screen_copy[s] != NULL) {
    SDL_FreeSurface (p_surf_screen_copy[s]) ;
  }
  }
    screenswap();
}
//________________________________________________________________________________________________________________________________________

/* Cross-Fades the given surfaces onto the given screen within the given time
 If the image surface is the screen surface (pointer are equal), a copy is made
 first. We must do that because we are overwriting the Screen Surface. */

void crossfade (int s, SDL_Surface* in_p_surf_screen, SDL_Surface* in_p_surf_img1, SDL_Surface* in_p_surf_img2, Uint32 in_ui_seconds)
{
    p_surf_screen[s]=in_p_surf_screen;
    p_surf_img1[s]=in_p_surf_img1;
    p_surf_img2[s]=in_p_surf_img2;
    ui_seconds[s]=in_ui_seconds;

  /* These are the steps to perform a cross-fade (looped):
  1. Draw p_surf_img1 onto p_surf_screen, just an ordinary blit.
  2. Increase the alpha value, based on the elapsed time since the previous loop-iteration.
  3. Draw p_surf_img2 onto p_surf_screen in the current alpha value.*/

 /* Convert the given time in seconds into miliseconds. */
  ui_time_ms[s] = ui_seconds[s] * 1000 ;

  ui_old_time[s] = SDL_GetTicks () ;
  ui_curr_time[s] = ui_old_time[s] ;

    f_alpha[s] = 0.0 ;

  crossfadeflag[s]=1;
  fadedelay[s]=SDL_GetTicks()+5;

}

void crossfadehandler(int s)
{

    /* Draw the image onto the screen */
    SDL_BlitSurface (p_surf_img1[s], NULL, p_surf_screen[s], NULL) ;
    /* Draw the black surface onto the screen */
    SDL_SetAlpha (p_surf_img2[s], SDL_SRCALPHA, (Uint8) f_alpha[s]) ;
    SDL_BlitSurface (p_surf_img2[s], NULL, p_surf_screen[s], NULL) ;
    /* Update the timer variables */
    ui_old_time[s] = ui_curr_time[s];
    ui_curr_time[s] = SDL_GetTicks();
    /* Flip the screen Surface */
    SDL_Flip (p_surf_screen[s]) ;
    /* Calculate the next alpha value */
    f_alpha[s] += (255.0 * ((double) (ui_curr_time[s] - ui_old_time[s]) / ui_time_ms[s])) ;

    screenswap();

    if (f_alpha[s] >=255.0)
	crossfadeflag[s]=0;
}
//________________________________________________________________________________________________________________________________________

// hit_pixelperfect(SDLbobfr[n],xa1,ya1,xa2,ya2,SDLbobfr[x],xb1,yb1,xb2,yb2)	:rutine with graphic image precision collision
int hit_pixelperfect(SDL_Surface *imga,int xa1,int ya1,int xa2,int ya2,SDL_Surface *imgb,int xb1,int yb1,int xb2,int yb2)
{
    int xaa,yaa,xbb,ybb;
    int xw,yh;
    int x,y;
    int cc;


    xaa=0;
    xbb=0;
    if (xa1<xb1)
	xaa=MAX(xa1,xb1)-MIN(xa1,xb1);
    else
	xbb=MAX(xa1,xb1)-MIN(xa1,xb1);

    yaa=0;
    ybb=0;
   if (ya1<yb1)
	yaa=MAX(ya1,yb1)-MIN(ya1,yb1);
    else
	ybb=MAX(ya1,yb1)-MIN(ya1,yb1);

    xw=MIN(xa2,xb2)-MAX(xa1,xb1);
    yh=MIN(ya2,yb2)-MAX(ya1,yb1);


    if (SDL_MUSTLOCK(imga)){
		SDL_LockSurface(imga);
		SDL_LockSurface(imgb);
	}

    cc=colorkey;
    if (cc==-1)cc=getpixel(imga,0,0);


    for (y=0; y<yh; y++){
	for (x=0; x<xw; x++){
	    if (getpixel(imga,xaa+x,yaa+y)!=cc){
		if(getpixel(imgb,xbb+x,ybb+y)!=cc){
		    if (SDL_MUSTLOCK(imga)){
			SDL_UnlockSurface(imga);
			SDL_UnlockSurface(imgb);
		    }
		    return 1;
		}
	    }
	}
    }

    if (SDL_MUSTLOCK(imga)){
		SDL_UnlockSurface(imga);
		SDL_UnlockSurface(imgb);
	}
    return 0;
}
//________________________________________________________________________________________________________________________________________

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */

Uint32 getpixel8(SDL_Surface *surface, int x, int y)
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
	p=(Uint8 *)surface->pixels + y * surface->pitch + x ;
	return *(Uint8 *)p;
    }
    else
	return 0;
}

Uint32 getpixel16(SDL_Surface *surface, int x, int y)
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
	p=(Uint8 *)surface->pixels + y * surface->pitch + x * 2;
	return *(Uint16 *)p;
    }
    else
	return 0;
}

Uint32 getpixel24BE(SDL_Surface *surface, int x, int y)
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
	p=(Uint8 *)surface->pixels + y * surface->pitch + x * 3;
	return p[0] << 16 | p[1] << 8 | p[2];
    }
    else
	return 0;
}

Uint32 getpixel24(SDL_Surface *surface, int x, int y)
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
	p=(Uint8 *)surface->pixels + y * surface->pitch + x * 3;
	return p[0] | p[1] << 8 | p[2] << 16;
    }
    else
	return 0;
}

Uint32 getpixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
	p=(Uint8 *)surface->pixels + y * surface->pitch + x * 4;
	return *(Uint32 *)p;
    }
    else
	return 0;
}

//________________________________________________________________________________________________________________________________________

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */

void putpixel8(SDL_Surface *surface, int x, int y, Uint32 col )
{
    Uint8 *p;
	if (x>=0 && y>=0 && x<surface->w && y<surface->h){
		p=(Uint8 *)surface->pixels + (y * surface->pitch) + x ;
		*p= col;
	}
}

void putpixel16(SDL_Surface *surface, int x, int y, Uint32 col )
{
    Uint8 *p;
	if (x>=0 && y>=0 && x<surface->w && y<surface->h){
		p=(Uint8 *)surface->pixels + (y * surface->pitch) + x * 2;
		*(Uint16 *)p=col;
	}
}

void putpixel24BE(SDL_Surface *surface, int x, int y, Uint32 col )
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
		p=(Uint8 *) surface->pixels + (y * surface->pitch) + x * 3;
		p[0] = (col >> 16) & 0xff;
		p[1] = (col >> 8) & 0xff;
		p[2] = col & 0xff;
    }

}

void putpixel24(SDL_Surface *surface, int x, int y, Uint32 col )
{
    Uint8 *p;
    if (x>=0 && y>=0 && x<surface->w && y<surface->h){
		p=(Uint8 *)surface->pixels + (y * surface->pitch) + x * 3;
		p[0] = col & 0xff;
		p[1] = (col >> 8) & 0xff;
		p[2] = (col >> 16) & 0xff;
    }

}

void putpixel32(SDL_Surface *surface, int x, int y, Uint32 col )
{
    Uint8 *p;
	if (x>=0 && y>=0 && x<surface->w && y<surface->h){
		p=(Uint8 *)surface->pixels + (y * surface->pitch) + x * 4;
		*(Uint32 *)p=col;
	}
}

void putpixelDX(SDL_Surface *surface, int x, int y, Uint32 col )
{
    // rettangolo di un pixel di lato
    SDL_Rect d;

    d.x=x;
    d.y=y;
    d.w=1;
    d.h=1;
    SDL_FillRect (surface, &d, col);
}


//}
//________________________________________________________________________________________________________________________________________

/*  Draw a line to use with other function like rect) */
void draw_line(SDL_Surface * surface,int x1, int y1, int x2, int y2, Uint32 color)
{
    //  Draw a line WITHOUT REFRESH VIDEO (to use with other function like rect)
    static int c,x,y;
    double slope;

    int dx = x2 - x1;  /* change in x */
    int dy = y2 - y1;  /* change in y */

    slope = (double)dy / dx;

    if (abs(dx) >= abs(dy)) {
        /* draw left/right - right/left */
        c = (x1 <= x2) ? 1 : -1;
        for (x = x1; x != x2 + c; x += c) {
            y = y1 + (int)( (x - x1) * slope + 0.5 );
            putpixel(surface, x, y, color);
        }
    }
    else
    {
        /* draw top/bottom - bottom/top */
        c = (y1 <= y2) ? 1 : -1;
        for (y = y1; y != y2 + c; y += c) {
            x = x1 + (int)( (y - y1) / slope + 0.5 );
            putpixel(surface, x, y, color);
        }
    }
}
//________________________________________________________________________________________________________________________________________

/* draw empty rect */
void draw_box(SDL_Surface *surface,int x1,int y1,int x2,int y2,Uint32 color)
{
int i;
for(i=x1;i<=x2;i++){putpixel(surface,i,y1,color);putpixel(surface,i,y2,color);}
for(i=y1;i<=y2;i++){putpixel(surface,x1,i,color);putpixel(surface,x2,i,color);}
}
//________________________________________________________________________________________________________________________________________

/*draw empty circle */
void draw_circle(SDL_Surface *surface,int vx,int vy, int r,Uint32 color)
{

  Sint16 x = 0;
  Sint16 y = r-1;     /*radius zero == draw nothing*/
  Sint16 d = 3 - 2*r;
  Sint16 diagonalInc = 10 - 4*r;
  Sint16 rightInc = 6;

  while (x <= y) {

    putpixel(surface,vx+x,vy+y,color);
    putpixel(surface,vx+x,vy-y,color);
    putpixel(surface,vx-x,vy+y,color);
    putpixel(surface,vx-x,vy-y,color);

    putpixel(surface,vx+y,vy+x,color);
    putpixel(surface,vx+y,vy-x,color);
    putpixel(surface,vx-y,vy+x,color);
    putpixel(surface,vx-y,vy-x,color);


  if (d >=  0) {
      d += diagonalInc;
      diagonalInc += 8;
      y -= 1;
    } else {
      d += rightInc;
      diagonalInc += 4;
    }
    rightInc += 4;
    x += 1;
  }
}
//________________________________________________________________________________________________________________________________________

/* draw fill circle */
void draw_fillcircle(SDL_Surface *surface,int vx,int vy, int r,Uint32 color)
{

  Sint16 x = 0;
  Sint16 y = r-1;     /*radius zero == draw nothing*/
  Sint16 d = 3 - 2*r;
  Sint16 diagonalInc = 10 - 4*r;
  Sint16 rightInc = 6;

  while (x <= y) {

    draw_line(surface,vx+x,vy+y,vx-x,vy+y,color);
    draw_line(surface,vx+x,vy-y,vx-x,vy-y,color);
    draw_line(surface,vx+y,vy+x,vx-y,vy+x,color);
    draw_line(surface,vx+y,vy-x,vx-y,vy-x,color);

  if (d >=  0) {
      d += diagonalInc;
      diagonalInc += 8;
      y -= 1;
    } else {
      d += rightInc;
      diagonalInc += 4;
    }
    rightInc += 4;
    x += 1;
  }
}
//________________________________________________________________________________________________________________________________________

/* draw empty ellipse */
void draw_ellipse(SDL_Surface *surface,int vx,int vy,int Xradius,int Yradius,Uint32 color)
{
  Sint32 x, y;
  Sint32 Xchange, Ychange;
  Sint32 EllipseError;
  Sint32 TwoASquare, TwoBSquare;
  Sint32 StoppingX, StoppingY;

  TwoASquare = 2*Xradius*Xradius;
  TwoBSquare = 2*Yradius*Yradius;

  /*1st set of points*/
  x = Xradius-1;  /*radius zero == draw nothing*/
  y = 0;

  Xchange = Yradius*Yradius*(1-2*Xradius);
  Ychange = Xradius*Xradius;

  EllipseError = 0;

  StoppingX = TwoBSquare*Xradius;
  StoppingY = 0;

  /*Plot four ellipse points by iteration*/
  while (StoppingX > StoppingY) {

    putpixel(surface,vx+x,vy+y,color);
    putpixel(surface,vx+x,vy-y,color);
    putpixel(surface,vx-x,vy+y,color);
    putpixel(surface,vx-x,vy-y,color);


    ++y;
    StoppingY    += TwoASquare;
    EllipseError += Ychange;
    Ychange      += TwoASquare;
    if (( 2*EllipseError + Xchange) > 0) {
      --x;
      StoppingX    -= TwoBSquare;
      EllipseError += Xchange;
      Xchange      += TwoBSquare;
    }
  }/*while*/

  /*2nd set of points*/
  x = 0;
  y = Yradius-1;  /*radius zero == draw nothing*/
  Xchange = Yradius*Yradius;
  Ychange = Xradius*Xradius*(1-2*Yradius);
  EllipseError = 0;
  StoppingX = 0;
  StoppingY = TwoASquare*Yradius;

  /*Plot four ellipse points by iteration*/
  while (StoppingX < StoppingY) {

    putpixel(surface,vx+x,vy+y,color);
    putpixel(surface,vx+x,vy-y,color);
    putpixel(surface,vx-x,vy+y,color);
    putpixel(surface,vx-x,vy-y,color);

    ++x;
    StoppingX    += TwoBSquare;
    EllipseError += Xchange;
    Xchange      += TwoBSquare;
    if ((2*EllipseError + Ychange) > 0) {
      --y;
      StoppingY    -= TwoASquare;
      EllipseError += Ychange;
      Ychange      += TwoASquare;
    }
  }
}
//________________________________________________________________________________________________________________________________________

/* draw fill ellipse */
void draw_fillellipse(SDL_Surface *surface,int vx,int vy,int Xradius,int Yradius,Uint32 color)
{
  Sint32 x, y;
  Sint32 Xchange, Ychange;
  Sint32 EllipseError;
  Sint32 TwoASquare, TwoBSquare;
  Sint32 StoppingX, StoppingY;

  TwoASquare = 2*Xradius*Xradius;
  TwoBSquare = 2*Yradius*Yradius;

  /*1st set of points*/
  x = Xradius-1;  /*radius zero == draw nothing*/
  y = 0;

  Xchange = Yradius*Yradius*(1-2*Xradius);
  Ychange = Xradius*Xradius;

  EllipseError = 0;

  StoppingX = TwoBSquare*Xradius;
  StoppingY = 0;

  /*Plot four ellipse points by iteration*/
  while (StoppingX > StoppingY) {

    draw_line(surface,vx+x,vy+y,vx-x,vy+y,color);
    draw_line(surface,vx+x,vy-y,vx-x,vy-y,color);


    ++y;
    StoppingY    += TwoASquare;
    EllipseError += Ychange;
    Ychange      += TwoASquare;
    if (( 2*EllipseError + Xchange) > 0) {
      --x;
      StoppingX    -= TwoBSquare;
      EllipseError += Xchange;
      Xchange      += TwoBSquare;
    }
  }/*while*/

  /*2nd set of points*/
  x = 0;
  y = Yradius-1;  /*radius zero == draw nothing*/
  Xchange = Yradius*Yradius;
  Ychange = Xradius*Xradius*(1-2*Yradius);
  EllipseError = 0;
  StoppingX = 0;
  StoppingY = TwoASquare*Yradius;

  /*Plot four ellipse points by iteration*/
  while (StoppingX < StoppingY) {

    draw_line(surface,vx+x,vy+y,vx-x,vy+y,color);
    draw_line(surface,vx+x,vy-y,vx-x,vy-y,color);

    ++x;
    StoppingX    += TwoBSquare;
    EllipseError += Xchange;
    Xchange      += TwoBSquare;
    if ((2*EllipseError + Ychange) > 0) {
      --y;
      StoppingY    -= TwoASquare;
      EllipseError += Ychange;
      Ychange      += TwoASquare;
    }
  }
}
//________________________________________________________________________________________________________________________________________

// xrgb for internal use

/*
// this version was suggested from Paulo Silva still have problem of color in my machine
Uint32  xrgb8(int colR,int colG,int colB)
{
    return ((colR/43)*36) + ((colG/43)*6) + (colB/43);
}
//*/

//*
Uint32 xrgb8(int colR,int colG,int colB)
{
    if (enablePalette==2)return colB;
    else return (colB/64) + ((colG/64) * 8)+((colR/64)*8*8);
}
//*/

Uint32 xrgb16(int colR,int colG,int colB)
{
    return (colB/8) + ((colG/8) * 64)+((colR/8)*64*32);
}

Uint32 xrgb24(int colR,int colG,int colB)
{
    return colB + (colG * 256)+(colR*256*256);
}

Uint32 xrgb32(int colR,int colG,int colB)
{
    return  colB + (colG * 256)+(colR*256*256);
}


//________________________________________________________________________________________________________________________________________

// rrgb for internal use

/*
// this version was suggested from Paulo Silva still have problem of color in my machine
Uint32 rrgb8(int col)
{
    int colR,colG,colB;
    colB = (col & 6)*51;
    colG =((col / 6) & 6)*51 ;
    colR =((col / 36) & 6)*51;
    return colB + (colG * 256)+(colR*256*256);
}
//*/

//*
Uint32 rrgb8(int col)
{
    int colR,colG,colB;
    colB = (col & 3)*64;
    colG =((col / 8) & 3)*64 ;
    colR =((col / (8*8)) & 3)*64;
    if (enablePalette==2)return colB;
    else return colB + (colG * 256)+(colR*256*256);
}
//*/

Uint32 rrgb16(int col)
{
    int colR,colG,colB;
    colB = (col & 31) *8;
    colG =((col/32) & 31) *8;
    colR =((col/(64*32)) & 31)*8;
    return colB + (colG * 256)+(colR*256*256);
}

Uint32 rrgb24(int col)
{
    return col;
}

Uint32 rrgb32(int col)
{
    return col;
}

//________________________________________________________________________________________________________________________________________

//createfont: make a monospace font and set at 0,0 the cursor coordinates for internal use
int createfont()
{
	int i;
	paper(0);
	pen(rgb(255,255,255));
	for (i=0;i<NUM_SCREENS;i++){
		stx[c_screen]=0;
		sty[c_screen]=0;
	}
	return 0;
}
//________________________________________________________________________________________________________________________________________

//print one char at current coordinates for internal use
int put_char(unsigned char n)
{
    SDL_Rect s;
    SDL_Rect d;
    SDL_Color oldc;


    oldc=SDLcol;

    if (n==13){
	stx[c_screen]=0;
	sty[c_screen]+=1;
	n=0;
    }
    else{
	ink (paper_color);
	bar(stx[c_screen]*XPRINT_SIZE,2+sty[c_screen]*(PRINT_SIZE+1),stx[c_screen]*XPRINT_SIZE+XPRINT_SIZE,2+sty[c_screen]*(PRINT_SIZE+1)+PRINT_SIZE);

	if (SDLfont_mono[n]!=NULL){
			s.x=0;
			s.y=0;
			s.w=XPRINT_SIZE-1;
			s.h=SDLfont_mono[n]->h;

			d.x=stx[c_screen]*XPRINT_SIZE;
			d.y=sty[c_screen]*(PRINT_SIZE+1);
			d.w=SDLfont_mono[n]->w;
			d.h=SDLfont_mono[n]->h;

			SDL_BlitSurface(SDLfont_mono[n], &s, SDLscreen[c_screen], &d );
	}

	stx[c_screen]=stx[c_screen]+1;
	if (stx[c_screen]+1>(screenwidth()/XPRINT_SIZE)){
			stx[c_screen]=0;
			sty[c_screen]=sty[c_screen]+1;
	}

    }

    if (sty[c_screen]+1>(screenheight()/(PRINT_SIZE+1))){
	screenswap();
	screencopy(c_screen,0,PRINT_SIZE,screenwidth(),screenheight()-(PRINT_SIZE+1),c_screen,0,0);
	ink(paper_color);
	bar(0,screenheight()-(PRINT_SIZE+1),screenwidth(),screenheight());

	sty[c_screen]=sty[c_screen]-1;
	screenswap();
    }

	SDLcol=oldc;
	return 0;
}
//________________________________________________________________________________________________________________________________________

/* make a cursor */
int createcursor()
{
	int i;
	int old_pen;

	old_pen=pen(-1);
	for (i=0; i<16;i++) {
		pen(rgb(i*15,i*15,0));
		SDL_FreeSurface(SDLcursore[i]);
		SDLcursore[i] =SDL_DisplayFormat( SDLfont_mono[95]);
	}
	pen(old_pen);
	return 0;
}
//________________________________________________________________________________________________________________________________________

/*
this was my very old rutines for input used in 1995 on borland tc turbovision replacement project adapted
on SDLengine
*/
void _input(char *instring,int x, int y,int displen)
{
    #define k_delete	127
    #define k_up   		273
    #define k_down  	274
    #define k_right 	275
    #define k_left  	276
    #define k_insert  	277
    #define k_home  	278
    #define k_end  		279
    #define k_pageup  	280
    #define k_pagedown  	281

    int i,n;
    int p,p1,pdisp;
    char provstring[255];
    char dispstring[255];
    int px;

    p=0;
    pdisp=0;
    strcpy(provstring,instring);
    p=strlen(provstring);
    provstring[p+1]=0;

    if ((p-pdisp)>displen)pdisp=p-displen;
    if ((p-pdisp)<0)pdisp=p;

    strncpy(dispstring, provstring+pdisp, displen);

    locate(x,y);fprints(dispstring);
    do{
	while (inkey()!=0);

	n=0;
	while(n==0){
	    px=(p-pdisp);//*xdf;
	    locate(x+px,y);
	    n=inkey();
	    if (key(k_left)){
		n=0;
		if(p>0){
		    p--;
		}
		while(key(k_left));
		break;
	    } //cleft

	    if (key(k_right)){
		n=0;
		if(p<strlen(provstring)){
		    p++;
		}
		while(key(k_right));
		break;

	    } //crigth

	    if (key(k_delete)){
		n=0;
		if(p<strlen(provstring))memcpy(provstring+p,provstring+p+1,strlen(provstring)-p);
		while(key(k_delete));
		break;
	    } //cancel

	    if (key(k_home)){p=0;n=0;break;}//inizio
	    if (key(k_end)){p=strlen(provstring);n=0;break;}//fine
	}

	if (n==13)break;

	if (n==8){
	    n=0;
	    if (p>0){
		for(i=p;i<strlen(provstring)+1;i++)
		    provstring[i-1]=provstring[i];
		p--;
	    }
	}//backdel

	if (n==127){
		if(p<strlen(provstring)){
		    for(i=p;i<strlen(provstring);i++)
			provstring[i]=provstring[i+1];
		}
	     n=0;
	}//delete

	if (n!=0 && strlen(provstring)<254){
	    for(p1=strlen(provstring);p1>=p;p1--)
		provstring[p1+1]=provstring[p1];
	    provstring[p]=n;
	    p++;

	}

	if ((p-pdisp)>displen)pdisp=p-displen;
	if ((p-pdisp)<0)pdisp=p;

	strncpy(dispstring,provstring+pdisp,displen);

	locate(x+strlen(dispstring),y);
	if(n==0)fprints(" ");
	if (n!=0 && stx[c_screen]==0 && (sty[c_screen]+2)>(screenheight()/(PRINT_SIZE))){
	    prints(" ");
	    y=y-2;
	}

	i=0;
	locate(x,y);
	fprints(dispstring);
	screenswap();

    }
    while (n !=13);
    strcpy (instring,provstring);
}
//_______________________________________________________________________________________________________________________

