// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef PLATFORM_PORTABLE_POPUPMENU_DATA_H
#define PLATFORM_PORTABLE_POPUPMENU_DATA_H

#include "core/util/tDictionary.h"

class GuiMenuBar;
struct EventDescriptor;
class PopupMenu;
class MenuBar;

struct PlatformPopupMenuData
{
   MenuBar *mMenuBar;
   GuiMenuBar::Menu *mMenuGui;

   static const U8 mCheckedBitmapIdx = 0;
   static Map<GuiMenuBar::Menu*, PopupMenu*> mMenuMap;

   PlatformPopupMenuData()
   {
      mMenuBar = NULL;
      mMenuGui = NULL;
   }

   ~PlatformPopupMenuData()
   {
      
   }

   void insertAccelerator(EventDescriptor &desc, U32 id);
   void removeAccelerator(U32 id);
   void setAccelleratorEnabled(U32 id, bool enabled);
};

#endif //PLATFORM_PORTABLE_POPUPMENU_DATA_H
