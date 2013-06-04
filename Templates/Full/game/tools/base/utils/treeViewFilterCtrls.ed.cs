// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Common functions for filter text and clear button controls on tree views.
// The GuiTextEditCtrl having the filter text must have "treeView" dynamic field
// that has the ID of the associated GuiTreeViewCtrl.
// The button ctrl used to clear the text field must have a "textCtrl" dynamic field
// that has the ID of the associated filter GuiTextEditCtrl.


//---------------------------------------------------------------------------------------------

function GuiTreeViewFilterText::onWake( %this )
{
   %filter = %this.treeView.getFilterText();
   if( %filter $= "" )
      %this.setText( "\c2Filter..." );
   else
      %this.setText( %filter );
}

//---------------------------------------------------------------------------------------------

function GuiTreeViewFilterText::onGainFirstResponder( %this )
{
   %this.selectAllText();
}

//---------------------------------------------------------------------------------------------

// When Enter is pressed in the filter text control, pass along the text of the control
// as the treeview's filter.
function GuiTreeViewFilterText::onReturn( %this )
{
   %text = %this.getText();
   if( %text $= "" )
      %this.reset();
   else
      %this.treeView.setFilterText( %text );
}

//---------------------------------------------------------------------------------------------

function GuiTreeViewFilterText::reset( %this )
{
   %this.setText( "\c2Filter..." );
   %this.treeView.clearFilterText();
}

//---------------------------------------------------------------------------------------------

function GuiTreeViewFilterClearButton::onClick( %this )
{
   %this.textCtrl.reset();
}
