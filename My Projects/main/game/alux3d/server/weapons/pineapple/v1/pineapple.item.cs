// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(WpnPineapple)
{
   // Mission editor category
   category = "Weapon";

   // Hook into Item Weapon class hierarchy. The weapon namespace
   // provides common weapon handling functions in addition to hooks
   // into the inventory system.
   className = "Weapon";

   // Basic Item properties
   shapeFile = "content/fr1tz/oldshapes/raptor/magazine/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   PreviewImage = 'lurker.png';
   pickUpName = "Pineapple Bomb";
   description = "Pineapple";
};

function WpnPineapple::activate(%this, %obj)
{
   // Destroy soil tiles.
	InitContainerRadiusSearch(%obj.getPosition(), 2, $TypeMasks::StaticObjectType);
	while((%srchObj = containerSearchNext()) != 0)
	{
      if(!%srchObj.isMethod("getDataBlock"))
         continue;

      if(%srchObj.teamId == 2 && %srchObj.getDataBlock() == MetaSoilTile.getId())
         Soil::destroyTile(%srchObj);
	}
 
   createExplosion(GrenadeLauncherExplosion, %obj.getPosition(), "0 0 1");
   %obj.schedule(0, "delete");
}

function WpnPineapple::onThrow(%this, %user, %amount)
{
   %obj = Parent::onThrow(%this, %user, %amount);
   %obj.fuseThread = %this.schedule(3000, "activate", %obj);
   return %obj;
}

function WpnPineapple::onUse(%this, %obj)
{
   %obj.throw(WpnPineapple);
}
