// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/worldEditor/guiMissionAreaEditor.h"
#include "gui/core/guiCanvas.h"

IMPLEMENT_CONOBJECT(GuiMissionAreaEditorCtrl);

ConsoleDocClass( GuiMissionAreaEditorCtrl,
   "@brief Specialized GUI used for editing the MissionArea in a level\n\n"
   "Editor use only.\n\n"
   "@internal"
);

GuiMissionAreaEditorCtrl::GuiMissionAreaEditorCtrl()
{
}

GuiMissionAreaEditorCtrl::~GuiMissionAreaEditorCtrl()
{
}

bool GuiMissionAreaEditorCtrl::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   return true;
}

void GuiMissionAreaEditorCtrl::initPersistFields()
{
   Parent::initPersistFields();
}

void GuiMissionAreaEditorCtrl::get3DCursor( GuiCursor *&cursor, 
                                       bool &visible, 
                                       const Gui3DMouseEvent &event_ )
{
   //cursor = mAddNodeCursor;
   //visible = false;
   
   cursor = NULL;
   visible = false;

   GuiCanvas *root = getRoot();
   if ( !root )
      return;

   S32 currCursor = PlatformCursorController::curArrow;

   if ( root->mCursorChanged == currCursor )
      return;

   PlatformWindow *window = root->getPlatformWindow();
   PlatformCursorController *controller = window->getCursorController();
   
   // We've already changed the cursor, 
   // so set it back before we change it again.
   if( root->mCursorChanged != -1)
      controller->popCursor();

   // Now change the cursor shape
   controller->pushCursor(currCursor);
   root->mCursorChanged = currCursor;   
}

void GuiMissionAreaEditorCtrl::setSelectedMissionArea( MissionArea *missionArea )
{
   mSelMissionArea = missionArea;

   if ( mSelMissionArea != NULL )
      Con::executef( this, "onMissionAreaSelected", missionArea->getIdString() );
   else
      Con::executef( this, "onMissionAreaSelected" );
}

ConsoleMethod( GuiMissionAreaEditorCtrl, setSelectedMissionArea, void, 2, 3, "" )
{
   if ( argc == 2 )
      object->setSelectedMissionArea(NULL);
   else
   {
      MissionArea *missionArea = NULL;
      if ( Sim::findObject( argv[2], missionArea ) )
         object->setSelectedMissionArea(missionArea);
   }
}

ConsoleMethod( GuiMissionAreaEditorCtrl, getSelectedMissionArea, const char*, 2, 2, "" )
{
   MissionArea *missionArea = object->getSelectedMissionArea();
   if ( !missionArea )
      return NULL;

   return missionArea->getIdString();
}
