// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ItemImpShield)
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
   pickUpName = "Impulse Shield";
   description = "Impulse Shield";
};

function ItemImpShield::onInventory(%this, %obj, %amount)
{
   if(%amount == 0)
   {
      %obj.setEnergyLevel(0, 1);
   
      %obj.zImpulseDamper = 0.0;
      %obj.zImpulseDamperRechargeRate = 0.0;
      if(%obj.getDataBlock().isMethod("updateImpulseDamperProperties"))
         %obj.getDataBlock().updateImpulseDamperProperties(%obj);
         
      if(isObject(%obj.ballast))
         %obj.ballast.delete();
   }
   else
   {
      %obj.setEnergyLevel(%obj.getDataBlock().maxEnergy[1], 1);
   
      %obj.zImpulseDamper = 0.75;
      %obj.zImpulseDamperRechargeRate = 0.4;
      if(%obj.getDataBlock().isMethod("updateImpulseDamperProperties"))
         %obj.getDataBlock().updateImpulseDamperProperties(%obj);
      
      %obj.ballast = new BallastShape() {
         dataBlock = ItemImpShieldShape;
      };
      copyPalette(%obj, %obj.ballast);
      %obj.mountObject(%obj.ballast, 3);
      MissionCleanup.add(%obj.ballast);
   }
}
