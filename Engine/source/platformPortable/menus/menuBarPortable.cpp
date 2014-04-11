// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/menus/menuBar.h"
#include "platform/menus/popupMenu.h"
#include "gui/core/guiCanvas.h"
#include "windowManager/platformWindowMgr.h"
#include "windowManager/platformWindow.h"
#include "core/util/safeDelete.h"

#include "gui/editor/guiMenuBar.h"

#include "platformPortable/menus/PlatformPortablePopupMenuData.h"


//-----------------------------------------------------------------------------
// Platform Data
//-----------------------------------------------------------------------------

// class PlatformMenuBarData
// {
// 
// };

Map<GuiMenuBar::Menu*, PopupMenu*> PlatformPopupMenuData::mMenuMap;

class GuiPlatformGenericMenuBar : public GuiMenuBar
{
   typedef GuiMenuBar Parent;
public:
   DECLARE_CONOBJECT(GuiPlatformGenericMenuBar);

   virtual void menuItemSelected(Menu *menu, MenuItem *item)
   {
      AssertFatal(menu && item, "");

      PopupMenu *popupMenu = PlatformPopupMenuData::mMenuMap[ menu ];
      AssertFatal(popupMenu, "");

      popupMenu->handleSelect( item->id );

      Parent::menuItemSelected(menu, item);
   }

protected:
   /// menu id / item id
   Map<CompoundKey<U32, U32>, String> mCmds;

};

IMPLEMENT_CONOBJECT(GuiPlatformGenericMenuBar);

//-----------------------------------------------------------------------------
// MenuBar Methods
//-----------------------------------------------------------------------------

void MenuBar::createPlatformPopupMenuData()
{
   mData = NULL;
}

void MenuBar::deletePlatformPopupMenuData()
{
//    SAFE_DELETE(mData);
}

//-----------------------------------------------------------------------------

GuiPlatformGenericMenuBar* _FindMenuBarCtrl()
{
   GuiControl* control;
   Sim::findObject("PlatformGenericMenubar", control);
   AssertFatal(control, "");
   if( !control )      
      return NULL;   

   GuiPlatformGenericMenuBar* menuBar;
   menuBar = dynamic_cast<GuiPlatformGenericMenuBar*>( control->findObjectByInternalName(  StringTable->insert("menubar"), true) );
   AssertFatal(menuBar, "");
   return menuBar;
}


void MenuBar::updateMenuBar(PopupMenu *popupMenu /* = NULL */)
{
   //if(! isAttachedToCanvas())
   //   return;   

   GuiPlatformGenericMenuBar* menuBarGui = _FindMenuBarCtrl();
   popupMenu->mData->mMenuBar = this;

   AssertFatal( dStrcmp( popupMenu->mData->mMenuGui->text, popupMenu->getBarTitle() ) == 0, "");
   GuiMenuBar::Menu* menuGui = menuBarGui->findMenu( popupMenu->getBarTitle() );
   if(!menuGui)
   {
      menuBarGui->addMenu( popupMenu->mData->mMenuGui );
      menuGui = menuBarGui->findMenu( popupMenu->getBarTitle() );
   }

   PlatformPopupMenuData::mMenuMap[ menuGui ] = popupMenu;
}

//-----------------------------------------------------------------------------

void MenuBar::attachToCanvas(GuiCanvas *owner, S32 pos)
{
   if(owner == NULL || isAttachedToCanvas())
      return;

   // This is set for popup menus in the onAttachToMenuBar() callback
   mCanvas = owner;

   PlatformWindow* pWindow = owner->getPlatformWindow();
   if(pWindow == NULL) 
      return;

   // Setup the native menu bar
   GuiMenuBar *hWindowMenu = static_cast<GuiMenuBar*>( pWindow->getPortableMenuHandle() );
	if( hWindowMenu == NULL && !Journal::IsPlaying() )
      hWindowMenu = _FindMenuBarCtrl();

   if(hWindowMenu)
   {
      pWindow->setPortableMenuHandle( hWindowMenu );
      GuiControl *base = hWindowMenu->getParent();
         
      while( base->getParent() )
      {
         base = base->getParent();
      }         

      mCanvas->setMenuBar( base );
   }
   
}

void MenuBar::removeFromCanvas()
{
   _FindMenuBarCtrl()->clearMenus();

   mCanvas->setMenuBar(NULL);

   if(mCanvas == NULL || !isAttachedToCanvas())
      return;
}

