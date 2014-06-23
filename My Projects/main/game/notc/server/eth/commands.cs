// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdSelectLoadout(%client, %nr)
{
   %player = %client.player;
   if(%player.getClassName() !$= "Etherform")
      return;
      
   if(%nr < 0 || %nr > 2)
      return;
      
   %client.LoadoutHud_SelectSlot(%nr);
      
   %client.zActiveLoadout = %nr;
}


