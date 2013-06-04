// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(CheetahDAE)
{
   baseShape = "./Cheetah_Body.DAE";
   loadLights = "0";
   lodType = "TrailingNumber";
   neverImport = "null  EnvironmentAmbientLight";
   forceUpdateMaterials = "0";
   loadLights = "0";
};

function CheetahDAE::onLoad(%this)
{
   %this.setSequenceCyclic("ambient", "0");
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "0", "1");
   %this.addSequence("timeline", "spring0", "10", "11");
   %this.addSequence("timeline", "spring1", "20", "21");
   %this.addSequence("timeline", "spring2", "30", "31");
   %this.addSequence("timeline", "spring3", "40", "41");
   %this.addSequence("timeline", "brakeLight", "50", "51");
   %this.setSequencePriority("brakeLight", "8");
   %this.setNodeTransform("cam", "5.46934e-008 -4.75632 2.89171 -0.404897 0.817636 0.409303 1.71107", "1");
   %this.removeNode("CheetahMesh300");
   %this.removeNode("CheetahMesh200");
   %this.removeNode("CheetahMesh100");
   %this.removeNode("CheetahMesh2");
   %this.removeNode("TailLightsMesh300");
   %this.removeNode("TailLightsMesh200");
   %this.removeNode("TailLightsMesh100");
   %this.removeNode("TailLightsMesh2");
   %this.removeNode("nulldetail1");
}
