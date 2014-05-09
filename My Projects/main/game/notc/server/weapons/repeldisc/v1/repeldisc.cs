// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock NortDiscData(WpnRepelDisc)
{
   stat = "repeldisc";

   // Script damage properties
	impactDamage       = 0;
	impactImpulse      = 0;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;

   energyDrain = 0; // how much energy does firing this projectile drain?

   sound = WpnRepelDiscSound;

   targetLockTimeMS = 0;

   maxTrackingAbility = 100;
   trackingAgility = 2;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;

   muzzleVelocity		= 30;
   maxVelocity       = 75;
   acceleration      = 4;
   velInheritFactor	= 1.0;

   armingDelay			= 0*1000;
   lifetime				= 10*1000;
   fadeDelay		   = 0*1000;

   isBallistic = false;
   gravityMod			 = 1.0;
   bounceElasticity	 = 0.99;
   bounceFriction		 = 0.0;
   numBounces           = 3;

   projectileShapeName = "content/xa/notc/core/shapes/repeldisc/projectile/p1/shape.dae";

   particleEmitter     = "WpnRepelDiscEmitter";
   
   bounceEffect[0] = WpnRepelDiscBounceEffect;
   bounceEffectTypeMask[0] = $TypeMasks::StaticObjectType;
   
   decal = WpnRepelDiscDecal;
   
   lightDesc = WpnRepelDiscLightDesc;

//	laserTrail[0]		= WpnRepelDiscInnerLaserTrail;
//	laserTrail[1]		= WpnRepelDiscOuterLaserTrail;

   startVertical = true;
};

function WpnRepelDisc::onAdd(%this,%obj)
{
   // echo("WpnRepelDisc::onAdd()");
   // Parent::onAdd(%this,%obj);
}

function WpnRepelDisc::onRemove(%this,%obj)
{
   // echo("WpnRepelDisc::onRemove()");
   // Parent::onRemove(%this,%obj);
}

function WpnRepelDisc::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   //echo("WpnRepelDisc::onCollision()");
   //echo(%col.getClassName());
   if(%obj.zLastCollisionObject == %col)
      return;
      
	//Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist);
 
	if(%col.getType() & $TypeMasks::PlayerObjectType)
	{
      %source = %obj.sourceObject;

		// Push enemy away from player.
		%vec = VectorSub(%col.getPosition(), %source.getPosition());
		%vec = VectorNormalize(%vec);
		%vec = VectorScale(%vec, 45 + 45*(1-%col.zImpShield));
		%col.setVelocity(%vec);

		createExplosion(WpnRepelDiscBounceEffect, %pos, %normal);
	}
 
   %obj.zLastCollisionObject = %col;
}

function WpnRepelDisc::onDeflected(%this, %obj)
{
   //echo("WpnRepelDisc::onDeflected()");
}

function WpnRepelDisc::onHitTarget(%this, %obj)
{
   //echo("WpnRepelDisc::onHitTarget()");
   %obj.stopAttacking();
}

function WpnRepelDisc::onMissedTarget(%this, %obj)
{
   //echo("WpnRepelDisc::onMissedTarget()");
   %obj.stopAttacking();
}

function WpnRepelDisc::onLostTarget(%this, %obj)
{
   //echo("WpnRepelDisc::onLostTarget()");
   %obj.stopAttacking();
}

// Called by script
function WpnRepelDisc::launch(%this, %source, %muzzlePoint, %muzzleVec, %targets)
{
   //echo("WpnRepelDisc::launch()");
   
   if(%source.getInventory(WpnRepelDiscAmmo) == 0)
   {
      if(isObject(%source.client))
         %source.playAudio(0, GenericNoAmmoSound);
      return;
   }
   
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
      %targetHudInfo.getObject().client.play2D(WpnRepelDiscAlertSound);

   %targetHudInfo.delete();
}


