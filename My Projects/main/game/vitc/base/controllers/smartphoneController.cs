// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createSmartphoneController(%client, %cid)
{
   %controller = new ScriptObject() {
      class = "SmartphoneController";
      client = %client;
      cid = %cid;
      type = "Smartphone";
      version = 1;
   };
   return %controller;
}

function SmartphoneController::onAdd(%this)
{
   echo("SmartphoneController::onAdd()");
   %this.widgetList = createWidgetList();
   %this.initGrid(2, 8, 12);
   %this.initGrid(1, 8, 12);
   %this.initGrid(0, 8, 12);
   for(%idx = Game.widgets.getCount()-1; %idx >= 0; %idx--)
   {
      %widget = Game.widgets.getObject(%idx);
      %state = "free";
      if(isObject(%widget.controller))
         %state = "taken";
      if(true) // TODO: check controller team id against unit obj team id
         %this.addToWidgetList(%widget, %state);
   }
}

function SmartphoneController::onRemove(%this)
{
   echo("SmartphoneController::onRemove()");
   %this.widgetList.delete();
   for(%grid = 0; %grid < 5; %grid++)
      if(isObject(%this.widgetGrid[%grid]))
         %this.widgetGrid[%grid].delete();
}

function SmartphoneController::processMsg(%this, %msg)
{
   %this.sendMsg("ECHO" SPC %msg);

   %cmd = getWord(%msg, 0);
   if(%cmd $= "REQUEST_WIDGET")
   {
      if(getWordCount(%msg) < 3)
	  {
	       %this.sendMsg("DEBUG REQUEST_WIDGET Malformed request");
		   return;
      }
	
	  %widgetId = getWord(%msg, 1);
	  %gridNo = getWord(%msg, 2);
	
	  %widget = findWidget(%widgetId);
	  if(!isObject(%widget))
	  {
	    %this.sendMsg("DEBUG REQUEST_WIDGET No widget with ID" SPC %widgetId);	
		return;
      }
	
	  %gridSizeN = %widget.getGridSizeN();
	  %gridPos = "";
	  %orientation = "";
	
	  if(getWordCount(%msg) == 6)
	  {
	    %gridPos = getWord(%msg, 3) SPC getWord(%msg, 4);		
	    %orientation = getWord(%msg, 5);		
        if(%orientation $= "E" || %orientation $= "W")
           %gridSize = getWord(%gridSizeN, 1) SPC getWord(%gridSizeN, 0);	
        else
           %gridSize = getWord(%gridSizeN, 0) SPC getWord(%gridSizeN, 1);	
		if(!%this.isFree(%gridNo, %gridPos, %gridSize, %widgetId))
		{
		   %this.sendMsg("DEBUG REQUEST_WIDGET Specified area not free on grid" SPC %gridNo);		
		   return;
		}
	  }
	  else
	  {
		%orientation = "N";		
	    %gridSizeX = getWord(%gridSizeN, 0);
	    %gridSizeY = getWord(%gridSizeN, 1);					
        %gridPos = %this.findFree(%gridNo, %gridSizeX, %gridSizeY);
		if(%gridPos $= "")
		{
		   %orientation = "E";
	       %gridSizeX = getWord(%gridSizeN, 1);
	       %gridSizeY = getWord(%gridSizeN, 0);							
           %gridPos = %this.findFree(%gridNo, %gridSizeX, %gridSizeY);			
		}

		if(%gridPos $= "")
		{
	       %this.sendMsg("DEBUG REQUEST_WIDGET No free space on grid" SPC %gridNo);	
		   return;			
		}
	  }
	
	  if(!%this.addWidget(%widget, %gridNo, %gridPos, %orientation))
	     %this.sendMsg("DEBUG REQUEST_WIDGET Internal server error");		
   }
   else if(%cmd $= "UPDATE_WIDGET")
   {
      if(getWordCount(%msg) < 3)
	  {
	       %this.sendMsg("DEBUG UPDATE_WIDGET Malformed UPDATE_WIDGET request");
		   return;
      }
	
	  %widgetId = getWord(%msg, 1);
	  %widget = findWidget(%widgetId);
	  if(!isObject(%widget))
	  {
	    %this.sendMsg("DEBUG UPDATE_WIDGET No widget with ID" SPC %widgetId);	
		return;
      }	
	  %args = getWords(%msg, 2, -1);
	  %widget.update(%args);
   }
}

