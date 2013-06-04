// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
   
function ConvexEditorGui::onWake( %this )
{   
}

function ConvexEditorGui::onSleep( %this )
{
}

function ConvexEditorGui::createConvexBox( %this )
{
   %obj = genericCreateObject( "ConvexShape" );
   %this.handleDeselect();
   %this.selectConvex( %obj );
   %this.dropSelectionAtScreenCenter();
}

function ConvexEditorGui::onSelectionChanged( %this, %shape, %face )
{
   //echo( "onSelectionChanged: " @ %shape SPC %face );
   
   ConvexEditorSplitFaceBtn.setActive( false );
   ConvexEditorSplitFaceBtn.ToolTip = "Split selected face [Disabled]" NL "Use Ctrl + Rotate instead for more control";
   ConvexEditorDeleteFaceBtn.setActive( false );
   ConvexEditorDeleteFaceBtn.ToolTip = "Delete selection [Disabled] (Delete)"; 
   
   if ( !isObject( %shape ) )      
      return;   
      
   ConvexEditorDeleteFaceBtn.setActive( true );
      
   if ( %face == -1 )     
      ConvexEditorDeleteFaceBtn.ToolTip = "Delete selected ConvexShape (Delete)";
   else
   {
      ConvexEditorDeleteFaceBtn.ToolTip = "Delete selected Face (Delete)";
      
      ConvexEditorSplitFaceBtn.ToolTip = "Split selected face" NL "Use Ctrl + Rotate instead for more control";
      ConvexEditorSplitFaceBtn.setActive( true );
   }
}