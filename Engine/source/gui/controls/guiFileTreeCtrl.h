// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_FILETREECTRL_H_
#define _GUI_FILETREECTRL_H_

#include "platform/platform.h"
#include "gui/controls/guiTreeViewCtrl.h"

class GuiFileTreeCtrl : public GuiTreeViewCtrl
{
private:

   // Utility functions
   void recurseInsert( Item* parent, StringTableEntry path );
   void addPathToTree( StringTableEntry path );

protected:
   String               mSelPath;
   String               mFileFilter;
   String               mRootPath;
   Vector< String >     mFilters;

   void _initFilters();
   
   static bool _setFileFilterValue( void *object, const char *index, const char *data );

public:

   typedef GuiTreeViewCtrl Parent;
   
   enum
   {
      Icon_Folder = 1,
      Icon_FolderClosed = 2,
      Icon_Doc = 3
   };
   
   GuiFileTreeCtrl();

   bool onWake();
   bool onVirtualParentExpand(Item *item);
   void onItemSelected( Item *item );
   const String& getSelectedPath() { return mSelPath; }
   bool setSelectedPath( const char* path );
      
   bool matchesFilters(const char* filename);
   void updateTree();

   DECLARE_CONOBJECT( GuiFileTreeCtrl );
   DECLARE_DESCRIPTION( "A control that displays a hierarchical tree view of a path in the game file system.\n"
                        "Note that to enable expanding/collapsing of directories, the control must be\n"
                        "placed inside a GuiScrollCtrl." );

   static void initPersistFields();
};

#endif //_GUI_FILETREECTRL_H_
