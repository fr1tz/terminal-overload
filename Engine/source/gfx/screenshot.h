// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SCREENSHOT_H_
#define _SCREENSHOT_H_

#include "gfx/gfxDevice.h"

class GuiCanvas;
class Point2I;
class Frustum;

//**************************************************************************
/*!
   This class will eventually support various capabilities such as panoramics,
   high rez captures, and cubemap captures.
   
   Right now it just captures standard screenshots, but it does support
   captures from multisample back buffers, so antialiased captures will work.
*/
//**************************************************************************

class ScreenShot
{
   /// This is overloaded to copy the current GFX 
   /// backbuffer to a new bitmap.
	virtual GBitmap* _captureBackBuffer() { return NULL; }

   /// This is set to toggle the capture.
   bool mPending;

   /// If true write the file as a JPG else its a PNG.
   bool mWriteJPG;

   /// The full path to the screenshot file to write.
   char mFilename[256];

   /// The number of times to tile the backbuffer to 
   /// generate screenshots larger than normally possible.
   U32 mTiles;

   /// How much pixel percentage overlap between tiles
   Point2F mPixelOverlap;

   /// How much the frustum must be adjusted for overlap
   Point2F mFrustumOverlap;

   /// The current tile we're rendering.
   Point2I mCurrTile;

   /// Helper for taking simple single tile screenshots and
   /// outputing it as a single file to disk.
   void _singleCapture( GuiCanvas *canvas );
   
public:
  
   /// Constructor.
   ScreenShot();
   virtual ~ScreenShot() { }

   /// Used to start the screenshot capture.
   void setPending( const char *filename, bool writeJPG, S32 tiles, F32 overlap );

   /// Returns true if we're in the middle of screenshot capture.
   bool isPending() const { return mPending; }

   /// Prepares the view frustum for tiled screenshot rendering.
   /// @see GuiTSCtrl::setupFrustum
   void tileFrustum( Frustum& frustum );

   ///
   void tileGui( const Point2I &screenSize );

   /// Called from the canvas to capture a pending screenshot.
   /// @see GuiCanvas::onRenderEvent
   void capture( GuiCanvas *canvas );

};

extern ScreenShot *gScreenShot;

#endif  // _SCREENSHOT_H_
