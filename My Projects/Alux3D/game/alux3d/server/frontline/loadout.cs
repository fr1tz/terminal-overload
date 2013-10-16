// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Pieces:
// 0 Infantry
// 1 Air
// 2 Missile
// 3 Box
// 4 Pistol
// 5 Shotgun
// 6 Sniper
// 7 Magnum
// 8 SMG
// 9 Speeder

function sLoadoutcode2Pieces(%code)
{
   %pieces = "";
   %arg1 = getWord(%code, 0);
   if(%arg1 == 4) // Soldier
   {
      %pieces = "0 1";
      %arg2 = getWord(%code, 4);
      if(%arg2 == 1)
         %pieces = %pieces; // TAB "4 1";
      else if(%arg2 == 2)
         %pieces = %pieces TAB "5 1";
      else if(%arg2 == 3)
         %pieces = %pieces TAB "6 1";
      else if(%arg2 == 4)
         %pieces = %pieces TAB "7 1";
      else if(%arg2 == 5)
         %pieces = %pieces TAB "8 1";
      else if(%arg2 == 6)
         %pieces = %pieces TAB "6 1";
   }
   else if(%arg1 == 3)
   {
      %pieces = "3 1"; // Box
   }
   else if(%arg1 == 2)
   {
      %pieces = "2 1"; // Bumblebee
   }
   else if(%arg1 == 1) // Parrot
   {
      %pieces = "1 1";
   }
   else if(%arg1 == 5) // Pillar
   {
      %pieces = "3 2";
   }
   else if(%arg1 == 6) // Hoverpod
   {
      %pieces = "9 1";
   }
   else if(%arg1 == 7) // Hovercycle
   {
      %pieces = "9 1";
   }
   return %pieces;
}

function sPiece2String(%piece)
{
   switch(%piece)
   {
      case 0: %icon = "Infantry";
      case 1: %icon = "Air";
      case 2: %icon = "Missile";
      case 3: %icon = "Box";
      case 4: %icon = "Pistol";
      case 5: %icon = "Shotgun";
      case 6: %icon = "Sniper";
      case 7: %icon = "Magnum";
      case 8: %icon = "SMG";
      case 9: %icon = "Speeder";
   }
}

function GameConnection::loadDefaultLoadout(%this, %no)
{
   switch(%no)
   {
      case 1:
         %this.loadoutName[%no] = "Drone";
         %this.loadoutCode[%no] = "1";
      case 2:
         %this.loadoutName[%no] = "Missile";
         %this.loadoutCode[%no] = "2";
      case 3:
         %this.loadoutName[%no] = "Crate";
         %this.loadoutCode[%no] = "3";
      case 4:
         %this.loadoutName[%no] = "Pillar";
         %this.loadoutCode[%no] = "5";
      case 5:
         %this.loadoutName[%no] = "Hoverpod";
         %this.loadoutCode[%no] = "6";
      case 6:
         %this.loadoutName[%no] = "Hovercycle";
         %this.loadoutCode[%no] = "7";
      case 51:
         %this.loadoutName[%no] = "Pistol Only";
         %this.loadoutCode[%no] = "4 0 0 0 1";
      case 52:
         %this.loadoutName[%no] = "Shotgun";
         %this.loadoutCode[%no] = "4 0 0 1 2";
      case 53:
         %this.loadoutName[%no] = "Heavy Rifle";
         %this.loadoutCode[%no] = "4 0 0 1 3";
      case 54:
         %this.loadoutName[%no] = "Hand Cannon";
         %this.loadoutCode[%no] = "4 0 0 1 4";
      case 55:
         %this.loadoutName[%no] = "Machine Pistol";
         %this.loadoutCode[%no] = "4 0 0 1 5";
      case 56:
         %this.loadoutName[%no] = "Sniper Rifle";
         %this.loadoutCode[%no] = "4 0 0 1 6";
      default:
         %this.loadoutName[%no] = "";
         %this.loadoutCode[%no] = "1";
   }
}

//------------------------------------------------------------------------------

