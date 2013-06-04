// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This file contains script methods unique to the WheeledVehicle class.  All
// other necessary methods are contained in "../server/scripts/vehicle.cs" in
// which the "generic" Vehicle class methods that are shared by all vehicles,
// (flying, hover, and wheeled) can be found.

// Parenting is in place for WheeledVehicleData to VehicleData.  This should
// make it easier for people to simply drop in new (generic) vehicles.  All that
// the user needs to create is a set of datablocks for the new wheeled vehicle
// to use.  This means that no (or little) scripting should be necessary.

function WheeledVehicleData::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);

   // Setup the car with some tires & springs
   for (%i = %obj.getWheelCount() - 1; %i >= 0; %i--)
   {
      %obj.setWheelTire(%i, DefaultCarTire);
      %obj.setWheelSpring(%i, DefaultCarSpring);
      %obj.setWheelPowered(%i, false);
   }

   // Steer with the front tires
   %obj.setWheelSteering(0, 1);
   %obj.setWheelSteering(1, 1);

   // Only power the two rear wheels... assuming there are only 4 wheels.
   %obj.setWheelPowered(2, true);
   %obj.setWheelPowered(3, true);
}

function WheeledVehicleData::onCollision(%this, %obj, %col, %vec, %speed)
{
   // Collision with other objects, including items
}

// Used to kick the players out of the car that your crosshair is over
function serverCmdcarUnmountObj(%client, %obj)
{
   %obj.unmount();
   %obj.setControlObject(%obj);

   %ejectpos = %obj.getPosition();
   %ejectpos = VectorAdd(%ejectpos, "0 0 5");
   %obj.setTransform(%ejectpos);

   %ejectvel = %obj.mVehicle.getVelocity();
   %ejectvel = VectorAdd(%ejectvel, "0 0 10");
   %ejectvel = VectorScale(%ejectvel, %obj.getDataBlock().mass);
   %obj.applyImpulse(%ejectpos, %ejectvel);
}

// Used to flip the car over if it manages to get stuck upside down
function serverCmdflipCar(%client)
{
   %car = %client.player.getControlObject();

   if (%car.getClassName() $= "WheeledVehicle")
   {
      %carPos = %car.getPosition();
      %carPos = VectorAdd(%carPos, "0 0 3");

      %car.setTransform(%carPos SPC "0 0 1 0");
   }
}

function serverCmdsetPlayerControl(%client)
{
     %client.setControlObject(%client.player);
}

function serverCmddismountVehicle(%client)
{
   %car = %client.player.getControlObject();
   
   %passenger = %car.getMountNodeObject(0);
   %passenger.getDataBlock().doDismount(%passenger, true);
   
   %client.setControlObject(%client.player);
}