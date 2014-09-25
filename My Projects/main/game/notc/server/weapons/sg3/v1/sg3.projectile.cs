// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShotgunProjectileData(WpnSG3Projectile : WpnSMG2Projectile)
{
   //projectileShapeName = "content/xa/notc/core/shapes/smg1/projectile/p1/shape.dae";

   // ShotgunProjectileData fields
   bulletDistMode = 1;
	numBullets = 10;
	muzzleSpreadRadius = 0.5;
	referenceSpreadRadius = 1.0;
	referenceSpreadDistance = 25;
};

function WpnSG3Projectile::onAdd(%this, %obj)
{
   //Parent::onAdd(%this, %obj);
   
   return;

   %data = WpnSG3Projectile;
   %ammo = WpnSG3Ammo;
	%player = %obj.sourceObject;
	%slot = %obj.sourceSlot;
 
   if(%player.getInventory(%ammo) == 0)
   {
      %obj.delete();
      return;
   }

   %player.decInventory(%ammo, 1);
}

function WpnSG3Projectile::onCollision(%this,%obj,%col,%fade,%pos,%normal)
{
   Parent::onCollision(%this,%obj,%col,%fade,%pos,%normal);
   
   if( !(%col.getType() & $TypeMasks::ShapeBaseObjectType) )
      return;

   %src = %obj.sourceObject;
   if(!isObject(%src))
      return;

   %currTime = getSimTime();

   // NOTE: This was a problem with ROTC, may not be
   //       a problem with Terminal Overload:
   // FIXME: strange linux version bug:
   //        after the game has been running a long time
   //        (%currTime == %obj.hitTime)
   //        often evaluates to false even if the
   //        values appear to be equal.
   //        (%currTime - %obj.hitTime) evaluates to 1
   //        in those cases.
   if(%currTime - %obj.hitTime <= 1)
   {
      %col.numSG3BulletHits += 1;
      if(%col.numSG3BulletHits == 4)
         %src.getDataBlock().addDiscTarget(%src, %col);
   }
   else
   {
      %obj.hitTime = %currTime;
      %col.numSG3BulletHits = 1;
   }
}