function GameConnection::defaultLoadout(%this)
{
   %this.activeLoadout = %this.loadoutCode[1];

	for(%i = 1; %i <= 9; %i++)
		this.loadout[%i] = "";

	if($Game::GameType == $Game::Ethernet)
	{
		%this.loadout[1] = $CatEquipment::BattleRifle;
		%this.loadout[2] = $CatEquipment::Blaster;
		%this.loadout[3] = $CatEquipment::Etherboard;
		//%this.loadout[4] = $CatEquipment::Damper;
		//%this.loadout[5] = $CatEquipment::VAMP;
		%this.loadout[6] = $CatEquipment::Anchor;
		%this.loadout[7] = $CatEquipment::Grenade;
		%this.loadout[8] = $CatEquipment::Bounce;
		%this.loadout[9] = $CatEquipment::RepelDisc;
		%this.loadout[10] = $CatEquipment::ExplosiveDisc;
	}
	else if($Game::GameType == $Game::Infantry)
	{
		%this.loadout[1] = $CatEquipment::Blaster;
		%this.loadout[2] = $CatEquipment::BattleRifle;
		%this.loadout[3] = $CatEquipment::Etherboard;
	}
	else if($Game::GameType == $Game::TeamJoust)
	{
		%this.loadout[1] = $CatEquipment::Blaster;
		%this.loadout[2] = $CatEquipment::BattleRifle;
		%this.loadout[3] = $CatEquipment::GrenadeLauncher;
		%this.loadout[4] = $CatEquipment::Damper;
		%this.loadout[5] = $CatEquipment::VAMP;
		%this.loadout[6] = $CatEquipment::Stabilizer;
		%this.loadout[7] = $CatEquipment::Grenade;
		%this.loadout[8] = $CatEquipment::Permaboard;
		%this.loadout[9] = $CatEquipment::SlasherDisc;
	}
	else if($Game::GameType == $Game::TeamDragRace)
	{
		%this.loadout[1] = $CatEquipment::Blaster;
		%this.loadout[2] = $CatEquipment::BattleRifle;
		%this.loadout[3] = $CatEquipment::GrenadeLauncher;
		%this.loadout[4] = $CatEquipment::Damper;
		%this.loadout[5] = $CatEquipment::VAMP;
		%this.loadout[6] = $CatEquipment::Stabilizer;
		%this.loadout[7] = $CatEquipment::Grenade;
		%this.loadout[8] = $CatEquipment::SlasherDisc;
	}
	else if($Game::GameType == $Game::GridWars)
	{
		%this.loadout[1] = $CatEquipment::BattleRifle;
		%this.loadout[2] = $CatEquipment::SniperRifle;
		%this.loadout[3] = $CatEquipment::Etherboard;
		%this.loadout[4] = $CatEquipment::Grenade;
		%this.loadout[5] = $CatEquipment::Bounce;
		%this.loadout[6] = $CatEquipment::RepelDisc;
		%this.loadout[7] = $CatEquipment::ExplosiveDisc;
	}
	else
	{
		%this.loadout[1] = $CatEquipment::Blaster;
		%this.loadout[2] = $CatEquipment::BattleRifle;
		%this.loadout[3] = $CatEquipment::Etherboard;
		%this.loadout[4] = $CatEquipment::Damper;
		%this.loadout[5] = $CatEquipment::VAMP;
		%this.loadout[6] = $CatEquipment::Stabilizer;
		%this.loadout[7] = $CatEquipment::Grenade;
		%this.loadout[8] = $CatEquipment::SlasherDisc;
	}
}

function GameConnection::updateLoadout(%this)
{
	%this.numWeapons = 0;
	%this.hasDamper = false;
	%this.hasAnchor = false;
	%this.hasStabilizer = false;
	%this.hasSlasherDisc = false;
	%this.hasRepelDisc = false;
	%this.hasExplosiveDisc = false;
	%this.hasGrenade = false;
	%this.hasBounce = false;
	%this.hasEtherboard = false;
	%this.hasPermaboard = false;
	%this.numVAMPs = 0;
	%this.numRegenerators = 0;

   if(isObject(%this.proxy))
      %this.proxy.delete();
   %this.proxy = new StaticShape() {
	  dataBlock = $Server::Game.form[getWord(%this.activeLoadout, 0)].proxy;
	  client = %this;
     teamId = %this.team.teamId;
   };
   MissionCleanup.add(%this.proxy);
   %this.proxy.setGhostingListMode("GhostOnly");
   %this.proxy.getHudInfo().setActive(false);
   %this.proxy.setCollisionsDisabled(true);

   %this.proxy.startFade(0, 0, true);

   %this.proxy.shapeFxSetTexture(0, 0);
   %this.proxy.shapeFxSetColor(0, 0);
   %this.proxy.shapeFxSetBalloon(0, 1.0, 0.0);
   %this.proxy.shapeFxSetFade(0, 1.0, 0.0);
   %this.proxy.shapeFxSetActive(0, true, true);

   %this.proxy.shapeFxSetTexture(1, 1);
   %this.proxy.shapeFxSetColor(1, 0);
   %this.proxy.shapeFxSetBalloon(1, 1.0, 0.0);
   %this.proxy.shapeFxSetFade(1, 1.0, 0.0);
   %this.proxy.shapeFxSetActive(1, true, true);
}

function GameConnection::displayInventory(%this, %obj)
{
   %this.updateLeftHudMenu();
}

