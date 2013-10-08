// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock RigidShapeData(FrmParrotWreck)
{
   isInvincible = true;

   shapeFile = "share/shapes/alux/parrot.dts";
   emap = true;

   // Rigid body
   mass = 90;
   massCenter = "0 0 0";   // Center of mass for rigid body
   massBox = "0 0 0";      // Size of box used for moment of inertia, \
                           // if zero it defaults to object bounding box
   bodyFriction = 0.5;     // Don't mess with this.
   bodyRestitution = 0.2;  // When you hit the ground, how much you rebound. (between 0 and 1)

   softImpactSpeed = 2;    // Sound hooks. This is the soft hit.
   hardImpactSpeed = 5;    // Sound hooks. This is the hard hit.

   integration = 4;        // Physics integration: TickSec/Rate
   collisionTol = 0.1;     // Collision distance tolerance
   contactTol = 0.1;       // Contact velocity tolerance
   
   softImpactSound  = FrmParrotSoftImpactSound;
   hardImpactSound  = FrmParrotHardImpactSound;
};

function FrmParrotWreck::onAdd(%this,%obj)
{
   Parent::onAdd(%this,%obj);

   // add wreck FX...
	%fx = new FXShape() {
		dataBlock = BomberWreckFX;
	};
   MissionCleanup.add(%fx);
   %fx.linkToObject(%obj);
   %obj.fx = %fx;
}

function FrmParrotWreck::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);

   // delete wreck fx...
   if(isObject(%obj.fx))
      %obj.fx.delete();
}
