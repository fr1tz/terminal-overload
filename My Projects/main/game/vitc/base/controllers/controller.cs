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
	
   %controller.processMsg(%msg);
	

}

function sendToControllers(%msg)
{
   for(%idx = ControllerGroup.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = ControllerGroup.getObject(%idx);
      %controller.sendMsg(%msg);
  }
}
