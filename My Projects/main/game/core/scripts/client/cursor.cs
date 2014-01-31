// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//---------------------------------------------------------------------------------------------
// Cursor toggle functions.
//---------------------------------------------------------------------------------------------
$cursorControlled = true;
function showCursor()
{
   if ($cursorControlled)
      lockMouse(false);
   Canvas.cursorOn();
}

function hideCursor()
{
   if ($cursorControlled)
      lockMouse(true);
   Canvas.cursorOff();
}

//---------------------------------------------------------------------------------------------
// In the CanvasCursor package we add some additional functionality to the built-in GuiCanvas
// class, of which the global Canvas object is an instance. In this case, the behavior we want
// is for the cursor to automatically display, except when the only guis visible want no
// cursor - usually the in game interface.
//---------------------------------------------------------------------------------------------
package CanvasCursorPackage
{

//---------------------------------------------------------------------------------------------
// checkCursor
// The checkCursor method iterates through all the root controls on the canvas checking each
// ones noCursor property. If the noCursor property exists as anything other than false or an
// empty string on every control, the cursor will be hidden.
//---------------------------------------------------------------------------------------------
function GuiCanvas::checkCursor(%this)
{
   %count = %this.getCount();
   for(%i = 0; %i < %count; %i++)
   {
      %control = %this.getObject(%i);
      if ((%control.noCursor $= "") || !%control.noCursor)
      {
         showCursor();
         return;
      }
   }
   // If we get here, every control requested a hidden cursor, so we oblige.
   hideCursor();
}

//---------------------------------------------------------------------------------------------
// The following functions override the GuiCanvas defaults that involve changing the content
// of the Canvas. Basically, all we are doing is adding a call to checkCursor to each one.
//---------------------------------------------------------------------------------------------
function GuiCanvas::setContent(%this, %ctrl)
{
   Parent::setContent(%this, %ctrl);
   %this.checkCursor();
}

function GuiCanvas::pushDialog(%this, %ctrl, %layer, %center)
{
   Parent::pushDialog(%this, %ctrl, %layer, %center);
   %this.checkCursor();
}

function GuiCanvas::popDialog(%this, %ctrl)
{
   Parent::popDialog(%this, %ctrl);
   %this.checkCursor();
}

function GuiCanvas::popLayer(%this, %layer)
{
   Parent::popLayer(%this, %layer);
   %this.checkCursor();
}

};

activatePackage(CanvasCursorPackage);
