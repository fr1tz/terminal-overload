// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./audioDescriptions.cs");
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
   exec("./territoryZone.cs");
   exec("./triggers.cs");
   exec("./turret.cs");
   exec("./vehicle.cs");
   exec("./vehicleWheeled.cs");
   exec("./weapon.sfx.cs");
   exec("./weapon.gfx.cs");
   exec("./weapon.cs");
   
   exec("notc/client/misc/Materials/v1/exec.cs");
   exec("notc/client/gui/BeepMsgHud/v1/exec.cs");
   exec("notc/client/gui/MinimapHud/v1/exec.cs");
   exec("notc/client/gui/LoadoutHud/v1/exec.cs");
   exec("notc/client/gui/HudIcons/v1/exec.cs");
   exec("notc/client/gui/PlayerList/v1/exec.cs");

   exec("notc/forms/etherform/exec.cs");
   exec("notc/forms/standardcat/exec.cs");
   exec("notc/forms/snipercat/exec.cs");
   exec("notc/forms/tg2dv/exec.cs");

   exec("notc/items/damper/exec.cs");
   exec("notc/items/vamp/exec.cs");
   exec("notc/items/impshield/exec.cs");
   exec("notc/items/ballast/exec.cs");
   exec("notc/items/stealth/exec.cs");
   exec("notc/items/etherboard/exec.cs");
   exec("notc/items/launcher/exec.cs");
   exec("notc/items/bounce/exec.cs");
   exec("notc/items/xjump/exec.cs");

   exec("notc/items/g1launcher/exec.cs");

   exec("notc/weapons/razordisc/exec.cs");
   exec("notc/weapons/explosivedisc/exec.cs");
   exec("notc/weapons/repeldisc/exec.cs");
   exec("notc/weapons/interceptordisc/exec.cs");

   exec("notc/weapons/smg1/exec.cs");
   exec("notc/weapons/smg2/exec.cs");
   exec("notc/weapons/smg3/exec.cs");
   exec("notc/weapons/mgl1/exec.cs");
   exec("notc/weapons/mgl2/exec.cs");
   exec("notc/weapons/sg1/exec.cs");
   exec("notc/weapons/sg2/exec.cs");
   exec("notc/weapons/sg3/exec.cs");
   exec("notc/weapons/sr1/exec.cs");
   exec("notc/weapons/sr2/exec.cs");
   exec("notc/weapons/mg1/exec.cs");
   exec("notc/weapons/mg2/exec.cs");
   exec("notc/weapons/ml1/exec.cs");
   exec("notc/weapons/rfl1/exec.cs");
   
   exec("notc/structures/tg1/exec.cs");
   exec("notc/structures/tg2/exec.cs");
}

executeBaseServerScripts();

