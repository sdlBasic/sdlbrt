//_________________________________________________________________________________________________________________________
//
//---- SDLengine --------------------------------------------------------------------------------------------------
//_________________________________________________________________________________________________________________________
// Screen
void basSetDefaults(void);
void basSetDisplay(void);
void basSetAlphaChannel(void);
void basSetCaption(void);
void basCaption(void);

void basSystemWidth(void);
void basSystemHeight(void);
void basDisplayMode(void);
void basDisplayWidth(void);
void basDisplayHeight(void);
void basDisplayBpp(void);

void basScreen(void);
void basScreenZ(void);
void basLastScreen(void);
void basDirectScreen(void);

void basScreenOpen(void);
void basScreenClose(void);
void basScreenClone(void);

void basScreenCopy(void);
void basScreenFade(void);
void basScreenFadein(void);
void basScreenCrossFade(void);
void basScreenAlpha(void);
void basScreenLock(void);
void basScreenUnlock(void);

void basScreenRect(void);
void basXScreenRect(void);
void basYScreenRect(void);
void basWScreenRect(void);
void basHScreenRect(void);
void basFlagScreenRect(void);

void basScreenWidth(void);
void basScreenHeight(void);

void basOffset(void);
void basXOffset(void);
void basYOffset(void);

void basCls(void);
void basScreenSwap(void);
void basAutoBack(void);
void basDualPlayfield(void);
void basWaitVbl(void);
void basFps(void);
//_________________________________________________________________________________________________________________________
// Graphics
void basRgb(void);
void basEnablePalette(void);
void basColor(void);
void basPalette(void);
void basColorCycling(void);
void basInk(void);

void basPoint(void);
void basDot(void);
void basPlot(void);
void basLine(void);
void basBox(void);
void basBar(void);
void basRectangle(void);
void basCircle(void);
void basFillCircle(void);
void basEllipse(void);
void basFillEllipse(void);
void basPaint(void);
void basTriangle(void);
void basPolyLine(void);
void basPolyGon(void);

//_________________________________________________________________________________________________________________________
// File graphics input output
void basLoadImage(void);
void basLoadZipImage(void);
void basSaveImage(void);
void basLoadSound(void);
void basLoadZipSound(void);
void basSaveSound(void);
void basLoadMusic(void);
void basLoadZipMusic(void);
//_________________________________________________________________________________________________________________________
// Image manipulation
void basHotSpot(void);
void basSetColorKey(void);
void basImageExists(void);
void basImageWidth(void);
void basImageHeight(void);
void basDeleteImage(void);
void basCopyImage(void);
void basSetAlpha(void);
void basZoomImage(void);
void basRotateImage(void);
void basRotozoomImage(void);
void basMirrorImage(void);
//_________________________________________________________________________________________________________________________
// Blitting
void basBlt(void);
void basPasteBob(void);
void basPasteIcon(void);
void basGrab(void);
//_________________________________________________________________________________________________________________________
// Sprite system
void basSpriteClip(void);
void basSprite(void);
void basDeleteSprite(void);
void basXSprite(void);
void basYSprite(void);
void basSpriteWidth(void);
void basSpriteHeight(void);
void basFrSprite(void);
void basLiveSprite(void);
void basSpriteHit(void);
void basSpriteZ(void);
void basLastSprite(void);
void basAutoUpdateSprite(void);
void basUpdateSprite(void);
//_________________________________________________________________________________________________________________________
// Bob system
void basSetBob(void);
void basBob(void);
void basDeleteBob(void);
void basXBob(void);
void basYBob(void);
void basBobWidth(void);
void basBobHeight(void);
void basFrBob(void);
void basLiveBob(void);
void basBobHit(void);
void basBobZ(void);
void basLastBob(void);
void basAutoUpdateBob(void);
void basUpdateBob(void);
//_________________________________________________________________________________________________________________________
//Text draw
void basText(void);
void basSetFont(void);
void basGetFont(void);
void basTextRender(void);
//_________________________________________________________________________________________________________________________
// Print screen
void basPen(void);
void basPaper(void);
void basfPrints(void);
void basPrints(void);
void basLocate(void);
void basAtx(void);
void basAty(void);
void basCursOn(void);
void basCursOff(void);
void basInputs(void);
void basZoneInputs(void);
//_________________________________________________________________________________________________________________________
// Sounds and music

void basIsEnabledSound(void);

void basSoundExists(void);
void basDeleteSound(void);
void basCopySound(void);

void basMusicExists(void);

void basPlaySound(void);
void basPlayFreqSound(void);
void basVolumeSound(void);
void basStopSound(void);
void basPauseSound(void);
void basResumeSound(void);
void basVuMeterSound(void);
void basPositionSound(void);
void basSoundChannels(void);

void basPlayMusic(void);
void basPositionMusic(void);
void basStopMusic(void);
void basPauseMusic(void);
void basResumeMusic(void);
void basRewindMusic(void);
void basFadeMusic(void);
void basVolumeMusic(void);
void basSpeedMusic(void);



//_________________________________________________________________________________________________________________________
// Keyboard
void basKey(void);
void basInkey(void);
void basWaitKey(void);
//_________________________________________________________________________________________________________________________
// Mouse
void basXMouse(void);
void basYMouse(void);
void basXMouseScreen(void);
void basYMouseScreen(void);
void basBMouse(void);
void basChangeMouse(void);
void basLocateMouse(void);
void basMouseShow(void);
void basMouseHide(void);
void basMouseZone(void);
//_________________________________________________________________________________________________________________________
// Joystick
void basNumJoySticks(void);
void basNameJoyStick(void);
void basNumAxesJoyStick(void);
void basNumBallsJoyStick(void);
void basNumHatsJoyStick(void);
void basNumButtonsJoyStick(void);
void basGetAxisJoyStick(void);
void basGetHatJoyStick(void);
void basGetButtonJoyStick(void);
void basXGetBallJoyStick(void);
void basYGetBallJoyStick(void);
void basJoy(void);
void basBJoy(void);
void basWaitBJoy(void);

//_________________________________________________________________________________________________________________________
// SDLtime
void basWait(void);
void basTimer(void);
//-----------------------------------------------------------------------------------------
