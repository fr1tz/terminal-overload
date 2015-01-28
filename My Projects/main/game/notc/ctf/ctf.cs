// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function CTF::restartGame()
{
   Game.roundRestarting = true;
   
   // Update team colors here so mappers don't have to restart the
   // server when experimenting with team colors.
   Game.team0.color = theLevelInfo.teamColors0;
   Game.team1.color = theLevelInfo.teamColors1;
   Game.team2.color = theLevelInfo.teamColors2;

   Game.team1.numPlayersOnRoundStart = 0;
   Game.team2.numPlayersOnRoundStart = 0;
   
   Game.team1.score = 0;
   Game.team2.score = 0;

   TerritoryZones_repairTick();
   
   CTF::applyTeamColors(MissionGroup);
   
   for( %clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++ )
   {
      %client = ClientGroup.getObject(%clientIndex);

      CTF::resetLoadout(%client);

      // Do not respawn observers.
      if(%client.team == Game.team1 || %client.team == Game.team2 )
         Game.preparePlayer(%client);
   }

   //serverUpdateMusic();
   //serverUpdateGameStatus();

   Game.roundRestarting = false;
}

function CTF::applyTeamColors(%group)
{
   %count = %group.getCount();
   if(%count != 0)
   {
      for (%i = 0; %i < %count; %i++)
      {
         %obj = %group.getObject(%i);
         if(%obj.getClassName $= "SimGroup")
            CTF::applyTeamColors(%obj);
         else if(%obj.isMethod("getTeamId"))
            changePalette(%obj, 0, ETH::getTeamColorI(%obj.getTeamId()));
      }
   }
}

function CTF::setupHud(%client)
{
   // LoadoutHud
   %active[0] = true;
   %active[1] = true;
   %active[2] = true;
   %active[3] = true;
   %active[4] = true;
   %active[5] = false;
   %icon[0] = "content/xa/notc/core/icons/p1/smg1.32x32.png";
   %icon[1] = "content/xa/notc/core/icons/p1/mgl1.32x32.png";
   %icon[2] = "content/xa/notc/core/icons/p1/sr1.32x32.png";
   %icon[3] = "content/xa/notc/core/icons/p1/mg1.32x32.png";
   %icon[4] = "content/xa/notc/core/icons/p1/tg2dv.32x32.png";
   for(%i = 0; %i < 6; %i++)
      %client.LoadoutHud_UpdateSlot(%i, %active[%i], %icon[%i], %client.zLoadoutProgress[%i]);
   %client.LoadoutHud_SelectSlot(%client.zActiveLoadout);
      
   // MinimapHUD
   %client.MinimapHud_SetHudInfoDatasetType_Color(2);
   %client.MinimapHud_SetHudInfoDatasetType_Icon(3);
   %client.MinimapHud_ClearColors();
   %client.MinimapHud_AddColor(1, Game.team1.color);
   %client.MinimapHud_AddColor(2, Game.team2.color);
   %client.MinimapHud_ClearIcons();
   %client.MinimapHud_AddIcon(1, "content/xa/notc/core/icons/p1/class0.8x8.png", 8);
   %client.MinimapHud_AddIcon(2, "content/xa/notc/core/icons/p1/class1.8x8.png", 8);
   %client.MinimapHud_AddIcon(3, "content/xa/notc/core/icons/p1/class2.8x8.png", 8);
   %client.MinimapHud_AddIcon(4, "content/xa/notc/core/icons/p1/class3.8x8.png", 8);
   %client.MinimapHud_AddIcon(128, "content/xa/notc/core/icons/p1/etherform.8x8.png", 8);
   %client.MinimapHud_AddIcon(129, "content/xa/notc/core/icons/p1/flagstand.14x14.png", 14);
   %client.MinimapHud_AddIcon(130, "content/xa/notc/core/icons/p1/flag.8x8.png", 8);
   
   // HudIcons
   %client.HudIcons_SetHudInfoDatasetType_Color(2);
   %client.HudIcons_SetHudInfoDatasetType_Icon(3);
   %client.HudIcons_ClearColors();
   //%client.HudIcons_AddColor(1, Game.team1.color);
   //%client.HudIcons_AddColor(2, Game.team2.color);
   %client.HudIcons_ClearIcons();
   //%client.MinimapHud_AddIcon(1, "content/xa/notc/core/icons/p1/class0.8x8.png", 8);
   //%client.MinimapHud_AddIcon(2, "content/xa/notc/core/icons/p1/class1.8x8.png", 8);
   //%client.MinimapHud_AddIcon(3, "content/xa/notc/core/icons/p1/class2.8x8.png", 8);
   //%client.MinimapHud_AddIcon(4, "content/xa/notc/core/icons/p1/class3.8x8.png", 8);
   %client.HudIcons_AddIcon(128, "content/xa/notc/core/icons/p1/etherform.256x256.png", 0);
   %client.HudIcons_AddIcon(130, "content/xa/notc/core/icons/p1/flag.8x8.png", 8);
}

function CTF::resetLoadout(%client)
{
   for(%i = 0; %i < 6; %i++)
   {
      %client.zLoadoutProgress[%i] = 1.0;
      %client.zLoadoutProgressDt[%i] = 0.0;
   }
}

function CTF::loadoutEtherform(%player)
{
   // Setup ShapeBase HudInfo object icon
   %player.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %player.zShapeBaseHudInfo.setDatasetIntField(2, 128);
   
   copyPalette(%player, %player.zBallastShape1);
   copyPalette(%player, %player.zBallastShape2);
}

