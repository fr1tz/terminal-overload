// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock BallastShapeData(ItemImpShieldShape)
{
   ignoreDamage = 1;
   shapeFile = "content/xa/rotc/p.5.4/shapes/rotc/misc/nothing.dts";
   //shapeFile = "content/xa/notc/core/shapes/standardcat/impshield/p1/shape.dae";
   mass = 0;
   inheritEnergyFromMount = true;
   levelEnergySlot = 1;
   groundConnectionBeamQuad = "ItemImpShieldBeam";
   canStealth = 1; // script field
};

function ItemImpShieldShape::onMount(%this, %obj, %mountObj, %node)
{
   //echo("ItemImpShieldShape::onMount()");

}

function ItemImpShieldShape::onUnmount(%this, %obj, %mountObj, %node)
{
   //echo("ItemImpShieldShape::onUnmount()");
   %obj.schedule(0, "delete");
}

