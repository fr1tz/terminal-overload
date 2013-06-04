// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(WheelBackDae)
{
   baseShape = "./wheelBack.DAE";
   lodType = "TrailingNumber";
   neverImport = "null	EnvironmentAmbientLight";
   matNamePrefix = "";
   forceUpdateMaterials = "0";
   loadLights = "0";
};

function WheelBackDae::onLoad(%this)
{
   %this.removeNode("TireBack_LOD2");
   %this.removeNode("TireBack_LOD300");
   %this.removeNode("TireBack_LOD200");
   %this.removeNode("TireBack_LOD100");
   %this.removeNode("collision-1");
   %this.removeNode("nulldetail1");
}
