// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SCREENSHOTD3D_H_
#define _SCREENSHOTD3D_H_

#include "gfx/screenshot.h"

//**************************************************************************
// D3D implementation of screenshot
//**************************************************************************
class ScreenShotD3D : public ScreenShot
{
protected:

   GBitmap* _captureBackBuffer();

};


#endif  // _SCREENSHOTD3D_H_
