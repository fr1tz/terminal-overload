// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//------------------------------------------------------------------------------
// Hard coded images referenced from C++ code
//------------------------------------------------------------------------------

//   editor/SelectHandle.png
//   editor/DefaultHandle.png
//   editor/LockedHandle.png


//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Mission Editor 
//------------------------------------------------------------------------------

function Editor::create()
{
   // Not much to do here, build it and they will come...
   // Only one thing... the editor is a gui control which
   // expect the Canvas to exist, so it must be constructed
   // before the editor.
   new EditManager(Editor)
   {
      profile = "GuiContentProfile";
      horizSizing = "right";
      vertSizing = "top";
      position = "0 0";
      extent = "640 480";
      minExtent = "8 8";
      visible = "1";
      setFirstResponder = "0";
      modal = "1";
      helpTag = "0";
      open = false;
   };
}

function Editor::getUndoManager(%this)
{
   if ( !isObject( %this.undoManager ) )
   {
      /// This is the global undo manager used by all
      /// of the mission editor sub-editors.
      %this.undoManager = new UndoManager( EUndoManager )
      {
         numLevels = 200;
      };
   }
   return %this.undoManager;
}

function Editor::setUndoManager(%this, %undoMgr)
{
   %this.undoManager = %undoMgr;
}

function Editor::onAdd(%this)
{
   // Ignore Replicated fxStatic Instances.
   EWorldEditor.ignoreObjClass("fxShapeReplicatedStatic");
}

function Editor::checkActiveLoadDone()
{
   if(isObject(EditorGui) && EditorGui.loadingMission)
   {
      Canvas.setContent(EditorGui);
      EditorGui.loadingMission = false;
      return true;
   }
   return false;
}

//------------------------------------------------------------------------------
function toggleEditor(%make)
{
   if (Canvas.isFullscreen())
   {
      MessageBoxOK("Windowed Mode Required", "Please switch to windowed mode to access the Mission Editor.");
      return;
   }
   
   if (%make)
   {      
      %timerId = startPrecisionTimer();
      
      if( $InGuiEditor )
         GuiEdit();
         
      if( !$missionRunning )
      {
         // Flag saying, when level is chosen, launch it with the editor open.
         ChooseLevelDlg.launchInEditor = true;
         Canvas.pushDialog( ChooseLevelDlg );         
      }
      else
      {
         pushInstantGroup();
         
         if ( !isObject( Editor ) )
         {
            Editor::create();
            MissionCleanup.add( Editor );
            MissionCleanup.add( Editor.getUndoManager() );
         }
         
         if( EditorIsActive() )
         {
            if (theLevelInfo.type $= "DemoScene") 
            {
               commandToServer('dropPlayerAtCamera');
               Editor.close("SceneGui");   
            } 
            else 
            {
               Editor.close("PlayGui");
            }
         }
         else 
         {
            if ( !$GuiEditorBtnPressed )
            {
               canvas.pushDialog( EditorLoadingGui );
               canvas.repaint();
            }
            else
            {
               $GuiEditorBtnPressed = false;
            }
            
            Editor.open();
			
			// Cancel the scheduled event to prevent
			// the level from cycling after it's duration
			// has elapsed.
            cancel($Game::Schedule);
            
            if (theLevelInfo.type $= "DemoScene")
               commandToServer('dropCameraAtPlayer', true);
               
            
            canvas.popDialog(EditorLoadingGui);
         }
         
         popInstantGroup();
      }
      
      %elapsed = stopPrecisionTimer( %timerId );
      warn( "Time spent in toggleEditor() : " @ %elapsed / 1000.0 @ " s" );
   }
}

//------------------------------------------------------------------------------
//  The editor action maps are defined in editor.bind.cs
GlobalActionMap.bind(keyboard, "f11", toggleEditor);


// The scenario:
// The editor is open and the user closes the level by any way other than
// the file menu ( exit level ), eg. typing disconnect() in the console.
//
// The problem:
// Editor::close() is not called in this scenario which means onEditorDisable
// is not called on objects which hook into it and also gEditingMission will no
// longer be valid.
//
// The solution:
// Override the stock disconnect() function which is in game scripts from here
// in tools so we avoid putting our code in there.
//
// Disclaimer:
// If you think of a better way to do this feel free. The thing which could
// be dangerous about this is that no one will ever realize this code overriding
// a fairly standard and core game script from a somewhat random location.
// If it 'did' have unforscene sideeffects who would ever find it?

package EditorDisconnectOverride
{
   function disconnect()
   {
      if ( isObject( Editor ) && Editor.isEditorEnabled() )
      {
         if (isObject( MainMenuGui ))
            Editor.close("MainMenuGui");
      }
      
      Parent::disconnect();  
   }
};
activatePackage( EditorDisconnectOverride );
