// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Global movement speed that affects all cameras.  This should be moved
// into the camera datablock.
$Camera::movementSpeed = 40;

function Observer::onTrigger(%this,%obj,%trigger,%state)
{
   // state = 0 means that a trigger key was released
   if (%state == 0)
      return;

   // Default player triggers: 0=fire 1=altFire 2=jump
   %client = %obj.getControllingClient();
   switch$ (%obj.mode)
   {
      case "Observer":
         // Do something interesting.

      case "Corpse":
         // Fade out the corpse
         if (isObject(%obj.orbitObj))
         {
            cancelAll(%obj.orbitObj);
            %obj.orbitObj.schedule(0, "startFade", 1000, 0, true);
            %obj.orbitObj.schedule(1000, "delete");
         }

         // Viewing dead corpse, so we probably want to respawn.
         game.preparePlayer(%client);

         // Set the camera back into observer mode, since in
         // debug mode we like to switch to it.
         %this.setMode(%obj,"Observer");
   }
}

function Observer::setMode(%this,%obj,%mode,%arg1,%arg2,%arg3)
{
   switch$ (%mode)
   {
      case "Observer":
         // Let the player fly around
         %obj.setFlyMode();

      case "Corpse":
         // Lock the camera down in orbit around the corpse,
         // which should be arg1
         %transform = %arg1.getTransform();
         %obj.setOrbitMode(%arg1, %transform, 0.5, 4.5, 4.5);
         %obj.orbitObj = %arg1;

   }
   %obj.mode = %mode;
}
