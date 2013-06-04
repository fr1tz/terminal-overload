// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "forest/editor/forestTool.h"
#include "forest/editor/forestEditorCtrl.h"

#include "forest/forestDataFile.h"
#include "forest/forestCell.h"

#include "util/undo.h"
#include "math/mMath.h"
#include "math/mathUtils.h"


IMPLEMENT_CONOBJECT( ForestTool );

ConsoleDocClass( ForestTool,
   "@brief Base class for Forest Editor specific tools\n\n"
   "Editor use only.\n\n"
   "@internal"
);

ForestTool::ForestTool()
   : mForest( NULL ),
     mEditor( NULL )
{   
}

ForestTool::~ForestTool()
{
}

void ForestTool::_submitUndo( UndoAction *action )
{
   AssertFatal( action, "ForestTool::_submitUndo() - No undo action!" );

   // Grab the mission editor undo manager.
   UndoManager *undoMan = NULL;
   if ( !Sim::findObject( "EUndoManager", undoMan ) )
   {
      Con::errorf( "ForestTool::_submitUndo() - EUndoManager not found!" );
      return;     
   }

   undoMan->addAction( action );

   mEditor->updateCollision();
}
