// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function serverCmdAction(%client, %nr)
{
   %obj = %client.getControlObject();
   if(%nr == 1)
      %obj.use(WpnBadger);
   else if(%nr == 2)
      %obj.use(WpnRaptor);
   else if(%nr == 20)
      %obj.reloadWeapon();
}

