// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createWidget(%moduleObj, %class)
{
   %widget = new ScriptObject() {
      class = %class;
      superClass = "Widget";
      moduleObj = %moduleObj;
      controller = "";
      numPieces = 0;
   };
   Game.widgets.add(%widget);
   
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = ControllerGroup.getObject(%idx);
      if(true) // TODO: check controller team id against unit obj team id
         %controller.addToWidgetList(%widget, "free");
   }

   return %widget;
}

function findWidget(%widgetId)
{
   for(%idx = Game.widgets.getCount()-1; %idx >= 0; %idx--)
   {
      %obj = Game.widgets.getObject(%idx);
	  if(%obj.getId() == %widgetId)
	     return %obj;
   }		
   return "";
}

function Widget::onAdd(%this)
{
   echo("Widget::onAdd()");
}

function Widget::onRemove(%this)
{
   echo("Widget::onRemove()");
   if(isObject(%this.controller))
      %this.controller.removeWidget(%this);
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = ControllerGroup.getObject(%idx);
      %controller.removeFromWidgetList(%this);
   }
}

function Widget::getDescription(%this)
{
   return "";
}