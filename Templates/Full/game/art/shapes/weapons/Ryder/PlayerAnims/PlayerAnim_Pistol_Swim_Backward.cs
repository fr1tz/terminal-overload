// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(PlayerAnim_Pistol_Swim_BackwardDAE)
{
   baseShape = "./PlayerAnim_Pistol_Swim_Backward.DAE";
   neverImport = "EnvironmentAmbientLight";
   loadLights = "0";
};

function PlayerAnim_Pistol_Swim_BackwardDAE::onLoad(%this)
{
   %this.setSequenceCyclic("ambient", "true");
   %this.addSequence("ambient", "Swim_Backward", "1600", "1659");
}
