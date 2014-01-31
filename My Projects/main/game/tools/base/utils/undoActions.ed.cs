// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Undo actions that are useful in multiple editors.


//=============================================================================================
//    Undo reparenting.
//=============================================================================================

//---------------------------------------------------------------------------------------------

function UndoActionReparentObjects::create( %treeView )
{
   pushInstantGroup();
   %action = new UndoScriptAction()
   {
      class = "UndoActionReparentObjects";
      numObjects = 0;
      treeView = %treeView;
   };
   popInstantGroup();
   
   return %action;
}

//---------------------------------------------------------------------------------------------

function UndoActionReparentObjects::add( %this, %object, %oldParent, %newParent )
{
   %index = %this.numObjects;
   
   %this.objects[ %index ] = %object;
   %this.oldParents[ %index ] = %oldParent;
   %this.newParents[ %index ] = %newParent;
   
   %this.numObjects = %this.numObjects + 1;
}

//---------------------------------------------------------------------------------------------

function UndoActionReparentObjects::undo( %this )
{
   %numObjects = %this.numObjects;
   for( %i = 0; %i < %numObjects; %i ++ )
   {
      %obj = %this.objects[ %i ];
      %group = %this.oldParents[ %i ];
      
      if( isObject( %obj ) && isObject( %group ) )
         %obj.parentGroup = %group;
   }
   
   if( isObject( %this.treeView ) )
      %this.treeView.update();
}

//---------------------------------------------------------------------------------------------

function UndoActionReparentObjects::redo( %this )
{
   %numObjects = %this.numObjects;
   for( %i = 0; %i < %numObjects; %i ++ )
   {
      %obj = %this.objects[ %i ];
      %group = %this.newParents[ %i ];
      
      if( isObject( %obj ) && isObject( %group ) )
         %obj.parentGroup = %group;
   }

   if( isObject( %this.treeView ) )
      %this.treeView.update();
}
