// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Inventory items.  These objects rely on the item & inventory support
// system defined in item.cs and inventory.cs

//-----------------------------------------------------------------------------
// Health Patches cannot be picked up and are not meant to be added to inventory.
// Health is applied automatically when an objects collides with a patch.
//-----------------------------------------------------------------------------

function HealthPatch::onCollision(%this, %obj, %col)
{
   // Apply health to colliding object if it needs it.
   // Works for all shapebase objects.
   if (%col.getDamageLevel() != 0 && %col.getState() !$= "Dead")
   {
      %col.applyRepair(%this.repairAmount);

      %obj.respawn();
      if (%col.client)
         messageClient(%col.client, 'MsgHealthPatchUsed', '\c2Health Patch Applied');
      serverPlay3D(HealthUseSound, %obj.getTransform());
   }
}

function ShapeBase::tossPatch(%this)
{
   //error("ShapeBase::tossPatch(" SPC %this.client.nameBase SPC ")");
   if(!isObject(%this))
      return;

   %item = ItemData::createItem(HealthKitPatch);
   %item.sourceObject = %this;
   %item.static = false;
   MissionCleanup.add(%item);

   %vec = (-1.0 + getRandom() * 2.0) SPC (-1.0 + getRandom() * 2.0) SPC getRandom();
   %vec = vectorScale(%vec, 10);
   %eye = %this.getEyeVector();
   %dot = vectorDot("0 0 1", %eye);
   if (%dot < 0)
      %dot = -%dot;
   %vec = vectorAdd(%vec, vectorScale("0 0 8", 1 - %dot));
   %vec = vectorAdd(%vec, %this.getVelocity());
   %pos = getBoxCenter(%this.getWorldBox());

   %item.setTransform(%pos);
   %item.applyImpulse(%pos, %vec);
   %item.setCollisionTimeout(%this);
   //serverPlay3D(%item.getDataBlock().throwSound, %item.getTransform());
   %item.schedulePop();

   return %item;
}
