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
   %id = %widget.getId();
   %type = %widget.type;
   %unitName = "NAME_TODO";
   if(%this.widgetList.addWidget(%id, %type, %state, %unitName))
      %this.sendMsg("WIDGET_LIST" SPC %this.widgetList.getString(%id));
}

function SmartphoneController::removeFromWidgetList(%this, %widget)
{
   %id = %widget.getId();
   if(%this.widgetList.removeWidget(%id))
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
   echo("SmartphoneController::initGrid()");
   if(isObject(%this.widgetGrid[%gridNo]))
      %this.widgetGrid[%gridNo].destroy();
   %this.widgetGrid[%gridNo] = createWidgetGrid(%sizeX, %sizeY);
   %this.sendMsg("WIDGET_GRID init" SPC %gridNo SPC %sizeX SPC %sizeY);
}

function SmartphoneController::findFree(%this, %gridNo, %sizeX, %sizeY)
{
   echo("SmartphoneController::findFree()");
   if(!isObject(%this.widgetGrid[%gridNo]))
      return "";
   return %this.widgetGrid[%gridNo].findFree(%sizeX, %sizeY);	
}


function SmartphoneController::sendMsg(%this, %msg)
{
   commandToClient(%this.client, '_VitcMessageToController', %this.cid, %msg);
}

