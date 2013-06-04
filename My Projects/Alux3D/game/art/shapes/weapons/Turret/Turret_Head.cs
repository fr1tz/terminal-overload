// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(Turret_HeadDAE)
{
   baseShape = "./Turret_Head.DAE";
   loadLights = "0";
};

function Turret_HeadDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "scan", "140", "412", "1", "0");
   %this.addSequence("timeline", "wait_deploy", "10", "11", "1", "0");
   %this.addSequence("timeline", "deploy", "10", "110", "1", "0");
   %this.addSequence("timeline", "destroyed", "840", "925", "1", "0");
   %this.addSequence("timeline", "fire", "440", "445", "1", "0");
   %this.addSequence("timeline", "fire_alt", "480", "495", "1", "0");
   %this.setSequenceCyclic("wait_deploy", "0");
   %this.setSequenceCyclic("deploy", "0");
   %this.setSequenceCyclic("destroyed", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.setSequenceCyclic("fire_alt", "0");
   %this.addNode("ejectPoint", "bn_head", "0 0 0 0 0 1 1.57", "0");
}