function SmartphoneController::dump(%this)
{
   echo(%this.client SPC %this.cid SPC %this.type SPC %this.version @ ":");
   echo("Widget List:");
   %this.widgetList.dump();
   echo("Widget Grids:");
   for(%grid = 0; %grid < 5; %grid++)
   {
      if(isObject(%this.widgetGrid[%grid]))
      {
         echo("Widget Grid #" @ %grid @ ":");
         %this.widgetGrid[%grid].dump();
      }
   }
}

function SmartphoneController::addToWidgetList(%this, %widget, %state)
{
   echo("SmartphoneController::addToWidgetList()" SPC %widget SPC %state);	
   %id = %widget.getId();
   if(%this.widgetList.addWidget(%widget, %state))
      %this.sendMsg("WIDGET_LIST" SPC %this.widgetList.getString(%id));
}

function SmartphoneController::removeFromWidgetList(%this, %widget)
{
   echo("SmartphoneController::removeFromWidgetList()" SPC %widget);	
   %id = %widget.getId();
   if(%this.widgetList.removeWidget(%widget))
      %this.sendMSG("WIDGET_LIST" SPC %id SPC "-1");
}

function SmartphoneController::removeGrid(%this, %gridNo)
{
   echo("SmartphoneController::removeGrid()" SPC %gridNo);
   if(isObject(%this.widgetGrid[%gridNo]))
   {
      %this.widgetGrid[%gridNo].delete();
      %this.widgetGrid[%gridNo] = "";
      %this.sendMsg("WIDGET_GRID remove" SPC %gridNo);
   }
}

function SmartphoneController::initGrid(%this, %gridNo, %sizeX, %sizeY)
{
   echo("SmartphoneController::initGrid()" SPC %gridNo SPC %sizeX SPC %sizeY);
   if(isObject(%this.widgetGrid[%gridNo]))
      %this.widgetGrid[%gridNo].destroy();
   %this.widgetGrid[%gridNo] = createWidgetGrid(%sizeX, %sizeY);
   %this.sendMsg("WIDGET_GRID init" SPC %gridNo SPC %sizeX SPC %sizeY);
}

function SmartphoneController::findFree(%this, %gridNo, %sizeX, %sizeY)
{
   echo("SmartphoneController::findFree()" SPC %gridNo SPC %sizeX SPC %sizeY);
   if(!isObject(%this.widgetGrid[%gridNo]))
      return "";
   return %this.widgetGrid[%gridNo].findFree(%sizeX, %sizeY);	
}

function SmartphoneController::isFree(%this, %gridNo, %gridPos, %gridSize, %ignorePiece)
{
   echo("SmartphoneController::isFree()" SPC %gridNo SPC %gridPos SPC %gridSize SPC %ignorePiece);
   if(!isObject(%this.widgetGrid[%gridNo]))
      return "";
   %posX = getWord(%gridPos, 0);
   %posY = getWord(%gridPos, 1);
   %sizeX = getWord(%gridSize, 0);
   %sizeY = getWord(%gridSize, 1);
   return %this.widgetGrid[%gridNo].isFree(%posX, %posY, %sizeX, %sizeY, %ignorePiece);	
}

function SmartphoneController::addWidget(%this, %widget, %gridNo, %gridPos, %orientation)
{
   echo("SmartphoneController::addWidget()" SPC %widget SPC %gridNo SPC %gridPos SPC %orientation);	
   if(!isObject(%this.widgetGrid[%gridNo]))
      return false;
   %widgetGridPiece = %this.widgetGrid[%gridNo].addPiece(%widget, %gridPos, %orientation);
   if(!isObject(%widgetGridPiece))
      return false;
   %this.sendMsg("WIDGET add" SPC %widget.getId() SPC %widget.getType() SPC
       %widget.getGridSizeN() SPC %gridNo SPC %gridPos SPC %orientation);	
   return true;
}

function SmartphoneController::sendMsg(%this, %msg)
{
   echo("SmartphoneController::sendMsg()" SPC %msg);		
   commandToClient(%this.client, '_VitcMessageToController', %this.cid, %msg);
}

