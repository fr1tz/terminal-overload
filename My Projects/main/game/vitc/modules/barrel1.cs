// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(Barrel1FireSound)
{
   //filename = "content/o/torque3d/3.0/sound/cheetah/turret_firing.wav";
   filename = "content/o/torque3d/3.0/sound/turret/wpn_turret_fire.wav";
   description = BulletFireDesc;
   preload = true;
};

//-----------------------------------------------------------------------------

datablock ProjectileData(Barrel1Projectile)
{
   projectileShapeName = "content/o/torque3d/3.0/shapes/weapons/shared/rocket.dts";
   directDamage = 10;
   radiusDamage = 15;
   damageRadius = 3;
   areaImpulse = 1200;

   explosion = RocketLauncherExplosion;
   waterExplosion = RocketLauncherWaterExplosion;

   decal = ScorchRXDecal;
   splash = RocketSplash;

   muzzleVelocity = 250;
   velInheritFactor = 0.7;

   armingDelay = 0;
   lifetime = 5000;
   fadeDelay = 4500;

   bounceElasticity = 0;
   bounceFriction = 0;
   isBallistic = false;
   gravityMod = 0.80;

   damageType = "RocketDamage";
};

datablock ParticleEmitterData(Barrel1FireSmokeEmitter)
{
   ejectionPeriodMS  = 10;
   periodVarianceMS  = 5;
   ejectionVelocity  = 6.5;
   velocityVariance  = 1.0;
   thetaMin          = "0";
   thetaMax          = "0";
   lifetimeMS        = 350;
   particles         = "GunFireSmoke";
   blendStyle        = "NORMAL";
   softParticles     = "0";
   alignParticles    = "0";
   orientParticles   = "0";
};

//-----------------------------------------------------------------------------

datablock StaticShapeData(Barrel1)
{
   category = "Modules";
   shapeFile = "content/vitc/shapes/barrel1/p1/shape.dae";
   ignoreDamage = true;
};

function Barrel1::create(%this)
{
   %obj = new StaticShape()
   {
      dataBlock = %this;
   };
   return %obj;
}

function Barrel1::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   %obj.setShapeName("Barrel" @ %obj.getId());
   %obj.fireWidget = createWidget(%obj, "Barrel1FireWidget");
}

function Barrel1::onRemove(%this, %obj)
{
   Parent::onAdd(%this, %obj);
   %obj.fireWidget.delete();
}

//-----------------------------------------------------------------------------

function Barrel1FireWidget::getDescription(%this)
{
   return "Fire Control";
}

function Barrel1FireWidget::getType(%this)
{
   return 4;	
}

function Barrel1FireWidget::getGridSizeN(%this)
{
   return "2 2";	
}

function Barrel1FireWidget::update(%this, %args)
{
   %obj = %this.moduleObj;
   %val = getWord(%args, 0);
   echo("Barrel1FireWidget:" SPC %val);
%obj.setEnergyLevel(100);

echo(%obj.getEnergyLevel() SPC %obj.getMuzzleVector(0));
   %obj.setImageTrigger(0, %val);
   %obj.ssc.trigger[0] = %val;
}