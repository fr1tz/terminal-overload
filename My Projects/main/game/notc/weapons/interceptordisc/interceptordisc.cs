// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock NortDiscData(WpnInterceptorDisc)
{
   stat = "interceptordisc";

   // Script damage properties
	impactDamage       = 0;
	impactImpulse      = 0;
	splashDamage       = 0;
	splashDamageRadius = 0;
	splashImpulse      = 0;

   energyDrain = 0; // how much energy does firing this projectile drain?

   sound = WpnInterceptorDiscSound;

   targetLockTimeMS = 0;

   maxTrackingAbility = 150;
   trackingAgility = 2;

   explodesNearEnemies = false;
   explodesNearEnemiesRadius = 5;

   muzzleVelocity		= 125;
   maxVelocity       = 125;
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

   projectileShapeName = "content/xa/notc/core/shapes/interceptordisc/projectile/p1/shape.dae";

   particleEmitter     = "WpnInterceptorDiscEmitter";
   
   bounceEffect[0] = WpnInterceptorDiscBounceEffect;
   bounceEffectTypeMask[0] = $TypeMasks::StaticObjectType;
   
   bounceDecal = WpnInterceptorDiscDecal;
   
   lightDesc = WpnInterceptorDiscLightDesc;

//	laserTrail[0]		= WpnInterceptorDiscLaserTrail0;
//	laserTrail[1]		= WpnInterceptorDiscOuterLaserTrail;

   startVertical = true;
};

function WpnInterceptorDisc::onAdd(%this,%obj)
{
   // echo("WpnInterceptorDisc::onAdd()");
   // Parent::onAdd(%this,%obj);
}

function WpnInterceptorDisc::onRemove(%this,%obj)
{
   // echo("WpnInterceptorDisc::onRemove()");
   // Parent::onRemove(%this,%obj);
}

function WpnInterceptorDisc::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   //echo("WpnInterceptorDisc::onCollision()");
}

function WpnInterceptorDisc::onDeflected(%this, %obj)
{
   //echo("WpnInterceptorDisc::onDeflected()");
}

function WpnInterceptorDisc::onHitTarget(%this, %obj)
{
   //echo("WpnInterceptorDisc::onHitTarget()");
   %source = %obj;
   %target = %obj.getTarget();
   %vel = VectorScale(%obj.getForwardVector(), %this.maxVelocity);
   %this.deflectDisc(%target, %obj, %vel);
   %obj.schedule(0, "delete");
}

function WpnInterceptorDisc::onMissedTarget(%this, %obj)
{
   //echo("WpnInterceptorDisc::onMissedTarget()");
}

function WpnInterceptorDisc::onLostTarget(%this, %obj)
{
   echo("WpnInterceptorDisc::onLostTarget()");
   %obj.schedule(0, "delete");
}

// Called by script
function WpnInterceptorDisc::deflectDisc(%this, %target, %source, %vel)
{
   createExplosion(WpnInterceptorDiscExplosion, %target.getPosition(), %target.getForwardVector());
   if(%target.getDataBlock().isMethod("setDeflected"))
   {
      %target.getDataBlock().setDeflected(%target, %source, %vel);
   }
   else
   {
      %target.setDeflected(%vel);
   }
}

// Called by script
function WpnInterceptorDisc::launch(%this, %source, %muzzlePoint, %muzzleVec, %targets)
{
   //echo("WpnInterceptorDisc::launch()");

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

   %targetHudInfo.delete();
}


