// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simBase.h"

#ifndef _MENUBAR_H_
#define _MENUBAR_H_

// Forward Refs
class PlatformMenuBarData;
class PopupMenu;
class GuiCanvas;

class MenuBar : public SimSet
{
   typedef SimSet Parent;

protected:
   PlatformMenuBarData *mData;
   GuiCanvas *mCanvas;

   /// Update the native menu bar to ensure consistency with the set
   void updateMenuBar(PopupMenu *menu = NULL);
   
   void createPlatformPopupMenuData();
   void deletePlatformPopupMenuData();
   
public:
   MenuBar();
   virtual ~MenuBar();
   DECLARE_CONOBJECT(MenuBar);

   /// Attach this menu bar to the native menu bar
   void attachToCanvas(GuiCanvas *owner, S32 pos);
   /// Remove this menu bar from the native menu bar
   void removeFromCanvas();

   /// Returns true if this menu is attached to the menu bar
   bool isAttachedToCanvas()                      { return mCanvas != NULL; }

   virtual void insertObject(SimObject *obj, S32 pos);

   // Overridden SimSet methods to ensure menu bar consistency when attached
   virtual void addObject(SimObject *obj);
   virtual void removeObject(SimObject *obj);
   virtual void pushObject(SimObject *obj);
   virtual void popObject();

   virtual bool reOrder(SimObject *obj, SimObject *target = 0);
};

#endif // _MENUBAR_H_
