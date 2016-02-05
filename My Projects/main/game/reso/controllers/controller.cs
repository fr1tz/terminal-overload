// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdMessageFromController(%client, %cid, %msg)
{
   echo("serverCmdMessageFromController()" SPC %client SPC %cid SPC %msg);
   
   %msgType = getWord(%msg, 0);
   
   if(%msgType $= "GAME_INFO_REQUEST")
   {
   	  %msg = "GAME_INFO" SPC 
              $Pref::Server::Name NL
   	          $Server::GameType NL
   	          $Server::MissionType NL
   	          $Server::MissionName;
      commandToClient(%client, '_ResoMessageToController', %cid, %msg);
   }   
   else if(%msgType $= "SESSION" && getWord(%msg, 1) $= "init")
   {
      %sessionId = getWord(%msg, 2);
   	  echo(" Got session init request for session" SPC %sessionId);      

      // See if the message can be ignored.
      for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
      {
         %controller = ControllerGroup.getObject(%idx);
         if(%controller.client == %client
         && %controller.cid $= %cid
         && %controller.sessionId == %sessionId)
         {
            echo(" Ignoring duplicate request");
            return;
         }
      }

      // Delete existing controllers from the same client with the same CID.
      for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
      {
         %controller = ControllerGroup.getObject(%idx);
         if(%controller.client == %client && %controller.cid $= %cid)
            %controller.delete();
      }      
      
      // Create new controller object.
      %controller = createSmartphoneController(%client, %cid, %sessionId);
      ControllerGroup.add(%controller);      
      commandToClient(%client, '_ResoMessageToController', %cid, %msg);
   } 
   else
   {
      for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
      {
         %controller = ControllerGroup.getObject(%idx);
	     if(%controller.client == %client && %controller.cid $= %cid)
	     {
	        %controller.processMsg(%msg);
		    break;
         }
      }
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

