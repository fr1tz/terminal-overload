// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemXJump)
{
   // Mission editor category
   category = "Item";

   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/standardcat/impshield/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "XJump Module";
   description = "XJump Module";
   useCostImpulseDamper = 0.15;
};

function ItemXJump::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      %obj.allowChargedXJump(false);
      %obj.allowInstantXJump(false);
   }
   else
   {
      %obj.allowChargedXJump(true);
      %obj.allowInstantXJump(true);
   }
}

function ItemXJump::onXJump(%this, %obj, %dir)
{
   //echo("ItemXJump::onXJump()");
   
   %pos = %obj.getWorldBoxCenter();
   %vel = VectorScale(VectorNormalize(%dir), -9999);
   
     // create the projectile object...
   %p = new Projectile() {
      dataBlock       = ItemXJumpProjectile;
      teamId          = %obj.teamId;
      initialVelocity = %vel;
      initialPosition = %pos;
      sourceObject    = %obj;
      sourceSlot      = 0;
      client          = %obj.client;
   };
   copyPalette(%obj, %p);
   MissionCleanup.add(%p);
}

