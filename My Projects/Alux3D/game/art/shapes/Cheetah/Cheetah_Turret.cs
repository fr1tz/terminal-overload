// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(Cheetah_TurretDAE)
{
   baseShape = "./Cheetah_Turret.DAE";
   lodType = "TrailingNumber";
   neverImport = "null	EnvironmentAmbientLight";
   matNamePrefix = "";
   forceUpdateMaterials = "0";
   loadLights = "0";
};

function Cheetah_TurretDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "fire");
   %this.removeNode("Cheetah_Turret_LOD200");
   %this.removeNode("Cheetah_Turret_LOD2");
   %this.removeNode("Cheetah_Turret_LOD100");
   %this.removeNode("collision-1");
   %this.removeNode("collision-2");
   %this.removeNode("Cheetah_Turret_LOD300");
   %this.removeNode("flash_LOD2");
   %this.removeNode("flash_LOD100");
   %this.removeNode("flash_LOD200");
}
