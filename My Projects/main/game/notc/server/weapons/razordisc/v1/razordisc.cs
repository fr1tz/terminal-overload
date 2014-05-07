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
   
//	explosion             = WpnRazorDiscExplosion;
//	hitEnemyExplosion     = WpnRazorDiscHit;
// nearEnemyExplosion	 = ThisDoesNotExist;
//	hitTeammateExplosion  = WpnRazorDiscHit;
//	hitDeflectorExplosion = WpnRazorDiscDeflectedEffect;
//	bounceExplosion       = WpnRazorDiscHit;

//	laserTrail[0]		= WpnRazorDiscInnerLaserTrail;
//	laserTrail[1]		= WpnRazorDiscOuterLaserTrail;

//	decals[0] = SlashDecalOne;

//lightDesc = "WpnMG1ProjectileLightDesc";

   startVertical = true;
};

function WpnRazorDisc::onAdd(%this,%obj)
{
   echo("WpnRazorDisc::onAdd()");
// Parent::onAdd(%this,%obj);
}

function WpnRazorDisc::onRemove(%this,%obj)
{
   echo("WpnRazorDisc::onRemove()");
//	Parent::onRemove(%this,%obj);
//    if(%obj.state() == $NortDisc::Attacking)
//        %obj.getTarget().removeAttackingDisc(%obj);

//	%source = %obj.sourceObject;
//	%source.incDiscs();
}

function WpnRazorDisc::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist)
{
   echo("WpnRazorDisc::onCollision()");
	Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal,%dist);
}

function WpnRazorDisc::onDeflected(%this, %obj)
{
   echo("WpnRazorDisc::onDeflected()");
//    if(%obj.state() == $NortDisc::Attacking)
//        %obj.getTarget().removeAttackingDisc(%obj);
}

function WpnRazorDisc::onHitTarget(%this, %obj)
{
   echo("WpnRazorDisc::onHitTarget()");
//    %obj.getTarget().removeAttackingDisc(%obj);
    %obj.stopAttacking();
}

function WpnRazorDisc::onMissedTarget(%this, %obj)
{
   echo("WpnRazorDisc::onMissedTarget()");
//    if(%obj.state() == $NortDisc::Attacking)
//        %obj.getTarget().removeAttackingDisc(%obj);

   %obj.stopAttacking();
}

function WpnRazorDisc::onLostTarget(%this, %obj)
{
   echo("WpnRazorDisc::onLostTarget()");
   %obj.stopAttacking();
}

// Called by script
function WpnRazorDisc::launch(%this, %source, %muzzlePoint, %muzzleVec, %targets)
{
   echo("WpnRazorDisc::launch()");

   %target = 0;
	%targetCount = %targets.getCount();
 
   if(%targetCount == 0)
      return;

   %lowestTargetDist = -1;
	for(%idx= 0; %idx < %targetCount; %idx++)
	{
      %t = %targets.getObject(%idx).getObject();
      %dist = VectorLen(VectorSub(%t.getPosition(), %muzzlePoint));
      if(%lowestTargetDist == -1 || %dist < %lowestTargetDist)
      {
         %target = %t;
         %lowestTargetDist = %dist;
      }
   }
   

//	if(%obj.hasDisc() && %target != 0
//	&& %target.numAttackingDiscs() == 0
//	&& !%target.hasBarrier()
//	)
//	{
		%muzzleSpeed = %this.muzzleVelocity;
		%objectVelocity = %source.getVelocity();
		%muzzleVelocity = VectorAdd(
			VectorScale(%muzzleVec,  %muzzleSpeed),
			VectorScale(%objectVelocity, %this.velInheritFactor));

		// create the disc...
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
		%disc.setTarget(%target);

//		%player.clearDiscTarget();
//		%player.decDiscs();
//		%target.addAttackingDisc(%player);
//		%player.playAudio(0, DiscThrowSound);
//		if(%target.client)
//			%target.client.play2D(DiscIncomingSound);
//	}
//	else
//	{
//		if(%player.client)
//			%player.client.play2D(DiscSeekerDeniedSound);
//	}
}


