// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createWidget(%unitObj, %type, %class)
{
   %widget = new ScriptObject() {
      class = %class;
      superClass = "Widget";
      type = %type;
      unitObj = %unitObj;
      controller = "";
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

function Widget::onAdd(%this)
{
   echo("Widget::onAdd()");
}

function Widget::onRemove(%this)
{
   echo("Widget::onRemove()");
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = ControllerGroup.getObject(%idx);
      %controller.removeFromWidgetList(%this);
   }
}

