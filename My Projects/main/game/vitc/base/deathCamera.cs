// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock CameraData(DeathCamera)
{
   dummy = "frungy";
};

function DeathCamera::onTrigger(%this,%obj,%trigger,%state)
{
   if(%state == 0)
      return;

   // Default player triggers: 0=fire 1=altFire 2=jump
   %client = %obj.client;
   %dt = getSimTime() - %client.timeOfDeath;
   if(%dt < 5000)
      return;

   // Respawn
   Game.preparePlayer(%client);
}

