// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock NortDiscData(WpnExplosiveDisc)
{
   stat = "explosivedisc";

   // Script damage properties
	impactDamage       = 0;
	impactImpulse      = 0;
	splashDamage       = 250;
	splashDamageRadius = 10;
	splashImpulse      = 5000;

   energyDrain = 0; // how much energy does firing this projectile drain?

   sound = WpnExplosiveDiscSound;

   targetLockTimeMS = 0;

   maxTrackingAbility = 20;
   trackingAgility = 1;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;

   muzzleVelocity		= 2;
   maxVelocity       = 25;
   acceleration      = 1;
   velInheritFactor	= 1.0;

   armingDelay			= 0*1000;
   lifetime				= 10*1000;
   fadeDelay			= 0*1000;

   isBallistic = false;
   gravityMod			 = 1.0;
   bounceElasticity	 = 0.99;
   bounceFriction		 = 0.0;
   numBounces           = 3;

   projectileShapeName = "content/xa/notc/core/shapes/explosivedisc/projectile/p1/shape.dae";

   particleEmitter     = "WpnExplosiveDiscEmitter";
   
   bounceEffect[0] = WpnExplosiveDiscBounceEffect;
   bounceEffectTypeMask[0] = $TypeMasks::StaticObjectType;
   
   decal = WpnExplosiveDiscDecal;
   
   lightDesc = WpnExplosiveDiscLightDesc;

//	laserTrail[0]		= WpnExplosiveDiscInnerLaserTrail;
//	laserTrail[1]		= WpnExplosiveDiscOuterLaserTrail;

   startVertical = false;
};

function WpnExplosiveDisc::onAdd(%this,%obj)
{
   // echo("WpnExplosiveDisc::onAdd()");
   // Parent::onAdd(%this,%obj);
}

function WpnExplosiveDisc::onRemove(%this,%obj)
{
   // echo("WpnExplosiveDisc::onRemove()");
   // Parent::onRemove(%this,%obj);
}

function WpnExplosiveDisc::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   //echo("WpnExplosiveDisc::onCollision()");
   //echo(%col.getClassName());
}

function WpnExplosiveDisc::onDeflected(%this, %obj)
{
   //echo("WpnExplosiveDisc::onDeflected()");
}

function WpnExplosiveDisc::onHitTarget(%this, %obj)
{
   //echo("WpnExplosiveDisc::onHitTarget()");
   if(%obj.getTarget() == %obj.sourceObject)
   {
      %obj.sourceObject.incInventory(WpnExplosiveDiscAmmo, 1);
   }
   else
   {
      %pos = %obj.getPosition();
      %norm = VectorNormalize(VectorScale(%obj.getForwardVector(), -1));
      %this.onExplode(%obj, %pos, 0);
      createExplosion(WpnExplosiveDiscExplosion, %pos, %norm);
      %obj.schedule(0, "delete");
   }
}

function WpnExplosiveDisc::onMissedTarget(%this, %obj)
{
   //echo("WpnExplosiveDisc::onMissedTarget()");
   %obj.stopAttacking();
}

function WpnExplosiveDisc::onLostTarget(%this, %obj)
{
   //echo("WpnExplosiveDisc::onLostTarget()");
   %obj.stopAttacking();
}

// Called by script
function WpnExplosiveDisc::launch(%this, %source, %muzzlePoint, %muzzleVec, %targets)
{
   //echo("WpnExplosiveDisc::launch()");
   
   if(%source.getInventory(WpnExplosiveDiscAmmo) == 0)
   {
      if(isObject(%source.client))
         %source.playAudio(0, GenericNoAmmoSound);
      return;
   }
   
   %source.decInventory(WpnExplosiveDiscAmmo, 1);
   
   %targetHudInfo = 0;
	%targetCount = %targets.getCount();
 
   if(%targetCount == 0)
   {
      if(isObject(%source.client))
         %source.client.play2D(GenericNoDiscTargetSound);
      return;
   }

   %lowestTargetDist = -1;
	for(%idx= 0; %idx < %targetCount; %idx++)
	{
      %t = %targets.getObject(%idx);
      %dist = VectorLen(VectorSub(%t.getObject().getPosition(), %muzzlePoint));
      if(%lowestTargetDist == -1 || %dist < %lowestTargetDist)
      {
         %targetHudInfo = %t;
         %lowestTargetDist = %dist;
      }
   }
   
   %muzzleSpeed = %this.muzzleVelocity;
   %objectVelocity = %source.getVelocity();
   %muzzleVelocity = VectorAdd(
      VectorScale(%muzzleVec,  %muzzleSpeed),
      VectorScale(%objectVelocity, %this.velInheritFactor));

   %disc = new (NortDisc)() {
      dataBlock       = %this;
      teamId          = %source.teamId;
      initialVelocity = %muzzleVelocity;
      initialPosition = %muzzlePoint;
      sourceObject    = %source;
      sourceSlot      = 1;
      client          = %source.client;
   };
   copyPalette(%source, %disc);
   MissionCleanup.add(%disc);

   %disc.setTargetingMask($TargetingMask::Launcher);
   %disc.setTarget(%targetHudInfo.getObject());
   
   %source.playAudio(0, GenericDiscLaunchSound);
   
   if(isObject(%targetHudInfo.getObject().client))
      %targetHudInfo.getObject().client.play2D(WpnExplosiveDiscAlertSound);

   %targetHudInfo.delete();
}


