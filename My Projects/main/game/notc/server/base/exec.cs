// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./aiPlayer.cs");
   exec("./bleedfx.cs");
   exec("./commands.cs");
   exec("./game.cs");
   exec("./gameCore.cs");
   exec("./inventory.cs");
   exec("./item.cs");
   exec("./misc.cs");
   exec("./observerCamera.cs");
   exec("./player.cs");
   exec("./projectile.cs");
   exec("./radiusDamage.cs");
   exec("./shapeBase.cs");
   exec("./teleporter.cs");
   exec("./triggers.cs");
   exec("./turret.cs");
   exec("./vehicle.cs");
   exec("./vehicleWheeled.cs");
   exec("./weapon.cs");
}

executeBaseServerScripts();

