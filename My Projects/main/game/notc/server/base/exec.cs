// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./bleedfx.cs");
   exec("./commands.cs");
   exec("./deathCamera.cs");
   exec("./game.cs");
   exec("./gameCore.cs");
   exec("./gameCoreBase.cs");
   exec("./inventory.cs");
   exec("./item.cs");
   exec("./misc.cs");
   exec("./observerCamera.cs");
   exec("./pathCamera.cs");
   exec("./packetline.gfx.cs");
   exec("./packetline.cs");
   exec("./player.cs");
   exec("./projectile.cs");
   exec("./radiusDamage.cs");
   exec("./shapeBase.cs");
   exec("./staticShape.cs");
   exec("./teleporter.cs");
   exec("./triggers.cs");
   exec("./turret.cs");
   exec("./vehicle.cs");
   exec("./vehicleWheeled.cs");
   exec("./weapon.sfx.cs");
   exec("./weapon.gfx.cs");
   exec("./weapon.cs");
   
   exec("notc/server/client/misc/Materials/v1/exec.cs");
   exec("notc/server/client/gui/BeepMsgHud/v1/exec.cs");
   exec("notc/server/client/gui/MinimapHud/v1/exec.cs");
   exec("notc/server/client/gui/LoadoutHud/v1/exec.cs");

   exec("notc/server/forms/etherform/exec.cs");
   exec("notc/server/forms/standardcat/exec.cs");
   exec("notc/server/forms/snipercat/exec.cs");

   exec("notc/server/items/damper/exec.cs");
   exec("notc/server/items/vamp/exec.cs");
   exec("notc/server/items/impshield/exec.cs");
   exec("notc/server/items/ballast/exec.cs");
   exec("notc/server/items/stealth/exec.cs");
   exec("notc/server/items/etherboard/exec.cs");
   exec("notc/server/items/launcher/exec.cs");
   exec("notc/server/items/bounce/exec.cs");

   exec("notc/server/items/g1launcher/v1/exec.cs");

   exec("notc/server/weapons/razordisc/v1/exec.cs");
   exec("notc/server/weapons/explosivedisc/v1/exec.cs");
   exec("notc/server/weapons/repeldisc/v1/exec.cs");
   exec("notc/server/weapons/interceptordisc/v1/exec.cs");

   exec("notc/server/weapons/smg1/v1/exec.cs");
   exec("notc/server/weapons/mgl1/v1/exec.cs");
   exec("notc/server/weapons/sg1/v1/exec.cs");
   exec("notc/server/weapons/sg2/v1/exec.cs");
   exec("notc/server/weapons/sr1/v1/exec.cs");
   exec("notc/server/weapons/mg1/v1/exec.cs");
   exec("notc/server/weapons/ml1/v1/exec.cs");
}

executeBaseServerScripts();

