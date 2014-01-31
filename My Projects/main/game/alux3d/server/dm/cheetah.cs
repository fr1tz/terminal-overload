// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function CheetahCar::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);

   %obj.setWheelTire(0,CheetahCarTire);
   %obj.setWheelTire(1,CheetahCarTire);
   %obj.setWheelTire(2,CheetahCarTireRear);
   %obj.setWheelTire(3,CheetahCarTireRear);

   // Setup the car with some tires & springs
   for (%i = %obj.getWheelCount() - 1; %i >= 0; %i--)
   {
      %obj.setWheelPowered(%i, true);
      %obj.setWheelSpring(%i, CheetahCarSpring);
   }

   // Steer with the front tires
   %obj.setWheelSteering(0, 1);
   %obj.setWheelSteering(1, 1);

   // Add tail lights
   %obj.rightBrakeLight = new PointLight() 
   {
      radius = "1";
      isEnabled = "0";
      color = "1 0 0.141176 1";
      brightness = "2";
      castShadows = "1";
      priority = "1";
      animate = "0";
      animationPeriod = "1";
      animationPhase = "1";
      flareScale = "1";
      attenuationRatio = "0 1 1";
      shadowType = "DualParaboloidSinglePass";
      texSize = "512";
      overDarkFactor = "2000 1000 500 100";
      shadowDistance = "400";
      shadowSoftness = "0.15";
      numSplits = "1";
      logWeight = "0.91";
      fadeStartDistance = "0";
      lastSplitTerrainOnly = "0";
      representedInLightmap = "0";
      shadowDarkenColor = "0 0 0 -1";
      includeLightmappedGeometryInShadow = "0";
      rotation = "1 0 0 0";
      canSave = "1";
      canSaveDynamicFields = "1";
         splitFadeDistances = "10 20 30 40";
   };
   %obj.leftBrakeLight = new PointLight() 
   {
      radius = "1";
      isEnabled = "0";
      color = "1 0 0.141176 1";
      brightness = "2";
      castShadows = "1";
      priority = "1";
      animate = "0";
      animationPeriod = "1";
      animationPhase = "1";
      flareScale = "1";
      attenuationRatio = "0 1 1";
      shadowType = "DualParaboloidSinglePass";
      texSize = "512";
      overDarkFactor = "2000 1000 500 100";
      shadowDistance = "400";
      shadowSoftness = "0.15";
      numSplits = "1";
      logWeight = "0.91";
      fadeStartDistance = "0";
      lastSplitTerrainOnly = "0";
      representedInLightmap = "0";
      shadowDarkenColor = "0 0 0 -1";
      includeLightmappedGeometryInShadow = "0";
      rotation = "1 0 0 0";
      canSave = "1";
      canSaveDynamicFields = "1";
         splitFadeDistances = "10 20 30 40";
   };

   // Mount a ShapeBaseImageData
   %didMount = %obj.mountImage(TurretImage, %this.turretSlot);

   // Mount the brake lights
   %obj.mountObject(%obj.rightBrakeLight, %this.rightBrakeSlot);
   %obj.mountObject(%obj.leftBrakeLight, %this.leftBrakeSlot);
}

function CheetahCar::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);

   if(isObject(%obj.rightBrakeLight))
      %obj.rightBrakeLight.delete();

   if(isObject(%obj.leftBrakeLight))
      %obj.leftBrakeLight.delete();

   if(isObject(%obj.turret))
      %obj.turret.delete();
}

function serverCmdtoggleBrakeLights(%client)
{
   %car = %client.player.getControlObject();

   if (%car.getClassName() $= "WheeledVehicle")
   {
      if(%car.rightBrakeLight.isEnabled)
      {
         %car.rightBrakeLight.setLightEnabled(0);
         %car.leftBrakeLight.setLightEnabled(0);
      }
      else
      {
         %car.rightBrakeLight.setLightEnabled(1);
         %car.leftBrakeLight.setLightEnabled(1);
      }
   }
}

// Callback invoked when an input move trigger state changes when the CheetahCar
// is the control object
function CheetahCar::onTrigger(%this, %obj, %index, %state)
{
   // Pass trigger states on to TurretImage (to fire weapon)
   switch ( %index )
   {
      case 0:  %obj.setImageTrigger( %this.turretSlot, %state );
      case 1:  %obj.setImageAltTrigger( %this.turretSlot, %state );
   }
}

function TurretImage::onMount(%this, %obj, %slot)
{
   // Load the gun
   %obj.setImageAmmo(%slot, true);
}
