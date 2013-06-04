// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifdef TORQUE_DEDICATED

#ifndef _DEDICATED_WINDOW_STUB_H_
#define _DEDICATED_WINDOW_STUB_H_

#include "windowManager/platformWindowMgr.h"

/// The DedicatedWindowMgr is for Dedicated servers, which may not
/// even have graphics hardware.  However, the WindowManager is referenced
/// (indirectly) by scripts, and therefore must exist.
class DedicatedWindowMgr : public PlatformWindowManager
{
public:

   DedicatedWindowMgr() {};

   virtual ~DedicatedWindowMgr()
   {
   }

   static void processCmdLineArgs(const S32 argc, const char **argv) {}

   /// Return the extents in window coordinates of the primary desktop
   /// area. On dedicated systems, this returns a token value of 0.
   virtual RectI getPrimaryDesktopArea() { return RectI(0, 0, 0, 0); }

   /// Retrieve the currently set desktop bit depth.
   /// @return -1 since there is no desktop
   virtual S32 getDesktopBitDepth() { return -1; }

   /// Retrieve the currently set desktop resolution
   /// @return Point2I(-1,-1) since there is no desktop
   virtual Point2I getDesktopResolution() { return Point2I(-1, -1); }

   /// Populate a vector with the token primary desktop area value
   virtual void getMonitorRegions(Vector<RectI> &regions) { regions.push_back(getPrimaryDesktopArea()); }

   /// Create a new window, appropriate for the specified device and mode.
   ///
   /// @return NULL - there is no graphics hardware available in dedicated mode
   virtual PlatformWindow *createWindow(GFXDevice *device, const GFXVideoMode &mode) { return NULL; }

   /// Produces an empty list since there are no windows in dedicated mode
   virtual void getWindows(VectorPtr<PlatformWindow*> &windows) { windows.clear(); }

   /// Get the window that currently has the input focus or NULL.
   virtual PlatformWindow* getFocusedWindow() { return NULL; }

   /// Get a window from a device ID.
   ///
   /// @return NULL.
   virtual PlatformWindow *getWindowById(WindowId id) { return NULL; }

   /// Get the first window in the window list
   ///
   /// @return The first window in the list, or NULL if no windows found
   virtual PlatformWindow *getFirstWindow() { return NULL; }


   /// Set the parent window
   ///
   /// This does nothing in dedicated builds
   virtual void setParentWindow(void* newParent) {}

   /// Get the parent window - returns NULL for dedicated servers
   virtual void* getParentWindow() { return NULL; }


   /// This method cues the appearance of that window ("lowering the curtain").
   virtual void lowerCurtain() {}

   /// @see lowerCurtain
   ///
   /// This method removes the curtain window.
   virtual void raiseCurtain() {}

private:
   /// Process command line arguments from StandardMainLoop. This is done to
   /// allow web plugin functionality, where we are passed platform-specific
   /// information allowing us to set ourselves up in the web browser,
   /// to occur in a platform-neutral way.
   virtual void _processCmdLineArgs(const S32 argc, const char **argv) {}
};

#endif // _DEDICATED_WINDOW_STUB_H_

#endif // TORQUE_DEDICATED
