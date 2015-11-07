// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createWidgetGrid(%sizeX, %sizeY)
{
   %widgetGrid = new ScriptObject() {
      class = "WidgetGrid";
      sizeX = %sizeX;
      sizeY = %sizeY;
      cells = "";
   };
   return %widgetGrid;
}

function WidgetGrid::onAdd(%this)
{
   %n = %this.sizeX * %this.sizeY;
   while(%n-- >= 0)
      %this.cells = %this.cells @ "0 ";
}

function WidgetGrid::onRemove(%this)
{

}

function WidgetGrid::dump(%this)
{
   for(%row = 0; %row < %this.sizeY; %row++)
   {
      %start = %row * %this.sizeX;
      %end = %start + %this.sizeX - 1;
      echo(getWords(%this.cells, %start, %end));
   }
}

function WidgetGrid::getCell(%this, %x, %y)
{
   if(%x < 0 || %x >= %this.sizeX || %y < 0 || %y >= %this.sizeY)
      return "-1";
   return getWord(%this.cells, %y*%this.sizeX + %x);
}

function WidgetGrid::setCell(%this, %x, %y, %piece)
{
   if(%x < 0 || %x >= %this.sizeX || %y < 0 || %y >= %this.sizeY)
      return false;
   %this.cells = setWord(%this.cells, %y*%this.sizeX + %x, %piece);
   return true;
}


function WidgetGrid::isFree(%this, %posX, %posY, %sizeX, %sizeY, %ignorePiece)
{
   for(%x = %posX; %x < %posX+%sizeX; %x++)
   {
      for(%y = %posY; %y < %posY+%sizeY; %y++)
      {
         %piece = %this.getCell(%x, %y);
         if(%piece == -1)
            return false;
         else if(%piece != 0 && %piece != %ignorePiece)
            return false;
      }
   }
   return true;
}

function WidgetGrid::findFree(%this, %sizeX, %sizeY)
{
   for(%x = 0; %x < %this.sizeX; %x++)
   {
      for(%y = 0; %y < %this.sizeY; %y++)
      {
         if(%this.isFree(%x, %y, %sizeX, %sizeY))
            return %x SPC %y;
      }
   }
   return "";
}

