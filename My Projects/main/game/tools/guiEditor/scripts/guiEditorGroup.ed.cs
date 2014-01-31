// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


// GuiEditorGroups are recorded only for undo/redo.  They are ScriptObjects
// containing all the information about a particular GUIControl group.
//
// The properties of GuiEditorGroups are:
//
// int count - Number of controls in group.
// object ctrl[ 0 .. count ] - Controls in group.
// object ctrlParent[ 0 .. count ] - Original parent of each control in group (if missing, controls are moved to parent of group object in ungroup())
// object groupObject - The GuiControl group object.
// object groupParent - The object to which the group should be parented to.


/// Return the combined global bounds of the controls contained in the GuiEditorGroup.
function GuiEditorGroup::getGlobalBounds( %this )
{
   %minX = 2147483647;
   %minY = 2147483647;
   %maxX = -2147483647;
   %maxY = -2147483647;
   
   for( %i = 0; %i < %this.count; %i ++ )
   {
      %ctrl = %this.ctrl[ %i ];
         
      %pos = %ctrl.getGlobalPosition();
      %extent = %ctrl.getExtent();

      // Min.      
      
      %posX = getWord( %pos, 0 );
      %posY = getWord( %pos, 1 );
      
      if( %posX < %minX )
         %minX = %posX;
      if( %posY < %minY )
         %minY = %posY;
      
      // Max.
      
      %posX += getWord( %extent, 0 );
      %posY += getWord( %extent, 1 );
      
      if( %posX > %maxX )
         %maxX = %posX;
      if( %posY > %maxY )
         %maxY = %posY;
   }
   
   return ( %minX SPC %minY SPC ( %maxX - %minX ) SPC ( %maxY - %minY ) );
}

/// Create a new GuiControl and move all the controls contained in the GuiEditorGroup into it.
function GuiEditorGroup::group( %this )
{
   %parent = %this.groupParent;
   
   // Create group.
   
   %group = new GuiControl();
   %parent.addGuiControl( %group );
   %this.groupObject = %group;
   
   // Make group fit around selection.
   
   %bounds = %this.getGlobalBounds();
   %parentGlobalPos = %parent.getGlobalPosition();
   
   %x = getWord( %bounds, 0 ) - getWord( %parentGlobalPos, 0 );
   %y = getWord( %bounds, 1 ) - getWord( %parentGlobalPos, 1 );

   %group.setPosition( %x, %y );
   %group.setExtent( getWord( %bounds, 2 ), getWord( %bounds, 3 ) );
   
   // Reparent all objects to group.
   
   for( %i = 0; %i < %this.count; %i ++ )
   {
      %ctrl = %this.ctrl[ %i ];
      
      // Save parent for undo.
      
      %this.ctrlParent[ %i ] = %ctrl.parentGroup;
      
      // Reparent.
      
      %group.addGuiControl( %ctrl );
      
      // Move into place in new parent.
      
      %pos = %ctrl.getPosition();
      %ctrl.setPosition( getWord( %pos, 0 ) - %x, getWord( %pos, 1 ) - %y );
   }
}

/// Move all controls out of group to either former parent or group parent.
function GuiEditorGroup::ungroup( %this )
{
   %defaultParent = %this.groupParent;
   %groupPos = %this.groupObject.getPosition();
   
   %x = getWord( %groupPos, 0 );
   %y = getWord( %groupPos, 1 );
   
   // Move each control to its former parent (or default parent when
   // there is no former parent).
   
   for( %i = 0; %i < %this.count; %i ++ )
   {
      %ctrl = %this.ctrl[ %i ];
      
      %parent = %defaultParent;
      if( isObject( %this.ctrlParent[ %i ] ) )
         %parent = %this.ctrlParent[ %i ];
                           
      %parent.addGuiControl( %ctrl );
         
      // Move into place in new parent.
      
      %ctrlPos = %ctrl.getPosition();
      %ctrl.setPosition( getWord( %ctrlPos, 0 ) + %x, getWord( %ctrlPos, 1 ) + %y );
   }
   
   // Delete old group object.

   %this.groupObject.delete();
}
