// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(Turret_LegsDAE)
{
   baseShape = "./Turret_Legs.DAE";
   loadLights = "0";
   lodType = "DetectDTS";
};

function Turret_LegsDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "110", "111", "1", "0");
   %this.addSequence("timeline", "scan", "140", "412", "1", "0");
   %this.addSequence("timeline", "throw", "10", "11", "1", "0");
   %this.addSequence("timeline", "deploy", "10", "110", "1", "0");
   %this.addSequence("timeline", "destroyed", "840", "925", "1", "0");
   %this.addSequence("timeline", "light_recoil", "440", "445", "1", "0");
   %this.addSequence("timeline", "medium_recoil", "480", "495", "1", "0");
   %this.setSequenceCyclic("throw", "0");
   %this.setSequenceCyclic("deploy", "0");
   %this.setSequenceCyclic("destroyed", "0");
   %this.setSequenceCyclic("light_recoil", "0");
   %this.setSequenceCyclic("medium_recoil", "0");
   %this.setSequenceBlend("light_recoil", "1", "root", "0");
   %this.setSequenceBlend("medium_recoil", "1", "root", "0");
   %this.setMeshSize("ColCapsule-1 2", "-1");
}
