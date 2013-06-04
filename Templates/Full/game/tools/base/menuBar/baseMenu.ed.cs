// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// onAdd creates the base menu's and document controller
function BaseEditorCanvas::createMenuBar( %this )
{
   if(isObject(%this.menuBar))
      return;
     
   // Menu bar
   %this.menuBar = new MenuBar()
   {
      dynamicItemInsertPos = 3;
      
      // File Menu
      new PopupMenu()
      {
         superClass = "MenuBuilder"; 
         class = "BaseEditorFileMenu";
         internalName = "FileMenu";      
         
         barTitle = "File";
         
         item[0] = "New..." TAB "Ctrl N" TAB  "[this].onNew();";
         item[1] = "Open..." TAB "Ctrl O" TAB "[this].onOpen();";
         item[2] = "-";
         item[3] = "Save" TAB "Ctrl S" TAB "[this].onSave();";
         item[4] = "Save As" TAB "Ctrl-Alt S" TAB "[this].onSaveAs();";
         item[5] = "Save All" TAB "Ctrl-Shift S" TAB "[this].onSaveAll();";
         item[6] = "-";
         item[7] = "Import..." TAB "Ctrl-Shift I" TAB "[this].onImport();";
         item[8] = "Export..." TAB "Ctrl-Shift E" TAB "[this].onExport();";         
         item[9] = "-";
         item[10] = "Revert" TAB "Ctrl R" TAB "[this].onRevert();";
         item[11] = "-";
         item[12] = "Close" TAB "Ctrl W" TAB "[this].onClose();";
      };      
   };
}

function BaseEditorCanvas::destroyMenuBar( %this )
{
   if( isObject( %this.menuBar ) )
      %this.menuBar.delete();
}

function BaseEditorCanvas::onCreateMenu(%this)
{
   if( !isObject( %this.menuBar ) )
      %this.createMenuBar();
      
   %this.menuBar.attachToCanvas( %this, 0 );
}

function BaseEditorCanvas::onDestroyMenu(%this)
{
   if( isObject( %this.menuBar ) )
   {
      %this.destroyMenuBar();
      %this.menuBar.removeFromCanvas( %this );
   }
}
