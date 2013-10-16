// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::clientAction(%game, %client, %nr)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::clientAction");
   
   %obj = %client.getControlObject();
   if(!isObject(%obj))
      return;
      
   %obj.getDataBlock().clientAction(%obj, %nr);
}

function FrontlineGame::clientLeaveForm(%game, %client, %obj, %dematerialize)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::clientLeaveForm");
   
   if(%obj.getClassName() $= "Etherform")
      return;

   // Can't leave a form we're not actually controlling
   %form = %client.player;
	if(isObject(%form) && %obj != %form)
		return;

	//%tagged = %form.isTagged();
	%pos = %form.getWorldBoxCenter();

	if($Server::NewbieHelp)
	{
		%client.newbieHelpData_NeedsRepair =
			(%client.player.getDamageLevel() > %client.player.getDataBlock().maxDamage*0.75);
		%client.newbieHelpData_LowEnergy =
			(%client.player.getEnergyLevel() < 50);
	}

	%data = %game.getEtherformDataBlock();
	%obj = new Etherform() {
		dataBlock = %data;
		client = %client;
		teamId = %client.team.teamId;
	};
   MissionCleanup.add(%obj);

	//%obj.setTransform(%form.getTransform());
	//%obj.setTransform(%form.getWorldBoxCenter());
   %obj.setTransform(%form.getEyeTransform());

	%nrg = %form.getEnergyLevel();
   %maxdmg = %form.getDataBlock().maxDamage;
   %prevhealth = (%maxdmg - %dmg)/%maxdmg;
   %newenergy = (%data.maxEnergy*%prevhealth)/2;
   %obj.setEnergyLevel(%newenergy);
	%obj.applyImpulse(%pos, VectorScale(%form.getVelocity(),100));
	%obj.playAudio(0, EtherformSpawnSound);

	%client.control(%obj);
	%client.player = %obj;

   if(%form.getDataBlock().isMethod("onLightLeft"))
      %form.getDataBlock().onLightLeft(%form);

//	if(%tagged)
//		%obj.setTagged();

   if(%dematerialize)
   {
      if(%form.getDataBlock().isMethod("dematerialize"))
         %form.getDataBlock().dematerialize(%form);
   }
   else
   {
		%form.setShapeName("");
		//%client.player.getHudInfo().markAsControlled(0, 0);
   }
}
