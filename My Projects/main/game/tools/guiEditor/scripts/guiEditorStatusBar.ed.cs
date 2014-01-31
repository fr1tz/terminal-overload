// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Code for the status bar in the Gui Editor.


//---------------------------------------------------------------------------------------------

function GuiEditorStatusBar::getMouseModeHelp( %this )
{
   %isMac = ( $platform $= "macos" );
   if( %isMac )
      %cmdCtrl = "CMD";
   else
      %cmdCtrl = "CTRL";
   
   %mouseMode = GuiEditor.getMouseMode();
   switch$( %mouseMode )
   {
      case "Selecting":
         return "";
      
      case "DragSelecting":
         return %cmdCtrl @ " to add to selection; ALT to exclude parents; CTRL+ALT to exclude children";
      
      case "MovingSelection":
         return "";
      
      case "SizingSelection":
         return "CTRL to activate snapping; ALT to move instead of resize";
      
      case "DragGuide":
         return "Drag into ruler to delete; drop to place";
   }
   
   return "";
}

//---------------------------------------------------------------------------------------------

function GuiEditorStatusBar::print( %this, %message )
{
   %this.setText( %message );
   
   %sequenceNum = %this.sequenceNum + 1;
   %this.sequenceNum = %sequenceNum;
   
   %this.schedule( 4 * 1000, "clearMessage", %sequenceNum );
}

//---------------------------------------------------------------------------------------------

function GuiEditorStatusBar::clearMessage( %this, %sequenceNum )
{
   // If we had no newer message in the meantime, clear
   // out the current text.
   
   if( %this.sequenceNum == %sequenceNum )
      %this.setText( %this.getMouseModeHelp() );
}

//=============================================================================================
//    Event Handlers.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEditorStatusBar::onWake( %this )
{
   %this.setText( %this.getMouseModeHelp() );
}
