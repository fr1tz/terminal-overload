// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMCURSORCONTROLLER_H_
#define _PLATFORMCURSORCONTROLLER_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class PlatformWindow;

class PlatformCursorController
{
protected:

   struct Cursor_Shape
   {
      enum Type
      {
         TYPE_RESOURCE,
         TYPE_FILE,
      };

      Type   mCursorType;
      S32    mCursorID;   // Points to a platform specific cursor ID
      String mCursorFile; // Points to a custom cursor file
   };

   Vector<Cursor_Shape> mCursors;

   /// The PlatformWindow that owns this Cursor Controller
   PlatformWindow *mOwner;

public:

   PlatformCursorController( PlatformWindow *owner ) :
      mOwner( owner )
   {
      VECTOR_SET_ASSOCIATION( mCursors );
   };

   virtual ~PlatformCursorController()
   {
      mOwner = NULL;
   };

   enum 
   {
      curArrow = 0,
      curWait,
      curPlus,
      curResizeVert,
      curResizeHorz,
      curResizeAll,
      curIBeam,
      curResizeNESW,
      curResizeNWSE,
      curHand,
   };

public:

   virtual void setCursorPosition(S32 x, S32 y) = 0;
   virtual void getCursorPosition( Point2I &point ) = 0;
   virtual void setCursorVisible( bool visible ) = 0;
   virtual bool isCursorVisible() = 0;

   virtual void setCursorShape( const Cursor_Shape &shape, bool reload );
   virtual void setCursorShape( U32 cursorID ) = 0;
   virtual void setCursorShape( const UTF8 *filename, bool reload ) = 0;

   virtual void pushCursor( S32 cursorID );
   virtual void pushCursor( const UTF8 *fileName );
   virtual void popCursor();
   virtual void refreshCursor();

   virtual U32 getDoubleClickTime() = 0;
   virtual S32 getDoubleClickWidth() = 0;
   virtual S32 getDoubleClickHeight() = 0;
};

#endif
