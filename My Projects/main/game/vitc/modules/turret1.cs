// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock TurretShapeData(Turret1)
{
   category = "Modules";
   shapeFile = "content/vitc/shapes/turret1/p1/shape.dae";

   // Basic Item properties
   mass = 1.5;
   elasticity = 0.1;
   friction = 0.6;
   simpleServerCollision = false;

   maxDamage = 70;
   destroyedLevel = 70;
   explosion = GrenadeExplosion;
   maxEnergy[0] = 100;
   
   zRotOnly = false;
   
   // Rotation settings
   minPitch = 0;
   maxPitch = 80;
   maxHeading = 180;
   headingRate = 50;
   pitchRate = 50;
};

function Turret1::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   %obj.setShapeName("Turret" @ %obj.getId());
   %obj.setAllowManualRotation(true);
   %obj.setAllowManualFire(false);

   %obj.ssc = new SimpleServerSideController();
   %obj.ssc.reset = true;
   %obj.useServerSideController(%obj.ssc);

   %obj.headingWidget = createWidget(%obj, "Turret1HeadingWidget");
   %obj.pitchWidget = createWidget(%obj, "Turret1PitchWidget");
}

function Turret1::onRemove(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   %obj.ssc.delete();
   %obj.headingWidget.delete();
   %obj.pitchWidget.delete();
}

//-----------------------------------------------------------------------------

function Turret1HeadingWidget::getDescription(%this)
{
   return "Heading";
}

function Turret1HeadingWidget::getType(%this)
{
   return 5;	
}

function Turret1HeadingWidget::getGridSizeN(%this)
{
   return "4 4";	
}

function Turret1HeadingWidget::update(%this, %args)
{
   %obj = %this.moduleObj;	
   %val = getWord(%args, 0) * 1;
   echo("Turret1HeadingWidget:" SPC %val);
   %obj.ssc.yaw = %val;
}

//-----------------------------------------------------------------------------

function Turret1PitchWidget::getDescription(%this)
{
   return "Pitch";
}

function Turret1PitchWidget::getType(%this)
{
   return 5;	
}

function Turret1PitchWidget::getGridSizeN(%this)
{
   return "4 4";	
}

function Turret1PitchWidget::update(%this, %args)
{
   %obj = %this.moduleObj;	
   %val = getWord(%args, 0) * 1;
   echo("Turret1PitchWidget:" SPC %val);
   %obj.ssc.pitch = -%val;
}



