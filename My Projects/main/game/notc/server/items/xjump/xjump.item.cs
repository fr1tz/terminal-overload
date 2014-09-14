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
      //%obj.allowJumping(true);
   }
   else
   {
      //%obj.allowJumping(false);
   }
}

function ItemXJump::activate(%this, %obj, %val)
{
   if(!%val)
      return;
      
   if(%obj.zImpShield < %this.useCostImpulseDamper)
      return;
      
   %canJump = false;
   %typeMask = $TypeMasks::ShapeBaseObjectType | $TypeMasks::StaticObjectType;
   %vec = "0 0 0";
   %start = %obj.getWorldBoxCenter();

   %numMisses = 0;
   for(%x = -0.3; %x <= 0.3; %x += 0.1)
   {
      for(%y = -0.3; %y <= 0.3; %y += 0.1)
      {
         for(%z = -0.3; %z <= 0.3; %z += 0.1)
         {
            %v = VectorScale(VectorNormalize(%x SPC %y SPC %z), 5);
            %end = VectorAdd(%start, %v);
            %col = ContainerRayCast(%start, %end, %typeMask, %obj);
            if(%col)
            {
               %canJump = true;
               %vec = VectorAdd(%vec, %v);
            }
            else
            {
               %numMisses++;
            }
         }
      }
   }

   if(!%canJump)
      return;
      
   %vec = VectorAdd(%vec, 0 SPC 0 SPC -0.0*%numMisses);

   %speedfactor = VectorLen(%obj.getVelocity())/25;
   if(%speedfactor < 1)
      %speedfactor = 1;

   %power = 500*%speedfactor;
   %impulseVec = VectorNormalize(%vec);
   //error(%power SPC %impulseVec);
   %impulseVec = VectorScale(%impulseVec, -%power);
   %obj.impulse(%start, %impulseVec, %obj);
   
   %obj.zImpShield -= %this.useCostImpulseDamper;
      
   // Eyecandy
   %data = ItemXJumpProjectile;
   %muzzlePoint = %start;
   %muzzleVec = VectorScale(VectorNormalize(%vec), 9999);
   %p = new Projectile() {
      dataBlock       = %data;
      teamId          = %obj.teamId;
      initialVelocity = %muzzleVec;
      initialPosition = %muzzlePoint;
      sourceObject    = %obj;
      sourceSlot      = 0;
      client          = %obj.client;
   };
   copyPalette(%obj, %p);
   MissionCleanup.add(%p);
}

