// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(TP_RaptorDAE)
{
   baseShape = "./TP_Raptor.DAE";
   forceUpdateMaterials = "0";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function TP_RaptorDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.setSequenceCyclic("timeline", "0");
   %this.addSequence("timeline", "root", "0", "0", "1", "0");
   %this.addSequence("timeline", "fire", "0", "1", "1", "0");
   %this.addSequence("timeline", "fire_vis", "9", "18", "1", "0");
}
