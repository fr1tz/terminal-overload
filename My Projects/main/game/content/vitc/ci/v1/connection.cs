// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function VitcControllerConnection::onDisconnect(%this)
{
   echo("CI: Connection" SPC %this.address SPC "disconnect");
   %name = %this.getName();
   eval("function " @ %name @ "::onDisconnect() {}");
   eval("function " @ %name @ "::onLine() {}");
   $VITC::CI::Connections.remove(%this);
   %this.delete();
}

function VitcControllerConnection::onLine(%this, %line)
{
   echo("CI: Connection" SPC %this.address SPC "got:" SPC %line);
   commandToServer('MessageFromController', %this.getId(), %line);
}


