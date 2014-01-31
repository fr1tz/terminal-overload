// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.



//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::toggleVisibility( %this )
{
   if( %this.isVisible() )
      %this.setVisible( false );
   else
      %this.setVisible( true );
}

//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::getRootGroup( %this )
{
   return GuiEditor.getContentControl();
}

//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::includeClass( %this, %className )
{
   return (    isMemberOfClass( %className, "GuiControl" )
            && !GuiEditor.isFilteredClass( %className ) );
}

//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::selectObject( %this, %object, %val )
{
   if( %val )
      GuiEditor.addSelection( %object );
   else
      GuiEditor.removeSelection( %object );
}

//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::clearSelection( %this )
{
   GuiEditor.clearSelection();
}

//=============================================================================================
//    Events.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEditorSelectDlg::onVisible( %this, %visible )
{
   if( !%visible )
      return;
      
   if( !%this.isInitialized )
   {
      %this.init();
      %this.isInitialized = true;
   }
   
   // Re-initialize the group list on each wake.
   
   %this.initGroupList();
}
