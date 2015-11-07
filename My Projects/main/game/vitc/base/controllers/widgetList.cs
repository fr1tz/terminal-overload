// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createWidgetList()
{
   %widgetList = new ScriptObject() {
      class = "WidgetList";
   };
   return %widgetList;
}

function WidgetList::onAdd(%this)
{
   %this.array = new ArrayObject();
}

function WidgetList::onRemove(%this)
{
   %this.array.delete();
}

function WidgetList::dump(%this)
{
   %this.array.echo();
}

function WidgetList::getString(%this, %id)
{
   %index = %this.array.getIndexFromKey(%id);
   if(%index != -1)
      return %this.array.getValue(%index);
   return "";
}

function WidgetList::addWidget(%this, %id, %type, %state, %unitName)
{
   %dirty = false;
   %index = %this.array.getIndexFromKey(%id);
   %newString = %id SPC %type SPC %state SPC %unitName;
   if(%index == -1)
   {
      %this.array.push_back(%id, %newString);
      %dirty = true;
   }
   else
   {
      %oldString = %this.array.getValue(%index);
      if(%newString !$= %oldString)
      {
         %this.array.setValue(%index, %newString);
         %dirty = true;
      }
   }
   return %dirty;
}

function WidgetList::removeWidget(%this, %id)
{
   %dirty = false;
   %index = %this.array.getIndexFromKey(%id);
   if(%index != -1)
   {
      %this.array.erase(%index);
      %dirty = true;
   }
   return %dirty;
}

function WidgetList::setWidgetState(%this, %id, %state)
{
   %dirty = false;
   %index = %this.array.getIndexFromKey(%id);
   if(%index != -1)
   {
      %oldString = %this.array.getValue(%index);
      %newString = setWord(%oldString, 2, %state);
      if(%newString !$= %oldString)
      {
         %this.array.setValue(%index, %newString);
         %dirty = true;
      }
   }
   return %dirty;
}

