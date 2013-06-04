// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton SimGroup( EWorldEditorSelectionFilters );


//---------------------------------------------------------------------------------------------

function ESelectObjectsWindow::toggleVisibility( %this )
{
   if( %this.isVisible() )
      %this.setVisible( false );
   else
      %this.setVisible( true );
}

//---------------------------------------------------------------------------------------------

/// Function called by EObjectSelection::onSelectObjects to determine where
/// to start searching for objects.
function ESelectObjectsWindow::getRootGroup( %this )
{
   return MissionGroup;
}

//---------------------------------------------------------------------------------------------

/// Function called by EObjectSelection::initFilterList to retrieve the set of
/// filter objects.
function ESelectObjectsWindow::getFilterSet( %this )
{
   return EWorldEditorSelectionFilters;
}

//---------------------------------------------------------------------------------------------

/// Method called by EObjectSelection::initClassList to determine if the given
/// class should be included in the class list.
function ESelectObjectsWindow::includeClass( %this, %className )
{
   if(    isMemberOfClass( %className, "SceneObject" )
       || %className $= "SimGroup"
       || %className $= "LevelInfo" ) // Derived directly from NetObject.
      return true;
      
   return false;
}

//---------------------------------------------------------------------------------------------

/// Method called by the EObjectSelection machinery when an object has been
/// matched against the given criteria.
function ESelectObjectsWindow::selectObject( %this, %object, %val )
{
   if( %this.selectionSet )
   {
      if( %val )
         %this.selectionSet.add( %object );
      else
         %this.selectionSet.remove( %object );
   }
   else
   {
      if( %val )
         EWorldEditor.selectObject( %object );
      else
         EWorldEditor.unselectObject( %object );
   }
}

//---------------------------------------------------------------------------------------------

function ESelectObjectsWindow::clearSelection( %this )
{
   if( %this.selectionSet )
      %this.selectionSet.clear();
   else
      EWorldEditor.clearSelection();
}

//=============================================================================================
//    Events.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function ESelectObjectsWindow::onWake( %this )
{
   if( !%this.isInitialized )
   {
      %this.init();
      %this.isInitialized = true;
   }
   
   // Re-initialize the group list on each wake.
   
   %this.initGroupList();
}

//---------------------------------------------------------------------------------------------

function ESelectObjectsWindow::onSelectObjects( %this, %val, %reuseExistingSet )
{
   // See if we should create an independent selection set.
   
   if( %this-->createSelectionSet.isStateOn() )
   {
      %name = %this-->selectionSetName.getText();
      
      // See if we should create or re-use a set.
      
      if( isObject( %name ) )
      {
         if( !%name.isMemberOfClass( "WorldEditorSelection" ) )
         {
            MessageBoxOk( "Error",
               "An object called '" @ %name @ "' already exists and is not a selection." NL
               "" NL
               "Please choose a different name." );
            return;
         }
         else if( !%reuseExistingSet )
         {
            MessageBoxYesNo( "Question",
               "A selection called '" @ %name @ "' already exists. Modify the existing selection?",
               %this @ ".onSelectObjects( " @ %val @ ", true );" );
            return;
         }
         else
            %sel = %name;
      }
      else
      {
         // Make sure the name is valid.
         if( !Editor::validateObjectName( %name, false ) )
            return;

         // Create a new selection set.
         eval( "%sel = new WorldEditorSelection( " @ %name @ " ) { parentGroup = Selections; canSave = true; };" );
         if( !isObject( %sel ) )
         {
            MessageBoxOk( "Error",
               "Could not create the selection set.  Please look at the console.log for details." );
            return;
         }
      }
      
      %this.selectionSet = %sel;
   }
   else
      %this.selectionSet = "";
   
   Parent::onSelectObjects( %this, %val );
   
   // Refresh editor tree just in case.
   
   EditorTree.buildVisibleTree();
}