function CTF::loadoutPlayer(%player)
{
   //echo("CTF::loadoutPlayer()");

   %client = %player.client;
   if(!isObject(%client))
      return;

   // Setup ShapeBase HudInfo object icon
   %player.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %player.zShapeBaseHudInfo.setDatasetIntField(2, %client.zActiveLoadout+1);

   %player.setInventory(ItemDamper, 1);
   %player.setInventory(ItemVAMP, 1);
   %player.setInventory(ItemImpShield, 1);
   %player.setInventory(ItemLauncher, 1);
   %player.setInventory(ItemBounce, 1);
   %player.setInventory(ItemXJump, 1);

   %player.setInventory(ItemG1Launcher, 1);
   
   %player.clearWeaponCycle();
   switch(%client.zActiveLoadout)
   {
      case 0:
         %player.setInventory(ItemEtherboard, 1);
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnRazorDiscAmmo, 9999);
         %player.setInventory(WpnSMG2, 1);
         %player.setInventory(WpnSG3, 1);
         %player.addToWeaponCycle(WpnSMG2);
         %player.addToWeaponCycle(WpnSG3);
         %player.mountImage(WpnSMG2Image, 0);
      case 1:
         %player.setInventory(ItemEtherboard, 1);
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnRepelDiscAmmo, 9999);
         %player.setInventory(WpnMGL2, 1);
         %player.addToWeaponCycle(WpnMGL2);
         %player.mountImage(WpnMGL2Image, 0);
      case 2:
         %player.setInventory(ItemEtherboard, 1);
         %player.setInventory(ItemStealth, 1);
         %player.setInventory(WpnExplosiveDiscAmmo, 9999);
         %player.setInventory(WpnSR2, 1);
         %player.addToWeaponCycle(WpnSR2);
         %player.mountImage(WpnSR2Image, 0);
      case 3:
         %player.setInventory(WpnRepelDiscAmmo, 9999);
         %player.setInventory(WpnMG2, 1);
         %player.addToWeaponCycle(WpnMG2);
         %player.mountImage(WpnMG2Image, 0);
   }
}

function CTF::switchToEtherform(%client)
{
   %player = %client.player;
   if(!isObject(%player))
      return;
      
   if(%player.getClassName() $= "Etherform")
      return;
      
   // Update loadout
   %damage = %player.getDamageLevel();
   %maxDamage = %player.getDataBlock().maxDamage;
   %percent = 1 - %damage/%maxDamage;
   %slot = %client.zActiveLoadout;
   %client.zLoadoutProgress[%slot] = %percent;
   %client.LoadoutHud_UpdateSlot(%slot, "", "", %percent);
   error(%percent);

   %tagged = %player.isTagged();
   %pos = %player.getWorldBoxCenter();

   %etherform = new Etherform() {
      dataBlock = FrmEtherform;
      client = %client;
      teamId = %client.team.teamId;
   };
	MissionCleanup.add(%etherform);
   Game.loadout(%etherform);

   %mat = %player.getTransform();
   %dmg = %player.getDamageLevel();
   %nrg = %player.getEnergyLevel();
   %buf = %player.getDamageBufferLevel();
   %vel = %player.getVelocity();

   %etherform.setTransform(%mat);
   %etherform.setTransform(%pos);
   %etherform.setDamageLevel(%dmg);
   %etherform.setShieldLevel(%buf);

//   if(%tagged || $Server::Game.tagMode == $Server::Game.alwaystag)
//      %etherform.setTagged();

   %client.control(%etherform);
   
   if(%player.getDamageState() $= "Enabled")
      %player.schedule(0, "delete");

   %etherform.setEnergyLevel(%nrg - 50);
   %etherform.applyImpulse(%pos, VectorScale(%vel,100));
   %etherform.playAudio(0, EtherformSpawnSound);

	%client.player = %etherform;
 
   // Demanifest effect
   if(%player.getDamageState() $= "Enabled")
   {
      %shape = new StaticShape() {
         dataBlock = FrmStandardcatDemanifestShape;
      };
      MissionCleanup.add(%shape);
      copyPalette(%etherform, %shape);
      %shape.playThread(0, "ambient");
      %shape.setThreadTimeScale(0, 3);
      %shape.setThreadDir(0, true);
      %shape.startFade(200, 50, true);
      %shape.schedule(500, "delete");
      
      %etherform.mountObject(%shape, 8);
   }
}

function CTF::onFlagReturned(%teamId)
{
   //echo("CTF::onFlagReturned()");
   serverPlay2D(ctfFlagReturnedSound);
   messageAll('MsgFlagReturned', '\c2Team %1 flag has been returned!', %teamId);
}

function CTF::onFlagCaptured(%teamId)
{
   //echo("CTF::onFlagCaptured()");
   Game.team[%teamId].score++;
   serverPlay2D(ctfFlagCapturedSound);
   messageAll('MsgFlagCaptured', '\c2Team %1 has scored!', %teamId);
}

function CTF::onFlagTaken(%teamId)
{
   //echo("CTF::onFlagTaken()");
   serverPlay2D(ctfFlagTakenSound);
   messageAll('MsgFlagTaken', '\c2Team %1 flag has been taken!', %teamId);
}

function CTF::onFlagDropped(%teamId)
{
   //echo("CTF::onFlagDropped()");
   serverPlay2D(ctfFlagDroppedSound);
   messageAll('MsgFlagDropped', '\c2Team %1 flag has been dropped!', %teamId);
}

