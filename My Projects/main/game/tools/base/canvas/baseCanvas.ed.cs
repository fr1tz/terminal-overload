// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
function BaseEditorCanvas::onAdd( %this )
{
   %this.createMenuBar();
   
   %panel = new GuiPanel() { internalName = "DocumentContainer"; };
   %this.setContent( %panel );
   
   %xOffset = 20;
   %yOffset = 20;
   
   for( %i =0; %i<10; %i++ )
   {
      %window = new GuiWindowCtrl() 
      { 
         extent = "200 100"; 
         position = %xOffset SPC %yOffset;
      };
      %panel.add( %window );
      
      %xOffset += 30;
      %yOffset += 30;

   }
}

function BaseEditorCanvas::onRemove( %this )
{
   %this.destroyMenuBar();
}

function testBaseEditor()
{
   %baseEd = new GuiCanvas() { class="BaseEditorCanvas"; };
}