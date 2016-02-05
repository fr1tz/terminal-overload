// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./audioDescriptions.cs");
   exec("./bleedfx.cs");
   exec("./commands.cs");
   exec("./controllerWidgets.cs");
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
   exec("./reso.cs");
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
   
   exec("notc/client/misc/Materials/v1/exec.cs");
   exec("notc/client/gui/BeepMsgHud/v1/exec.cs");
   exec("notc/client/gui/MinimapHud/v1/exec.cs");
   exec("notc/client/gui/LoadoutHud/v1/exec.cs");
   exec("notc/client/gui/HudIcons/v1/exec.cs");
   exec("notc/client/gui/PlayerList/v1/exec.cs");   
   
   exec("reso/forms/satellite/exec.cs");
   exec("reso/forms/alphadisc/exec.cs");
}

executeBaseServerScripts();

