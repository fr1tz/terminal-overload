// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdAction(%client, %nr)
{
   echo("serverCmdAction(): client" SPC %client SPC "action" SPC %nr);
   Game.clientAction(%client, %nr);
}

