// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock NortDiscData(WpnRazorDisc)
{
   stat = "razordisc";

   // Script damage properties
   impactDamage       = 60;
   impactImpulse      = 1000;
   splashDamage       = 0;
   splashDamageRadius = 0;
   splashImpulse      = 0;

   energyDrain = 0; // how much energy does firing this projectile drain?

   sound = WpnRazorDiscSound;

   targetLockTimeMS = 0;

   maxTrackingAbility = 80;
   trackingAgility = 2;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;

   muzzleVelocity		= 30;
   maxVelocity       = 75;
   acceleration      = 4;
   velInheritFactor	= 1.0;

   armingDelay			= 0*1000;
   lifetime				= 10*1000;
   fadeDelay			  = 3*1000;

   isBallistic = false;
   gravityMod			 = 1.0;
   bounceElasticity	 = 0.99;
   bounceFriction		 = 0.0;
   numBounces           = 3;

   projectileShapeName = "content/xa/notc/core/shapes/razordisc/projectile/p1/shape.dae";

   particleEmitter     = "WpnRazorDiscEmitter";
   
   bounceEffect[0] = WpnRazorDiscBounceEffect;
   bounceEffectTypeMask[0] = $TypeMasks::StaticObjectType;
   
   decal = WpnRazorDiscDecal;
   
   lightDesc = WpnRazorDiscLightDesc;

//	laserTrail[0]		= WpnRazorDiscInnerLaserTrail;
//	laserTrail[1]		= WpnRazorDiscOuterLaserTrail;

   startVertical = true;
};

function WpnRazorDisc::onAdd(%this,%obj)
{
   // echo("WpnRazorDisc::onAdd()");
   // Parent::onAdd(%this,%obj);
}

function WpnRazorDisc::onRemove(%this,%obj)
{
   // echo("WpnRazorDisc::onRemove()");
   // Parent::onRemove(%this,%obj);
}

function WpnRazorDisc::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   //echo("WpnRazorDisc::onCollision()");
   //echo(%col.getClassName());
   if(%obj.zLastCollisionObject == %col)
      return;
	Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist);
   %obj.zLastCollisionObject = %col;
}

function WpnRazorDisc::onDeflected(%this, %obj)
{
   //echo("WpnRazorDisc::onDeflected()");
}

function WpnRazorDisc::onHitTarget(%this, %obj)
{
   //echo("WpnRazorDisc::onHitTarget()");
   %obj.stopAttacking();
}

function WpnRazorDisc::onMissedTarget(%this, %obj)
{
   //echo("WpnRazorDisc::onMissedTarget()");
   %obj.stopAttacking();
}

function WpnRazorDisc::onLostTarget(%this, %obj)
{
   //echo("WpnRazorDisc::onLostTarget()");
   %obj.stopAttacking();
}

// Called by script
function WpnRazorDisc::launch(%this, %source, %muzzlePoint, %muzzleVec, %targets)
{
   //echo("WpnRazorDisc::launch()");
   
   if(%source.getInventory(WpnRazorDiscAmmo) == 0)
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
      %targetHudInfo.getObject().client.play2D(WpnRazorDiscAlertSound);

   %targetHudInfo.delete();
}


