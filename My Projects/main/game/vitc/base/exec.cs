// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./controllers/exec.cs");
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
   exec("./widget.cs"); 
   
   exec("vitc/client/misc/Materials/v1/exec.cs");
   exec("vitc/client/gui/BeepMsgHud/v1/exec.cs");
   exec("vitc/client/gui/MinimapHud/v1/exec.cs");
   exec("vitc/client/gui/LoadoutHud/v1/exec.cs");
   exec("vitc/client/gui/HudIcons/v1/exec.cs");
   exec("vitc/client/gui/PlayerList/v1/exec.cs");

   exec("vitc/forms/etherform/exec.cs");
   exec("vitc/forms/standardcat/exec.cs");
   exec("vitc/forms/snipercat/exec.cs");
   exec("vitc/forms/tg2dv/exec.cs");

   //exec("vitc/items/damper/exec.cs");
   //exec("vitc/items/vamp/exec.cs");
   //exec("vitc/items/impshield/exec.cs");
   //exec("vitc/items/ballast/exec.cs");
   //exec("vitc/items/stealth/exec.cs");
   //exec("vitc/items/etherboard/exec.cs");
   //exec("vitc/items/launcher/exec.cs");
   //exec("vitc/items/bounce/exec.cs");
   //exec("vitc/items/xjump/exec.cs");

   //exec("vitc/items/g1launcher/exec.cs");

   //exec("vitc/weapons/razordisc/exec.cs");
   //exec("vitc/weapons/explosivedisc/exec.cs");
   //exec("vitc/weapons/repeldisc/exec.cs");
   //exec("vitc/weapons/interceptordisc/exec.cs");

   //exec("vitc/weapons/smg1/exec.cs");
   //exec("vitc/weapons/smg2/exec.cs");
   //exec("vitc/weapons/smg3/exec.cs");
   //exec("vitc/weapons/smg4/exec.cs");
   //exec("vitc/weapons/mgl1/exec.cs");
   //exec("vitc/weapons/mgl2/exec.cs");
   //exec("vitc/weapons/sg1/exec.cs");
   //exec("vitc/weapons/sg2/exec.cs");
   //exec("vitc/weapons/sg3/exec.cs");
   //exec("vitc/weapons/sr1/exec.cs");
   //exec("vitc/weapons/sr2/exec.cs");
   //exec("vitc/weapons/mg1/exec.cs");
   //exec("vitc/weapons/mg2/exec.cs");
   //exec("vitc/weapons/ml1/exec.cs");
   //exec("vitc/weapons/rfl1/exec.cs");
   
   //exec("vitc/structures/tg1/exec.cs");
   //exec("vitc/structures/tg2/exec.cs");
   
   exec("vitc/modules/exec.cs");
   exec("vitc/units/exec.cs");
}

executeBaseServerScripts();

