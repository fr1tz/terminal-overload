// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLWINDOWTARGET_H_
#define _GFXGLWINDOWTARGET_H_

#include "gfx/gfxTarget.h"

class GFXGLWindowTarget : public GFXWindowTarget
{
public:

   GFXGLWindowTarget(PlatformWindow *win, GFXDevice *d);
   const Point2I getSize() 
   { 
      return mWindow->getClientExtent();
   }
   virtual GFXFormat getFormat()
   {
      // TODO: Fix me!
      return GFXFormatR8G8B8A8;
   }
   void makeActive();
   virtual bool present();
   virtual void resetMode();
   virtual void zombify() { }
   virtual void resurrect() { }
   
   virtual void resolveTo(GFXTextureObject* obj);
   
   void _onAppSignal(WindowId wnd, S32 event);
   
private:
   friend class GFXGLDevice;
   Point2I size;   
   GFXDevice* mDevice;
   void* mContext;
   void* mFullscreenContext;
   void _teardownCurrentMode();
   void _setupNewMode();
};

#endif