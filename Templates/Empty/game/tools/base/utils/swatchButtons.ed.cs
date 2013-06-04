// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Common functionality for GuiSwatchButtonCtrls.
//
// Note that for the mouse-event related functionality, "useMouseEvents" must be set
// to true.


//---------------------------------------------------------------------------------------------

function GuiSwatchButtonCtrl::onMouseDragged( %this )
{
   %payload = new GuiSwatchButtonCtrl();
   %payload.assignFieldsFrom( %this );
   %payload.position = "0 0 ";
   %payload.dragSourceControl = %this;
   
   %xOffset = getWord( %payload.extent, 0 ) / 2;
   %yOffset = getWord( %payload.extent, 1 ) / 2;  
   %cursorpos = Canvas.getCursorPos();
   %xPos = getWord( %cursorpos, 0 ) - %xOffset;
   %yPos = getWord( %cursorpos, 1 ) - %yOffset;

   // Create the drag control.
   
   %ctrl = new GuiDragAndDropControl()
   {
      canSaveDynamicFields    = "0";
      Profile                 = "ToolsGuiSolidDefaultProfile";
      HorizSizing             = "right";
      VertSizing              = "bottom";
      Position                = %xPos SPC %yPos;
      extent                  = %payload.extent;
      MinExtent               = "4 4";
      canSave                 = "1";
      Visible                 = "1";
      hovertime               = "1000";
      deleteOnMouseUp         = true;
      class                   = "GuiDragAndDropControlType_ColorSwatch";
   };
   
   %ctrl.add( %payload );
   
   // Start drag.
   
   Canvas.getContent().add( %ctrl );
   %ctrl.startDragging( %xOffset, %yOffset );
}

//---------------------------------------------------------------------------------------------

function GuiSwatchButtonCtrl::onControlDropped( %this, %payload, %position )
{
   if( !%payload.parentGroup.isInNamespaceHierarchy( "GuiDragAndDropControlType_ColorSwatch" ) )
      return;
      
   // If dropped on same button whence we came from,
   // do nothing.
   
   if( %payload.dragSourceControl == %this )
      return;

   // If a swatch button control is dropped onto this control,
   // copy it's color.
   
   if( %payload.isMemberOfClass( "GuiSwatchButtonCtrl" ) )
   {
      // If the swatch button is part of a color-type inspector field,
      // remember the inspector field so we can later set the color
      // through it.

      if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorI" ) )
         %this.parentGroup.apply( ColorFloatToInt( %payload.color ) );
      else if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorF" ) )
         %this.parentGroup.apply( %payload.color );
      else
         %this.setColor( %payload.color );
   }
}
