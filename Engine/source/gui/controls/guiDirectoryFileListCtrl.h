// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_DIRECTORYFILELISTCTRL_H_
#define _GUI_DIRECTORYFILELISTCTRL_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

#ifndef _GUI_LISTBOXCTRL_H_
#include "gui/controls/guiListBoxCtrl.h"
#endif

class GuiDirectoryFileListCtrl : public GuiListBoxCtrl
{
private:
   typedef GuiListBoxCtrl Parent;
protected:
   StringTableEntry mFilePath;
   StringTableEntry mFilter;

   void openDirectory();
   
   static bool _setFilePath( void *object, const char *index, const char *data )
   {
      GuiDirectoryFileListCtrl* ctrl = ( GuiDirectoryFileListCtrl* ) object;
      ctrl->setCurrentPath( data, ctrl->mFilter );
      return false;
   }
   static bool _setFilter( void *object, const char *index, const char *data )
   {
      GuiDirectoryFileListCtrl* ctrl = ( GuiDirectoryFileListCtrl* ) object;
      ctrl->setCurrentFilter( data );
      return false;
   }
   
public:
   GuiDirectoryFileListCtrl();
   
   DECLARE_CONOBJECT(GuiDirectoryFileListCtrl);
   DECLARE_DESCRIPTION( "A control that displays a list of files from within a single\n"
                        "directory in the game file system." );
   
   static void initPersistFields();
   
   void update() { openDirectory(); }

   /// Set the current path to grab files from
   bool setCurrentPath( const char* path, const char* filter );
   void setCurrentFilter( const char* filter );

   /// Get the currently selected file's name
   StringTableEntry getSelectedFileName();

   virtual void onMouseDown(const GuiEvent &event);
   virtual bool onWake();
};

#endif