function GameConnection::selectLoadout(%this, %nr)
{
	if(%this.inventoryMode $= "show")
	{
      if(%nr == -17)
      {
			%this.inventoryMode = "select";
			%this.inventoryMode[1] = 1;
      }
		else if(%nr >= 0 && %nr <= 10)
		{
         if(%this.loadoutName[%nr] $= "")
            return;

         %this.activeLoadout = %this.loadoutCode[%nr];

         for(%i = 0; %i < 1; %i++)
         {
            %c = getSubStr(%this.loadoutCode[%nr], %i, 1);
            if(%c < 1 || %c > 7)
            {
               %this.loadout[1] = 0;
              	%this.play2D(BeepMessageSound);
               %this.displayInventory();
               return;
            }
 			   switch(%c)
			   {
				   case 1: %equipment = $CatEquipment::Blaster;
				   case 2: %equipment = $CatEquipment::BattleRifle;
				   case 3: %equipment = $CatEquipment::SniperRifle;
				   case 4: %equipment = $CatEquipment::MiniGun;
				   case 5: %equipment = $CatEquipment::RepelGun;
				   case 6: %equipment = $CatEquipment::Etherboard;
				   case 7: %equipment = $CatEquipment::Regeneration;
			   }
            %this.loadout[%i+1] = %equipment;
         }
			%this.updateLoadout();
		}
		else if(%nr == 7)
		{
			%this.inventoryMode = "fill";
			%this.inventoryMode[1] = 1;
		}
      else
      {
         return;
      }
		%this.displayInventory();
	}
	else if(%this.inventoryMode $= "fill")
	{
		if($Game::GameType == $Game::TeamJoust
		|| $Game::GameType == $Game::TeamDragRace)
		{
			if(%nr < 1 || %nr > 5)
				return;

			switch(%nr)
			{
				case 1: %equipment = $CatEquipment::Blaster;
				case 2: %equipment = $CatEquipment::BattleRifle;
				case 3: %equipment = $CatEquipment::SniperRifle;
				case 4: %equipment = $CatEquipment::MiniGun;
				case 5: %equipment = $CatEquipment::GrenadeLauncher;
			}
		}
		else
		{
			if(%nr < 1 || %nr > 7)
				return;

			switch(%nr)
			{
				case 1: %equipment = $CatEquipment::Blaster;
				case 2: %equipment = $CatEquipment::BattleRifle;
				case 3: %equipment = $CatEquipment::SniperRifle;
				case 4: %equipment = $CatEquipment::MiniGun;
				case 5: %equipment = $CatEquipment::RepelGun;
				case 6: %equipment = $CatEquipment::Etherboard;
				case 7: %equipment = $CatEquipment::Regeneration;
			}
		}

		if(%equipment != $CatEquipment::Regeneration)
		{
			for(%i = 0; %i < %this.inventoryMode[1]; %i++)
			{
				if(%this.loadout[%i] == %equipment)
					return;
			}
		}

		%this.loadout[%this.inventoryMode[1]] = %equipment;

		if(%this.inventoryMode[1] == 3)
		{
			%this.updateLoadout();
			%this.inventoryMode = "show";
		}
		else
		{
			%this.inventoryMode[1]++;
		}
		%this.displayInventory(0);
	}
	else if(%this.inventoryMode $= "select")
	{
		if($Game::GameType == $Game::TeamJoust
		|| $Game::GameType == $Game::TeamDragRace)
		{
			if(%nr < 1 || %nr > 5)
				return;

			switch(%nr)
			{
				case 1: %equipment = $CatEquipment::Blaster;
				case 2: %equipment = $CatEquipment::BattleRifle;
				case 3: %equipment = $CatEquipment::SniperRifle;
				case 4: %equipment = $CatEquipment::MiniGun;
				case 5: %equipment = $CatEquipment::GrenadeLauncher;
			}
		}
		else
		{
			if(%nr < 1 || %nr > 7)
				return;

			switch(%nr)
			{
				case 1: %equipment = $CatEquipment::Blaster;
				case 2: %equipment = $CatEquipment::BattleRifle;
				case 3: %equipment = $CatEquipment::SniperRifle;
				case 4: %equipment = $CatEquipment::MiniGun;
				case 5: %equipment = $CatEquipment::RepelGun;
				case 6: %equipment = $CatEquipment::Etherboard;
				case 7: %equipment = $CatEquipment::Regeneration;
			}
		}

		%this.loadout[%this.inventoryMode[1]] = %equipment;
		%this.updateLoadout();

		%this.inventoryMode = "show";
		%this.displayInventory(0);
	}
  	%this.play2D(BipMessageSound);
}

//------------------------------------------------------------------------------

