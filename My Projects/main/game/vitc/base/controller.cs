// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdRegisterController(%client, %cid)
{
   echo("serverCmdRegisterController()" SPC %client SPC %cid);
   %controller = createSmartphoneController(%client, %cid);
   ControllerGroup.add(%controller);
   commandToClient(%client, '_VitcRegisterControllerReply', %controller.cid);
}

function serverCmdMessageFromController(%client, %cid, %msg)
{
   echo("serverCmdMessageFromController()" SPC %client SPC %cid SPC %msg);

   %controller = "";
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %obj = ControllerGroup.getObject(%idx);
	  if(%obj.cid == %cid)
	  {
	     %controller = %obj;
		 break;
      }
   }

   if(!isObject(%controller))
      return;
	
   %controller.sendMsg("ECHO" SPC %msg);

   %cmd = getWord(%msg, 0);
   if(%cmd $= "REQUEST_WIDGET")
   {
      if(getWordCount(%msg) < 3)
	  {
	       %controller.sendMsg("DEBUG Malformed REQUEST_WIDGET request");
		   return;
      }
	
	  %widgetId = getWord(%msg, 1);
	  %gridNo = getWord(%msg, 2);
	
	  echo(%widgetId SPC %gridNo);
	
	  %widget = "";
	  for(%idx = Game.widgets.getCount()-1; %idx >= 0; %idx--)
      {
         %obj = Game.widgets.getObject(%idx);
		 if(%obj.getId() == %widgetId)
		 {
		    %widget = %obj;
			break;
		 }
      }	
	
	  if(!isObject(%widget))
	  {
	    %controller.sendMsg("DEBUG No widget with ID" SPC %widgetId);	
		return;
      }
	
	  %gridSize = %widget.getGridSize();
	  %gridSizeX = getWord(%gridSize, 0);
	  %gridSizeY = getWord(%gridSize, 0);			
	
	  %gridPosX = "";
	  %gridPosY = "";
	  %orientation = "";
	  if(getWordCount(%msg) == 6)
	  {
	    %gridPosX = getWord(%msg, 3);	
	    %gridPosY = getWord(%msg, 4);		
	    %orientation = getWord(%msg, 5);		
		return;
	  }
	  else
	  {
        %gridPos = %controller.findFree(%gridNo, %sizeX, %sizeY);
		if(%gridPos $= "")
		{
	       %controller.sendMsg("DEBUG No free space on grid" SPC %gridNo);	
		   return;			
		}
		else
		{
	      %gridPosX = getWord(%gridPos, 0);	
	      %gridPosY = getWord(%gridPos, 1);		
	      %orientation = 0;
		}
	  }
	
	  %controller.addWidget(%widget, %gridNo, %gridPosX, %gridPosY, %orientation);
	  %controller.sendMsg("WIDGET add" SPC %widget.getId() SPC %widget.type SPC
	    %gridNo SPC %gridPosX SPC %gridPosY SPC %orientation);
   }
   else if(%cmd $= "UPDATE_WIDGET")
   {
      if(getWordCount(%msg) < 3)
	  {
	       %controller.sendMsg("DEBUG Malformed UPDATE_WIDGET request");
		   return;
      }
	
	  %widgetId = getWord(%msg, 1);
	  %args = getWords(%msg, 2, -1);
	  %widgetId.update(%args);
   }
}

function sendToControllers(%msg)
{
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = ControllerGroup.getObject(%idx);
      %controller.sendMsg(%msg);
  }
}


