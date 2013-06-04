// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simBase.h"
#include "console/simDatablock.h"
#include "gui/editor/guiInspector.h"
#include "gui/editor/inspector/datablockField.h"
#include "gui/editor/inspector/group.h"
#include "gui/buttons/guiIconButtonCtrl.h"
#include "gui/editor/inspector/datablockField.h"
#include "sfx/sfxTypes.h"
#include "sfx/sfxDescription.h"
#include "sfx/sfxEnvironment.h"
#include "sfx/sfxAmbience.h"
#include "sfx/sfxTrack.h"


//-----------------------------------------------------------------------------
// GuiInspectorDatablockField 
// Field construction for datablock types
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorDatablockField);

ConsoleDocClass( GuiInspectorDatablockField,
   "@brief Custom field type for datablock enumeration.\n\n"
   "Editor use only.\n\n"
   "@internal"
);


GuiInspectorDatablockField::GuiInspectorDatablockField( StringTableEntry className )
{
   setClassName( className );
}

void GuiInspectorDatablockField::setClassName( StringTableEntry className )
{
   if( !className || !className[ 0 ] )
      mDesiredClass = NULL;
   else
   {
      mDesiredClass = AbstractClassRep::findClassRep( className );
      if( !mDesiredClass )
         Con::errorf( "GuiInspectorDatablockField::setClassName - no class '%s' found!", className );
   }
}

void GuiInspectorDatablockField::_populateMenu( GuiPopUpMenuCtrl* menu )
{
   menu->addScheme( 1, ColorI( 80, 0, 0, 255 ), ColorI( 80, 0, 0, 255 ), ColorI( 80, 0, 0, 255 ) ); // For client-only coloring.
   menu->addEntry( "", 0 ); // For unsetting.

   SimSet* set = _getDatablockSet();
   U32 id = 1;

   for( SimSet::iterator iter = set->begin(); iter != set->end(); ++ iter )
   {
      SimDataBlock* datablock = dynamic_cast< SimDataBlock* >( *iter );

      // Skip non-datablocks if we somehow encounter them.
      if( !datablock )
         continue;

      // Ok, now we have to figure inheritance info.
      if( datablock && ( !mDesiredClass || datablock->getClassRep()->isClass( mDesiredClass ) ) )
         menu->addEntry( datablock->getName(), id ++, datablock->isClientOnly() ? 1 : 0 );
   }
   
   menu->sort();
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXDescriptionName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXDescriptionName);

ConsoleDocClass( GuiInspectorTypeSFXDescriptionName,
   "@brief Inspector field type for SFXDescriptionName\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXDescriptionName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXDescriptionName )->setInspectorFieldType( "GuiInspectorTypeSFXDescriptionName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXTrackName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXTrackName);

ConsoleDocClass( GuiInspectorTypeSFXTrackName,
   "@brief Inspector field type for SFXTrackName\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXTrackName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXTrackName )->setInspectorFieldType( "GuiInspectorTypeSFXTrackName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXEnvironmentName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXEnvironmentName);

ConsoleDocClass( GuiInspectorTypeSFXEnvironmentName,
   "@brief Inspector field type for SFXEnvironment\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXEnvironmentName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXEnvironmentName )->setInspectorFieldType( "GuiInspectorTypeSFXEnvironmentName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXAmbienceName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXAmbienceName);

ConsoleDocClass( GuiInspectorTypeSFXAmbienceName,
   "@brief Inspector field type for SFXAmbience\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXAmbienceName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXAmbienceName )->setInspectorFieldType( "GuiInspectorTypeSFXAmbienceName" );
}
