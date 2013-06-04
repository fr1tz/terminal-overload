// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/editor/inspector/variableInspector.h"
#include "gui/editor/inspector/variableGroup.h"

GuiVariableInspector::GuiVariableInspector()
{
}

GuiVariableInspector::~GuiVariableInspector()
{
}

IMPLEMENT_CONOBJECT(GuiVariableInspector);

ConsoleDocClass( GuiVariableInspector,
   "@brief GUI dedicated to variable viewing/manipulation\n\n"
   "Mostly used in console system, internal use only.\n\n"
   "@internal"
);

void GuiVariableInspector::loadVars( String searchStr )
{     
   clearGroups();

   GuiInspectorVariableGroup *group = new GuiInspectorVariableGroup();

   group->setHeaderHidden( true );
   group->setCanCollapse( false );
   group->mParent = this;
   group->setCaption( "Global Variables" );
   group->mSearchString = searchStr;

   if( group != NULL )
   {
      group->registerObject();
      mGroups.push_back( group );
      addObject( group );
   }   

   //group->inspectGroup();
}

ConsoleMethod( GuiVariableInspector, loadVars, void, 3, 3, "loadVars( searchString )" )
{
   object->loadVars( argv[2] );
}