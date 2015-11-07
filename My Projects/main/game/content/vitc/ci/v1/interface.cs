// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function VitcEnableControllerInterface()
{
   VitcDisableControllerInterface();
   %ci = new TcpObject(VitcControllerInterface);
   %ci.controllers = new SimSet();
   %ci.listen(27999);
}

function VitcDisableControllerInterface()
{
   %ci = VitcControllerInterface;
   if(isObject(%ci))
   {
      for(%idx = %ci.controllers.getCount()-1; %idx >= 0; %idx--)
      {
         %connection = %ci.controllers.getObject(%idx);
         %connection.delete();
      }
      %ci.controllers.delete();
      %ci.delete();
   }
}

//------------------------------------------------------------------------------

function VitcControllerInterface::onConnectionRequest(%this, %address, %id)
{
   echo("New controller connection" SPC %id SPC "from" SPC %address);
   %name = VitcControllerConnection @ %id;
   eval("function " @ %name @ "::onDisconnect(%this) { VitcControllerConnection::onDisconnect(%this); }");
   eval("function " @ %name @ "::onLine(%this, %line) { VitcControllerConnection::onLine(%this, %line); }");
   %controller = new TCPObject(%name, %id) {
      address = %address;
   };
   %this.controllers.add(%controller);
   %this.registerController(%controller);
}

function VitcControllerInterface::send(%this, %controller, %msg)
{
   %controller.send(%msg @ "\n");
}

function VitcControllerInterface::registerController(%this, %controller)
{
   commandToServer('RegisterController', %controller.getID());
}

//------------------------------------------------------------------------------

function clientCmd_VitcRegisterControllerReply(%controller)
{
   echo("clientCmd_VitcRegisterControllerReply()" SPC %controller);
   VitcControllerInterface.send(%controller, "REGISTERED");
}

function clientCmd_VitcMessageToController(%cid, %msg)
{
   for(%idx = VitcControllerInterface.controllers.getCount()-1; %idx >= 0; %idx--)
   {
      %controller = VitcControllerInterface.controllers.getObject(%idx);
      if(%controller.getID() == %cid)
      {
         %controller.send(%msg @ "\n");
         return;
      }
  }
}
