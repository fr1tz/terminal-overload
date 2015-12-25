// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createWidgetGridPiece(%widget)
{
   %widgetGridPiece = new ScriptObject() {
      class = "WidgetGridPiece";
      widget = %widget;
   };
   return %widgetGridPiece;	
}

function WidgetGridPiece::onAdd(%this)
{
   //%gridSize = %this.widget.getGridSizeN();
   //%this.gridSizeX = getWord(%gridSize, 0);
   //%this.gridSizeX = getWord(%gridSize, 0);
}

function WidgetGridPiece::onRemove(%this)
{
	
}

function createWidgetGrid(%sizeX, %sizeY)
{
   %pieces = new SimGroup();
   %widgetGrid = new ScriptObject() {
      class = "WidgetGrid";
      sizeX = %sizeX;
      sizeY = %sizeY;
	  pieces = %pieces;
      cells = "";
   };
   return %widgetGrid;
}

function WidgetGrid::onAdd(%this)
{
   %this.rebuildCells();
}

function WidgetGrid::onRemove(%this)
{
   %this.pieces.delete();
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

function WidgetGrid::rebuildCells(%this)
{
   %n = %this.sizeX * %this.sizeY;
   %this.cells = "";
   while(%n-- >= 0)
      %this.cells = %this.cells @ "0 ";	
   for(%idx = %this.pieces.getCount()-1; %idx >= 0; %idx--)
   {
      %gridPiece = %this.pieces.getObject(%idx);
	  %orientation = %gridPiece.orientation;
	  %posX = %gridPiece.gridPosX;
	  %posY = %gridPiece.gridPosY;
      %widget = %gridPiece.widget;	
      %gridSizeN = %widget.getGridSizeN();	
      if(%orientation $= "E" || %orientation $= "W")	
	  {
	     %sizeX = getWord(%gridSizeN, 1);
	     %sizeY = getWord(%gridSizeN, 0);	
      }
	  else
	  {
	     %sizeX = getWord(%gridSizeN, 0);
	     %sizeY = getWord(%gridSizeN, 1);	
      }	
      for(%x = %posX; %x < %posX+%sizeX; %x++)
      {
         for(%y = %posY; %y < %posY+%sizeY; %y++)
         {
            %this.setCell(%x, %y, %widget.getId());   
         }
      }	  
   }	
}

function WidgetGrid::addPiece(%this, %widget, %gridPos, %orientation)
{
   echo("WidgetGrid::addWidget()" SPC %widget SPC %gridPos SPC %orientation);
   %gridSizeN = %widget.getGridSizeN();
   if(%gridSizeN $= "")
      return "";
	
   if(%orientation $= "E" || %orientation $= "W")
   {
      %gridSizeX = getWord(%gridSizeN, 1);
      %gridSizeY = getWord(%gridSizeN, 0);	
   }
   else
   {
      %gridSizeX = getWord(%gridSizeN, 0);
      %gridSizeY = getWord(%gridSizeN, 1);	
   }

   %gridPosX = getWord(%gridPos, 0);
   %gridPosY = getWord(%gridPos, 1);

   if(!%this.isFree(%gridPosX, %gridPosY, %gridSizeX, %gridSizeY, %widget.getId()))
      return "";

   // See if there's already a piece for that widget on the grid.
   %gridPiece = "";
   for(%idx = %this.pieces.getCount()-1; %idx >= 0; %idx--)
   {
      %gp = %this.pieces.getObject(%idx);
	  if(%gp.widget == %widget)
	  {
         %gridPiece = %gp;
		 break;
	  }
   }	

   if(%gridPiece $= "")
   {
      %gridPiece = createWidgetGridPiece(%widget);
      %this.pieces.add(%gridPiece);
      %widget.numPieces++;
   }

   %gridPiece.gridPosX = %gridPosX;
   %gridPiece.gridPosY = %gridPosY; 
   %gridPiece.orientation = %orientation;
   
   %this.rebuildCells();
   return %gridPiece;
}

function WidgetGrid::removePiece(%this, %widget)
{
   echo("WidgetGrid::removePiece()" SPC %widget);
   for(%idx = %this.pieces.getCount()-1; %idx >= 0; %idx--)
   {
      %gp = %this.pieces.getObject(%idx);
	  if(%gp.widget == %widget)
	  {
         %gp.delete();
         %widget.numPieces--;
	  }
   }   
   %this.rebuildCells();   
}

